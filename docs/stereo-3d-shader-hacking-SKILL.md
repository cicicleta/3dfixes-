---
name: stereo-3d-shader-hacking
description: "Recognizes patterns and formulas for stereoscopic 3D shader fixes across games. Use this whenever debugging stereo rendering issues, analyzing shader problems, working with 3Dmigoto fixes, or implementing convergence/depth corrections. Apply this for any stereo 3D, shader analysis, screen-space fixes, HUD/decal/particle correction, depth buffer reconstruction, or cross-game stereo hacking questions."
compatibility: "3Dmigoto, HLSL shader analysis, nvidia_dx11, geo-11, DGVoodoo2"
---

# Stereo 3D Shader Hacking Pattern Recognition

A comprehensive guide to recognized patterns, formulas, and techniques for fixing stereoscopic rendering issues across PC games using 3Dmigoto, HLSL, and shader analysis.

## Core Stereo Correction Formulas

### Fundamental Screen-Space Correction
The baseline stereo correction applied to screen-space X coordinates in pixel shaders:

```hlsl
o0.x += s.x * (1 - s.y / depth)
```

**Components:**
- `s.x` = stereo separation (constant, pulled from stereo state)
- `s.y` = convergence distance
- `depth` = linear depth of current pixel (from depth buffer or clip-space w)
- Result: corrects for parallax shift accounting for depth

**Variants by depth source:**
- **From clip-space w:** `o0.x += s.x * (1 - s.y/o0.w)` — use when w contains depth
- **From depth buffer:** `o0.x += s.x * (1 - s.y/depthValue)` — requires depth buffer fetch
- **Depth-invariant:** `o0.x += s.x * (1 - s.x/v0.w)` — when convergence scale unknown

### Masterotaku Base Formulas (with empirical scaling)

**Screen-depth correction (most common starting point):**
```hlsl
o0.x -= separation * (o0.w - convergence)
```
**Usage:** First thing to try when element is at screen depth. Load stereo params:
```hlsl
float4 stereo = StereoParams.Load(0);
float separation = stereo.x;
float convergence = stereo.y;
```

**Light/effect correction with convergence influence scaling:**
```hlsl
r1.x -= separation * (r1.w - convergence * 0.07)
```
**Why the multiplier (0.07)?** Without it, lights move too fast when increasing convergence. The multiplier is empirically determined (trial and error) to keep lights at correct position regardless of convergence setting. Typical range: 0.07-0.9 depending on element type and desired responsiveness.

**HUD with aggressive convergence response:**
```hlsl
o0.x += stereo.x * (o0.w - stereo.y * 0.20)
```
**Usage:** UI elements that need strong convergence tracking. Adjust multiplier (0.20) based on visual feedback.

### Convergence-Aware Depth Compensation
For decals and elements where convergence offset matters:

```hlsl
r2.x -= s.x * (1 - s.y / r0.y)
```

**Application:** Kingdom Come decals, terrain-following elements  
**Why:** Prevents misalignment when convergence is non-zero; simpler formula works only at convergence=0

### Scale Factor Compensation
When game units don't match world coordinates (e.g., isometric games):

```hlsl
o0.x += s.x * (o0.w - s.y*SCALE_FACTOR) / o0.w
```

**Example:** Death's Door ice reflections use `SCALE_FACTOR=39` to match game's unit scale

## Pattern Recognition by Element Type

### HUD & UI Elements

**Pattern: Orthographic HUD (all elements o0.w=1.0)**
- **Detection:** All HUD elements output `o0.w=1.0` (clip-space orthographic)
- **Formula:** `o0.x += s.x * (1 - s.y/1.0) * multiplier` → simplifies to `o0.x += s.x * (1 - s.y) * multiplier`
- **Screen-space conversion:** `screenX = o0.x * 0.5 + 0.5` (from [-1,1] to [0,1] NDC)
- **Calibration:** Apply with multiplier 1.0, cycle convergence values, adjust multiplier empirically

**Pattern: Depth-based HUD masking**
- **Detection:** HUD elements at varying depths (some background, some foreground)
- **Formula:** Use `smoothstep()` for soft falloff based on depth
  ```hlsl
  float depthMask = smoothstep(nearZ, farZ, pixelDepth);
  correction = s.x * (1 - s.y/pixelDepth) * depthMask;
  ```
- **Applications:** Forever Skies UI, cursor with depth falloff

**Pattern: PNG mask sampling with resolution independence**
- **Technique:** Sample PNG mask at resolution-scaled UVs
  ```hlsl
  float2 maskUV = screenPos * float2(rt_width_inv, rt_height_inv);
  float mask = maskTexture.Sample(sampler, maskUV).r;
  correction *= mask;
  ```
- **Use case:** Selective HUD correction (hide correction in certain screen regions)

**Pattern: Render target size filtering (offscreen buffers)**
- **Detection:** Some HUD drawn to offscreen buffer before copying to screen
- **Method:** Pass render target dimensions via IniParams
  ```ini
  [ShaderOverrideHUDBlue]
  Hash = xxx
  x1 = rt_width
  y1 = rt_height
  z1 = res_width
  w1 = res_height
  ```
- **In shader:**
  ```hlsl
  float4 rt_filter = IniParams.Load(int2(1,0));
  if (rt_filter.x == rt_filter.z && rt_filter.y == rt_filter.w) {
    // Render target dimensions match resolution - adjust UI depth
    correction_enabled = 1;
  }
  ```

**Pattern: Texture-based HUD filtering**
- **Detection:** Isolate specific HUD elements using texture hash + filter_index
  ```ini
  [TextureOverrideCrosshair]
  Hash = xxx
  filter_index = 2
  ```
- **In shader:**
  ```hlsl
  float4 tex_filter = IniParams.Load(int2(2,0));
  if (tex_filter.x == 2) {
    o0.x += stereo.x * 0.9;  // Apply correction only to crosshair
  }
  ```
- **Use case:** Selective fixes when multiple shaders are affected

### Partner Shader Filtering

**Pattern: Conditional fix application based on pixel shader presence**
- **Context:** Complex material with multiple effects; only some need stereo correction
- **Method:** Vertex shader sets flag based on accompanying pixel shader
  ```ini
  [ShaderOverrideWetRocksDecalsEtcVS]
  Hash = e40b51d48a2da321
  y2 = 0  ; Default: disable correction
  
  [ShaderOverrideWetRocksPS]
  Hash = xxxxxxxx
  ; Pixel shader detection triggers VS fix
  post y2 = 1
  ```
- **Why:** Prevents correcting elements that don't need it (e.g., wet rocks YES, other effects NO)
- **Workflow:** 3Dmigoto processes VS before PS, allowing PS to toggle VS behavior

**Example:** Applying mono copy technique for testing
- Copy shader to "mono" variant: test with one eye to isolate stereo vs. base shader issues
- Helps determine if problem is stereo logic or underlying shader

### Lens Flares & Volumetric Effects

**Pattern: Volumetric lens flare (UE4)**
- **Detection:** Post-normalized screen coordinates, radial from center
- **Fix location:** Pixel shader, after normalizing `r0.xy` to `[-0.5, 0.5]`
- **Formula:**
  ```hlsl
  r0.x -= s.x * (1 - s.y / v3.w) * 0.5;
  r1.xy = v3.ww * r0.xy;  // then apply existing math
  ```
- **Reference:** Forever Skies volumetric flare fix
- **Key:** Apply stereo offset **before** scaling by clip-space w

**Pattern: Stained glass / vitral shaders**
- **Detection:** Refraction-based shaders sampling through glass
- **Wrong approach:** Applying stereo in texture-space
- **Correct approach:** Apply before `t5.SampleLevel()` to adjust refraction direction
- **Formula:** Adjust `r4.x` (refraction direction X) before sample
  ```hlsl
  r4.x += s.x * (1 - s.y/v0.w);
  t5.SampleLevel(...);
  ```

### Decals & Projected Textures

**Pattern: Simple decal at convergence=0**
- **Formula:** `r2.x -= s.x` (no depth compensation needed)
- **Application:** Kingdom Come decals work with this alone at convergence=0

**Pattern: Convergence-aware decal projection**
- **Formula:** `r2.x -= s.x * (1 - s.y / r0.y)`
- **Why:** Full compensation when convergence ≠ 0
- **Context:** Kingdom Come with convergence > 0 requires this
- **Detection:** If simpler formula causes misalignment across convergence values, use full formula

**Pattern: Unity decals with reciprocal depth (clip-space w = 1/z)**
- **Context:** Unity uses reciprocal depth (`1/z`) in clip-space w for Z-buffer optimization
- **Formula:** `r0.x -= s.x * (1.0 - s.y * r0.w) * calibration_factor`
- **Why multiply instead of divide?** Because `r0.w = 1/depth`, the formula becomes:
  ```
  offset = separation * (1 - convergence * reciprocal_depth)
  offset = separation * (1 - convergence / depth)  [mathematically equivalent]
  ```
- **Critical timing:** Apply correction **BEFORE** `/r0.www` (perspective divide)
- **Convergence invariance:** The factor `(1.0 - s.y * r0.w)` scales dynamically with both depth and convergence
- **Calibration:** 
  - Test with convergence sweep (0 cm, ±5 cm, ±10 cm)
  - Multiplier remains constant across all convergence values if formula is correct
  - Example: `1.02999938` for snow footprint decals (game unit scale specific)
- **Application context:** Projected decals, huellas en la nieve, terrain-conforming textures
- **Validation:** Fix works identically across full convergence range (truly convergence-invariant)

### Particles & Compute Shaders

**Pattern: Bee swarm or particle displacement (compute shader)**
- **Detection:** Hash-based stereo offset application before `store_uav_typed`
- **Formula:**
  ```hlsl
  r7 = original_particle_position;
  r7.x -= s.x * (1 - s.y / depth) * scale_factor;
  store_uav_typed u0.xyzw, indices, r7;
  ```
- **Application:** Forever Skies bee swarm fix (hash `e463e03746a9d09e`)
- **Key:** Stereo offset applied **before** UAV store, use free register

**Pattern: Billboard particles conforming to terrain**
- **Detection:** Particles using depth buffer for height matching
- **Technique:** Reconstruct world position from depth buffer, apply stereo, re-project
- **Reference:** Green Hell rain particle fix (same depth reconstruction technique)

### Water & Reflections

**Pattern: Planar reflection correction (DX9/DX11)**
- **Formula (Warband):**
  ```hlsl
  r4.xyzw = r1.xyzw / r1.wwww;
  r4.x -= separation * (1 - convergence / v9.w);
  Sample(...);
  ```
- **Why:** Reflect ray direction needs stereo offset to account for eye position shift
- **Application:** Sea map reflections, water surface reflections

**Pattern: Screen-space reflection (SSR)**
- **Detection:** Reflections computed in screen-space, sampling from reflection RT
- **Fix:** Apply stereo in two places:
  1. **RT creation:** `StereoMode=1` on reflections RT (separate stereo state)
  2. **Sampling:** `r1.x += s.x * (1 - s.y/v4.w) * 0.5` in PS

### Dynamic Crosshairs & Cursors

**Pattern: World-space crosshair (DX9)**
- **Detection:** Crosshair positioned in 3D space, affected by camera perspective
- **Method:** Vertex shader correction using `filter_index=15`, texture hash matching
- **Formula:** Apply stereo offset in VS based on world position depth
- **Reference:** Warband dynamic crosshair (hash `c8f40aa4b021e340`)

**Pattern: Screen-space cursor**
- **Detection:** Always centered or at mouse position, orthographic projection
- **Fix:** `o3.w=0` (invisible) when at convergence point; apply stereo offset when away
- **Conditional:** Only correct when `adjust_from_depth_buffer != 0`
- **Reference:** Kingdom Come HUD crosshair

## Engine-Specific Techniques

### Constant Buffer (CB) Analysis for FOV Extraction

**Universal Unity FOV Extraction:**
```hlsl
float fov = dot(unity_matrixV.row1, InvViewProj.col0)
```
In DXBC assembly: `mul/mad` sequence using `unity_matrixV[9-12].x` against `InvViewProj[0]`

**FOV Rule of Thumb:**
- Column magnitude **~1.0** = pure orthogonal View matrix → not usable for FOV
- Column magnitude **≠ 1.0** = projection mixed in → usable for FOV extraction

**VP vs. Pure View identification:**
- If VP (ViewProjection) in MatrixV slot: column magnitude includes projection scaling
- If pure View in MatrixV slot: magnitude ~1.0, cannot extract FOV directly
- Test: Check `rsq()` output of column X magnitude; if result << 1.0, has FOV data

**Example CB anatomy (unknown game, hash `4bbbc6c87e3f29f6`):**
```
cb13[20-23] = VP left
cb13[24-27] = pure View (camera right = cb13[24].xyz)
cb13[32-35] = VP right
```

### CryEngine (Kingdom Come: Deliverance)

**nvidia_dx11 + geo-11 Setup:**
- Delete NVIDIA Inspector profile OR zero `StereoMiscFlags` to avoid conflicts
- Use geo-11 build v0.6.60.23 minimum for stable ShaderFixes→ShaderFixesDM
- Depth buffer fetched via shader log + `shaderusage.xml` cross-reference

**Depth Buffer Identification Workflow:**
1. Enable shader logging in d3dxdm.ini
2. Cross-reference `<DepthTarget>` + `<Register>` entries in `shaderusage.xml`
3. Use Python script to extract PS hashes where depth buffer appears in both RT and register
4. Verify slot doesn't conflict (e.g., `ps-t100` is typically safe)

**HUD VS Fix Pattern:**
- Input: `filter_index` + texture hash matching to isolate HUD VS
- Output: Stereo offset applied to world position before projection
- Ellipse/circle zone detection in screen-space for conditional application
- Crosshair invisible when `adj==0` (on convergence plane)

### UE4 Specifics

**Orthographic UI Detection:**
- All HUD elements output `o0.w=1.0` (orthographic)
- Screen-space formula: `screenX = o0.x * 0.5 + 0.5`

**Volumetric/Post-Process Shaders:**
- Apply stereo offset **before** final output scaling
- Normalize screen coordinates to `[-0.5, 0.5]`, apply correction, scale
- Key insight: radial effects (lens flares, vignette) distort if corrected post-scaling

**Forever Skies Table Dirt & Elements:**
- Controlled via `IniParams[90].x` for on/off switching
- Particle fixes require depth-aware stereo offset in compute shaders

## Screen-Space Coordinate Logic

### NDC to Screen Space Conversions

**Clip-space to normalized device coords:**
```hlsl
ndc.x = clipSpace.x / clipSpace.w
screen.x = ndc.x * 0.5 + 0.5  // [-1,1] → [0,1]
pixel.x = screen.x * width
```

**Impossible Condition Detection:**
- Pattern: `o0.x > 0.3 && o0.x < -0.3` is logically impossible
- Root cause: Shader author likely meant different register or logic error
- Fix: Identify intended zone (e.g., left/right halves, center band) and implement correctly

**Clock-Analogy Zone Targeting:**
- Divide screen into zones (12 o'clock, 3 o'clock, etc.) using angle/distance from pixel to reference point
- Apply conditional stereo correction only in specific zones
- Useful for selective HUD or lens flare regions

### Depth Buffer Reconstruction

**World position from depth + screen coords:**
```hlsl
float linearDepth = depth / (farPlane - nearPlane);
float3 worldPos = cameraPos + cameraDir * linearDepth * range;
```

**Reverse-Z linearization (common in modern engines):**
- If depth is reversed (1.0 at near, 0.0 at far): `linearDepth = 1.0 - depth;`
- Verify by checking sample depth values near camera vs. far distance

**Stereo application using reconstructed depth:**
- Reconstruct world position from depth buffer
- Apply stereo offset in world/camera space
- Re-project if needed

## DGVoodoo2 & Compatibility

### Swapchain Configuration

**Key parameters for stereo stability:**
- `dxgi_format` = output format (usually `DXGI_FORMAT_R8G8B8A8_UNORM`)
- `swap_effect=4` = **required for nvidia_dx11 stereo** (flip discard mode)
- `msaa_count` / `msaa_quality` = irrelevant with `swap_effect=4`
- `buffer_count` = 2 (lower latency, sharper) vs. 3 (smoother framing)

**Known issue:** AWOIAF mod + `swap_effect=4` causes hang; workaround: comment out `allow_creat_device=1`

### Shader Logging & Analysis

**Enable detailed logging:**
- Set logging level to capture all shader compiles
- Cross-reference CRC32 hashes against shader log
- Use Notepad++ regex for filtering (e.g., isolate PS hashes with depth buffer)

## Advanced Techniques: Matrix Inversion & Decal Projection

### Inverse Matrix Technique for Decals & Projected Content

**Problem:** Decals/reflections computed in projected space need stereo correction in world/view space

**Solution:** 
1. Create inverse of view-projection matrix via compute shader
2. Unproject clip coords → world coords → apply stereo → reproject

**Pattern (HLSL - pre-inversion):**
```hlsl
// Project world position
mul r30.xyzw, r10.yyyy, cb2[number2].xyzw
mad r30.xyzw, r10.xxxx, cb2[number1].xyzw, r30.xyzw
mad r30.xyzw, r10.zzzz, cb2[number3].xyzw, r30.xyzw
mad r30.xyzw, r10.wwww, cb2[number4].xyzw, r30.xyzw

// Apply stereo correction BEFORE matrix application
r10.x -= stereo.x * (r10.w - stereo.y) * cbuffer1[00].x * 0.5;
```
**Key:** Stereo applied to world/view position **before** projection matrix

**Pattern (Assembly - with inverse matrix):**
```asm
// Transform to world space via inverse matrix
mul tmp1.xyzw, tmp3.yyyy, cb13[1].xyzw
mad tmp1.xyzw, tmp3.xxxx, cb13[0].xyzw, tmp1.xyzw
mad tmp1.xyzw, tmp3.zzzz, cb13[2].xyzw, tmp1.xyzw
mad tmp1.xyzw, tmp3.wwww, cb13[3].xyzw, tmp1.xyzw

// Apply stereo correction in world space
add tmp2.w, tmp1.w, -stereo.y
mul tmp2.w, stereo.x, tmp2.w
mul tmp2.w, tmp2.w, cbuffer1[0].x
div tmp2.w, tmp2.w, l(2.0)
add tmp1.x, tmp1.x, -tmp2.w
```

**Compute shader for inverse matrix generation:**
```ini
[ResourceInvViewMatrix]
type = Buffer
format = R32G32B32A32_FLOAT
array = 4

[CustomShaderInverseMatrix_cb0]
cs = ShaderFixes/inverse-cs-cb0.hlsl
ResourceBackupCSCB0 = ref cs-cb0
ResourceBackupCSU0 = ref cs-u0
cs-cb0 = ResourceInputDecals
cs-u0 = ResourceInvViewMatrix
Dispatch = 1, 1, 1
```

### ShaderRegex Decal Patterns

**Use case:** Apply stereo correction to decals matching specific pattern across multiple shaders

**Pattern recognition example (from ADR1FT):**
```ini
[ShaderRegexDecals1]
shader_model = ps_4_0 ps_5_0
temps = stereo tmp1 tmp2 tmp3
ResourceInputDecals = ref ps-cb0

[ShaderRegexDecals1.Pattern]
mul r\d+\.xy, (?P<variable>v\d+)\.xyxx, (?P<cbuffer1>cb[012])\[(?P<number>\d+)\]\.zwzz\n
\s*sample_l_indexable\(texture2d\)\(float,float,float,float\) r\d+\.x, r\d+\.xyxx, t\d+\.xyzw, s\d+, l\(0\.000000\)\n
\s*mul r\d+\.xyzw, (?P=variable)\.yyyy, (?P<cbuffer2>cb[012])\[(?P<number2>\d+)\]\.xyzw\n
\s*mad r\d+\.xyzw, (?P=variable)\.xxxx, (?P=cbuffer2)\[(?P<number1>\d+)\]\.xyzw, r\d+\.xyzw\n
\s*mad r\d+\.xyzw, r\d+\.xxxx, (?P=cbuffer2)\[(?P<number3>\d+)\]\.xyzw, r\d+\.xyzw\n
\s*add r\d+\.xyzw, r\d+\.xyzw, (?P=cbuffer2)\[(?P<number4>\d+)\]\.xyzw\n
```
**What it matches:** Decals using UV coordinate transformation + texture sampling + matrix projection

**Automatic injection:** Regex replaces matched pattern with stereo-corrected version without manual per-shader editing

### Identifying Stereo Issues

**Symptom: Ghosting or misalignment at specific depths**
- Likely: Missing or wrong depth term in correction formula
- Fix: Add `(1 - s.y/depth)` factor if missing
- Verification: Cycle convergence values; if misalignment changes, depth term is needed

**Symptom: Correct at convergence=0, broken elsewhere**
- Likely: Simple formula lacking convergence awareness
- Fix: Use full formula `s.x * (1 - s.y / depth)` instead of bare `s.x`

**Symptom: HUD shifts relative to world**
- Likely: Wrong depth value (using world depth instead of orthographic 1.0)
- Fix: Confirm HUD output w=1.0, use `o0.x += s.x * (1 - s.y)` without depth divide

### Subnautica Sun Light Correction Example

**Problem:** Sun lighting elements rendered in screen space, appearing at fixed depth

**Pattern:**
```hlsl
r0.xyzw = cb4[1].xyzw * v0.yyyy;
r0.xyzw = cb4[0].xyzw * v0.xxxx + r0.xyzw;
r0.xyzw = cb4[2].xyzw * v0.zzzz + r0.xyzw;
r0.xyzw = cb4[3].xyzw + r0.xyzw;
r1.xyzw = cb5[18].xyzw * r0.yyyy;
r1.xyzw = cb5[17].xyzw * r0.xxxx + r1.xyzw;
r1.xyzw = cb5[19].xyzw * r0.zzzz + r1.xyzw;
r0.xyzw = cb5[20].xyzw * r0.wwww + r1.xyzw;

// Stereo correction AFTER matrix application, using clip-space w as depth
float4 stereo = StereoParams.Load(0);
r0.x -= stereo.x * r0.w * 0.9;  // Multiplier tuned for light responsiveness
```

**Why 0.9 multiplier?** Empirically determined to prevent lights from drifting too much. Can be tuned per-game.

## Correction Placement Guide: Where to Apply the Fix

**Critical principle:** Stereo correction must be applied in the correct coordinate space

**View Space vs. Projection Space:**
- **View space:** `S * (-r.z - C) * P11` — uses Z component
- **Projection space:** `S * (r.w - C)` — uses clip-space W
  - Where: S = separation, C = convergence, P11 = projection matrix (1,1) element, r = source coordinate

**Typical placement contexts:**

| Context | Where to Fix | Formula | Notes |
|---------|-------------|---------|-------|
| Before matrix application | Vertex/pixel shader early | `pos.x -= sep * (pos.w - conv)` | Cleanest; affects downstream |
| After matrix application | Vertex/pixel shader late | `r0.x -= sep * r0.w * scale` | May need to revert w-dependent calcs |
| Texture coordinate fix | Texture sampling | `uv.x += sep * (1 - conv/depth)` | For refraction/parallax mapping |
| Projection space (screen) | Post-projection | `o0.x += sep * (1 - conv/o0.w)` | Standard for post-process |
| View space (camera-relative) | Pre-projection | `r.z -= sep * (r.z - conv) * P11` | Less common; requires P11 extraction |

**Rule of thumb:** If unsure, try before matrix application first. If that doesn't work, try after.

**Subnautica example shows:** Fix **after** final matrix = can use clip-space w directly = `r0.x -= stereo.x * r0.w * scale`

**Using filter_index:**
- Isolate specific shaders by texture hash + filter_index combination
- Apply fix only to matched shader (partner shader technique)
- Common pattern: `filter_index=15` for specific VS in complex materials

**Mono copy technique (DarkStarSword pattern):**
- Copy shader override to a "mono" variant
- Apply only to one eye (test left vs. right eye perception)
- Helps isolate whether issue is in stereo logic or base shader

### Calibration Methodology

**Empirical multiplier tuning:**
1. Apply stereo formula with multiplier = 1.0
2. Cycle through convergence values (0, 10, 20, 30, 50)
3. Adjust multiplier until alignment is correct across all convergence values
4. Use Excel with 20 decimal places for polynomial regression if multi-variable

**Example:** HUD depth multiplier found to be 0.85 after cycling convergence from 0-50

## Tool-Specific Patterns

### 3Dmigoto Shader Override Structure

**Basic pattern:**
```
[PS_HASH]
ps-t0 = Resource(BufferIndex);
o0.x += s.x * (1 - s.y / depth);
run = $active ? 1 : 0;
```

**Advanced filtering:**
- Use `texhash` to match input textures
- Use `indexedtextureoverride` for multi-stage sampling
- Use `registertypematch` to match specific register types

### d3dxdm.ini Auto-Convergence Tuning

**Key parameters:**
- `dm_min_convergence_*` / `dm_max_convergence_*` = bounds for auto-adjust
- `dm_slow_convergence_rate_*` = gradual change rate
- `dm_instant_convergence_threshold_*` = snap threshold
- `dm_anti_judder_threshold_*` = filter micro-adjustments
- Increase `dm_anti_judder_threshold_absolute_override` to reduce jumping

## Reference Examples by Game

### Forever Skies (UE4)
- Volumetric lens flare stereo offset in PS after normalization
- Bee swarm compute shader displacement (hash `e463e03746a9d09e`)
- Billboard terrain-following particles with depth reconstruction
- Table dirt shader control via `IniParams[90].x`

### Kingdom Come: Deliverance (CryEngine)
- Depth buffer identification via `shaderusage.xml`
- HUD VS fix with `filter_index` and ellipse zone detection
- Decal PS correction: `r2.x -= s.x * (1 - s.y / r0.y)` for convergence-aware fix
- Crosshair invisible when on convergence plane

### Mount & Blade: Warband (Custom DX9)
- Dynamic crosshair VS correction (hash `c8f40aa4b021e340`)
- Cloud reflection PS fix (texture hashes `edb05325`/`6be69621`)
- Water planar reflection: `r4.x -= separation * (1 - convergence / v9.w)`
- Halos and HUD elements with PNG mask sampling
- DGVoodoo2 with `swap_effect=4`; AWOIAF mod incompatibility workaround

### Death's Door (Unity isometric)
- Scale factor compensation: `SCALE_FACTOR=39` for unit scaling
- Camera right extraction: `camright = float3(cb3[9].x, cb3[10].x, cb3[11].x)`
- Ice reflection VS fix with convergence scaling
- SSR with separate RT `StereoMode=1` + PS sampling correction

### Snow Footprint Decals (Unity projected)
- Reciprocal depth in clip-space w: `r0.w = 1/depth`
- Convergence-invariant formula: `r0.x -= s.x * (1.0 - s.y * r0.w) * 1.02999938`
- Applied pre-perspective divide in clip-space
- Calibration factor `1.02999938` determined empirically for game unit scale
- Verified across full convergence range (-10cm to +10cm)

---

## Quick Lookup Table

| Problem | Formula | When to Use |
|---------|---------|------------|
| Screen-space shift | `o0.x += s.x * (1 - s.y/depth)` | General case, depth-aware |
| HUD orthographic | `o0.x += s.x * (1 - s.y)` | w=1.0 HUD elements |
| Simple decal | `r2.x -= s.x` | Decal at convergence=0 |
| Decal + convergence | `r2.x -= s.x * (1 - s.y/r0.y)` | Convergence ≠ 0 |
| **Unity decal (reciprocal w)** | **`r0.x -= s.x * (1.0 - s.y * r0.w) * factor`** | **Unity clip-space (r0.w = 1/depth)** |
| Lens flare volumetric | `r0.x -= s.x * (1 - s.y/v3.w) * 0.5` | Post-normalization |
| Reflection ray | `r4.x -= sep * (1 - conv/v9.w)` | Planar reflection |
| Particle/UAV | Stereo offset before `store_uav_typed` | Compute shader displacement |
| Depth-masked | `corr * smoothstep(near, far, depth)` | Layered HUD/elements |

---

## Notes for Debugging

- **Always verify w-value context:** Is it clip-space w (depth)? Or orthographic 1.0? Or something else?
- **Test convergence sweep:** Apply fix at convergence 0, 20, 50. If alignment drifts, depth term needed.
- **Use mono copy:** Test left/right eye separately to isolate left-eye-only vs. both-eyes issues.
- **Log shader hashes:** Keep running log of all shader hashes you fix; patterns often repeat across games/engines.
- **Depth buffer slot conflicts:** Always verify chosen register slot doesn't conflict with existing game use.
- **Screen-space vs. world-space:** Be clear which space correction is applied in; mixing causes subtle misalignment.
