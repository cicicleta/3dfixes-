# Stereo 3D Shader Hacking: Finding CAMRIGHT

Guide for locating and using camera vectors (`camright`, `camup`, `camforward`) in DirectX shaders for stereoscopic 3D fixes using 3DMigoto, geo-11, and DGVoodoo2.

---

## **Finding CAMRIGHT: 8 Essential Rules**

### **RULE 1: It's a 3-component orthogonal vector**

`camright` is a 3D vector (x, y, z) that must:
- Be **orthogonal** (perpendicular) to `camup` and `camforward`
- Have magnitude **≈ 1.0** (normalized)

**Verification:**
```
camright · camup = 0
camright · camforward = 0
magnitude = sqrt(x² + y² + z²) ≈ 1.0
```

**Example:**
```
camright = (0.707, 0.707, 0.0)
magnitude = sqrt(0.707² + 0.707² + 0.0²) = 1.0 ✓
```

---

### **RULE 2: View matrix has predictable structure**

The View matrix always contains:
```
[camright.x,    camup.x,    -camforward.x,   0]
[camright.y,    camup.y,    -camforward.y,   0]
[camright.z,    camup.z,    -camforward.z,   0]
[?,             ?,          ?,               1]
```

**Key points:**
- First **column** = `camright`
- Second **column** = `camup`
- Third **column** = `-camforward` (negated, important)
- Fourth row always ends in 1

---

### **RULE 3: Search in "global" constant buffers**

Search order (by priority):
1. **cb0** ← Start here always
2. **cb1** ← Second candidate
3. **cb2** ← Third candidate
4. **cb3** ← Fourth candidate
5. **cb13** ← If not found above

Avoid cb10+, cb14, cb20+ initially — these are typically specialized (lights, post-process, etc.).

---

### **RULE 4: Visual pattern in dumps**

Two distinct storage patterns:

#### **Row-Major (per-row):**
```
cb0[4] = [0.707, 0.707, 0.0, 0.0]      ← camright complete in ONE line
cb0[5] = [-0.707, 0.707, 0.0, 0.0]     ← camup complete in ONE line
cb0[6] = [0.0, 0.0, 1.0, 0.0]          ← camforward complete in ONE line
```

**Visual clue:** The 3 values sit in the same line. Diagonal moves across.

**To access:**
```hlsl
float3 camright = cb0[4].xyz;
float3 camup = cb0[5].xyz;
float3 camforward = -cb0[6].xyz;  // Negated
```

#### **Column-Major (per-column):**
```
cb0[0] = [0.707, -0.707, 0.0, ...]    ← camright.x, camup.x, forward.x
cb0[1] = [0.707, 0.707, 0.0, ...]     ← camright.y, camup.y, forward.y
cb0[2] = [0.0, 0.0, 1.0, ...]         ← camright.z, camup.z, forward.z
```

**Visual clue:** Same position repeats down different slots; values form columns.

**To access:**
```hlsl
float3 camright = float3(cb0[0].x, cb0[1].x, cb0[2].x);
float3 camup = float3(cb0[0].y, cb0[1].y, cb0[2].y);
float3 camforward = -float3(cb0[0].z, cb0[1].z, cb0[2].z);  // Negated
```

---

### **RULE 5: Quick shader test to confirm**

Don't guess — test both formats in shader:

```hlsl
// Test row-major
float3 camright_row = cb0[4].xyz;

// Test column-major
float3 camright_col = float3(cb0[0].x, cb0[1].x, cb0[2].x);
```

Apply to stereo correction, compile, and test in-game:
1. **Rotate camera left/right** → effect should rotate smoothly with it
2. **If effect moves strangely or stays stuck** → try the other format
3. **If correct:** effect rotates naturally as camera rotates

---

### **RULE 6: Magnitude = scale hint**

The vector's length reveals its nature:

| Magnitude | Meaning | Action |
|-----------|---------|--------|
| ≈ 1.0 | Pure View vector | ✓ Likely camright |
| 1.2 - 2.0 | Mixed with projection | Possible, but verify |
| > 5 | Unrelated data | ✗ Discard, search elsewhere |

```
magnitude = sqrt(x² + y² + z²)
```

**Example:**
```
Vector = (1.5, 0.5, 0.2)
magnitude = sqrt(1.5² + 0.5² + 0.2²) ≈ 1.6
Result: Possibly mixed with projection, but could work
```

---

### **RULE 7: Engine-specific locations**

#### **Unity:**
- Location: **cb3** (typical)
- Format: **column-major**
- Typical slots:
  ```
  cb3[9].xyz   = first column (camright)
  cb3[10].xyz  = second column (camup)
  cb3[11].xyz  = third column (camforward)
  ```
- Or search cb3[20-23], cb3[24-27] for full matrices

#### **Unreal Engine:**
- Location: **cb0**
- Format: **row-major**
- Pattern: Look for `View[0]`, `View[1]`, `View[2]` or slots 0-3
- Projection typically in slots 4-7

#### **Custom/Unknown:**
Use Rule 8 (systematic process).

---

### **RULE 8: Systematic process if lost**

Follow this step-by-step when you can't locate vectors:

**Step 1: Dump all cbuffers**
```
Dump cb0, cb1, cb2, cb3, cb13 in full
Save to file for comparison
```

**Step 2: Find 3 orthogonal vectors**

Search for vectors with:
- Magnitude ≈ 1.0
- Dot products ≈ 0 (perpendicular to each other)

**Example search:**
```
cb0[4] = (0.707, 0.707, 0.0)    magnitude = 1.0 ✓
cb0[5] = (-0.707, 0.707, 0.0)   magnitude = 1.0 ✓
cb0[6] = (0.0, 0.0, 1.0)        magnitude = 1.0 ✓

dot(cb0[4], cb0[5]) = 0 ✓
dot(cb0[4], cb0[6]) = 0 ✓
Found candidates!
```

**Step 3: Rotate camera 180°**
1. Dump cbuffer **BEFORE** rotation
2. Rotate camera 180° in-game (turn around completely)
3. Dump cbuffer **AFTER** rotation

**Step 4: Compare dumps**

Do your candidate vectors also rotate 180°?

```
Before rotation:
  vector1 = (1.0, 0.0, 0.0)
  vector2 = (0.0, 1.0, 0.0)
  vector3 = (0.0, 0.0, 1.0)

After 180° rotation:
  vector1 = (-1.0, 0.0, 0.0)   ← Rotated 180° ✓
  vector2 = (0.0, 1.0, 0.0)    ← Did NOT rotate (camup) ✓
  vector3 = (0.0, 0.0, -1.0)   ← Rotated 180° ✓
```

**If this pattern matches:** You found the vectors!

**Step 5: Zoom in/out**

Change camera focal distance (zoom):
- Magnitude should remain ≈ 1.0
- If magnitude changes significantly → Might be mixed with projection

```
Before zoom:  magnitude = 1.0
After zoom:   magnitude = 1.0
Result: Pure View ✓
```

**Step 6: Confirm**

The vector trio that passes **rotation test** AND maintains **constant magnitude** = **Found it!**

---

## **Understanding Camera Vectors**

### **The 3 vectors:**

| Vector | Points to | Changes when... | Stays same when... |
|--------|-----------|-----------------|-------------------|
| **camright** | Right side of camera | Rotating yaw (turning left/right) | Looking up/down (pitch) |
| **camup** | Up from camera | Pitching (looking up/down) | Rotating yaw |
| **camforward** | Where camera looks/ahead | Any rotation | Never (always reflects view direction) |

### **Quick identification test:**

Move camera to achieve: `camright=(1,0,0)`, `camup=(0,1,0)`, `camforward=(0,0,1)`

This "identity" state makes vectors easiest to spot in dumps visually.

### **Behavior when rotating right:**
```
Move mouse RIGHT (rotate yaw 90°):
  camright   = (1,0,0) → (0,0,-1)    CHANGED ✓
  camup      = (0,1,0) → (0,1,0)     NO CHANGE
  camforward = (0,0,1) → (1,0,0)     CHANGED ✓
```

### **Behavior when looking up:**
```
Move mouse UP (pitch 90°):
  camright   = (1,0,0) → (1,0,0)     NO CHANGE
  camup      = (0,1,0) → (0,0,-1)    CHANGED ✓
  camforward = (0,0,1) → (0,1,0)     CHANGED ✓
```

---

## **Why CAMRIGHT is Used for Stereo Correction**

**Stereoscopic 3D problem:** Eyes see **horizontally separated** (left eye left, right eye right).

**Solution needed:** Correct pixels in **horizontal axis** (left-right on screen).

**camright** = vector pointing **horizontally right** of camera → **Perfect for this correction**.

**Not camforward:**
- Points "ahead" of camera, not left/right
- Doesn't tell you which direction is "screen right"

---

## **Common Stereo Corrections Using camright**

### **Basic HUD/UI correction (convergence-invariant):**
```hlsl
float3 camright = cb0[4].xyz;  // or however you extract it
o0.x += separation * (1.0 - convergence / o0.w) * camright.x;
```

### **SSR (Screen Space Reflection) correction:**
```hlsl
float3 camright = cb0[4].xyz;
r1.x += separation * (1.0 - convergence / v4.w) * camright.x * 0.5;
```

### **Decal stereo fix (world-space):**
```hlsl
float3 camright = cb0[4].xyz;
o0.x -= separation * (1.0 - convergence/o0.w) * camright.x;
```

### **Shadow halo correction (convergence-dependent):**
```hlsl
float3 camright = cb0[4].xyz;
o3.x -= stereo.x * camright.x / depth;
```

---

## **Troubleshooting**

| Problem | Cause | Solution |
|---------|-------|----------|
| "All cbuffer values change when I move camera" | Looking at projection matrix, not View | Search different cb slots |
| "Magnitude is always 1.0 but rotation test fails" | Wrong row/column format | Try the other format (Rule 5) |
| "Values don't change at all when I move" | Shader not executing or cbuffer not used | Verify with PIX/RenderDoc frame capture |
| "Found 3 vectors but one has magnitude 2.0" | Scaled View matrix | Use it anyway, note scale factor in comments |
| "Effect rotates but in wrong direction" | Using `-camright` instead of `camright` | Remove the negation |
| "Effect looks correct but breaks at certain angles" | Missing camup or camforward for full correction | May need 3D correction, not just x-axis |

---

## **Real-world Example: DayZ Standalone**

Shadow pixel shader (hash `3891f53772483be9`):

**Found:** camright in cb0[9-11] (column-major, Unity-style)

**Extract:**
```hlsl
float3 camright = float3(cb0[9].x, cb0[10].x, cb0[11].x);
```

**Apply correction at shadow space UV calculation:**
```hlsl
// Before: r5.x = shadow_uv.x (wrong, ignores stereo)
// After:
r5.x += stereo.x / depth_value;  // Simplified
// Or full:
r5.x += separation * (1.0 - convergence/depth) * camright.x;
```

Result: Shadows stay world-positioned instead of screen-stuck.

---

## **Related Concepts**

- **camup:** Usually (0, 1, 0) in gravity-based games; only changes with pitch
- **camforward:** Combination of all rotations — use for directional effects
- **View matrix:** Contains all 3 vectors
- **Convergence:** Depth offset in stereo; multiply with camright for horizontal correction
- **Separation:** Eye distance in stereo 3D; controls stereo intensity
- **Orthotest:** dot(camright, camup) ≈ 0 to verify orthogonality

---

**Last updated:** June 2026
**Status:** Complete guide for locating camright in any DX11 stereo 3D shader
