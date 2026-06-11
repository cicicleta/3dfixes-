# Stereo 3D Shader Hacking Skills & Documentation

Comprehensive pattern recognition and technique documentation for stereoscopic 3D shader fixes across PC games.

## 📚 Contents

### Main Skill Document
- **[stereo-3d-shader-hacking-SKILL.md](./stereo-3d-shader-hacking-SKILL.md)**
  - Core stereo correction formulas
  - Pattern recognition by element type (HUD, decals, particles, water, reflections)
  - Engine-specific techniques (UE4, Unity, CryEngine, DX9)
  - Constant buffer analysis for FOV extraction
  - Calibration methodology
  - Quick lookup table with formulas

### Supplementary Documentation
- **[unity_decal_reciprocal_depth_stereo.md](./unity_decal_reciprocal_depth_stereo.md)**
  - Detailed technique: Unity decals with reciprocal depth (1/z)
  - Mathematical explanation
  - Implementation example
  - Calibration data

## 🎮 Covered Games & Techniques

### By Engine
- **UE4:** Lens flares, volumetric effects, particles, SSR
- **Unity:** Isometric games, reciprocal depth decals
- **CryEngine:** Kingdom Come Deliverance - HUD, depth buffer, auto-convergence
- **Custom DX9:** Mount & Blade Warband - water reflections, crosshairs
- **DGVoodoo2:** Game Cube emulation via Dolphin

### By Element Type
- HUD & UI orthographic/depth-based
- Decals & projected textures (simple, convergence-aware, reciprocal depth)
- Lens flares & volumetric effects
- Particles & compute shaders
- Water & planar reflections
- Screen-space reflections (SSR)
- Dynamic crosshairs & cursors
- Outline shaders

## 🔧 Key Formulas at a Glance

| Element | Formula | Notes |
|---------|---------|-------|
| Screen-space shift | `o0.x += s.x * (1 - s.y/depth)` | General case, depth-aware |
| HUD orthographic | `o0.x += s.x * (1 - s.y)` | w=1.0 elements |
| Decal (convergence=0) | `r2.x -= s.x` | Simple case |
| Decal (convergence≠0) | `r2.x -= s.x * (1 - s.y/r0.y)` | Full compensation |
| **Unity decal (reciprocal w)** | **`r0.x -= s.x * (1.0 - s.y * r0.w) * factor`** | **r0.w = 1/depth** |
| Lens flare volumetric | `r0.x -= s.x * (1 - s.y/v3.w) * 0.5` | Post-normalization |
| Reflection ray | `r4.x -= sep * (1 - conv/v9.w)` | Planar reflection |

## 📖 How to Use This Skill

1. **For debugging stereo issues:** Consult the Pattern Recognition section to identify your element type
2. **For new games:** Check Reference Examples section for similar engines/techniques
3. **For calibration:** Follow the Calibration Methodology section with Excel regression
4. **For implementation:** Use the Quick Lookup Table to find the right formula
5. **For convergence-invariant fixes:** Use formulas with `(1 - s.y/depth)` or `(1 - s.y * r0.w)` factors

## 🔗 External References

- **3Dmigoto:** https://github.com/DarkStarSword/3Dmigoto
- **geo-11:** https://github.com/illusion0001/geo-11
- **DGVoodoo2:** http://dege.freeweb.hu/dgvoodoo2/

## 📝 Notes

- All formulas use `StereoParams.Load(0)` convention: `s.x` = separation, `s.y` = convergence
- Timing of correction (before/after matrix application) is critical
- Calibration factors are game/engine specific; 20 decimal places recommended for polynomial regression
- Test convergence sweep (-10cm to +10cm) to validate convergence-invariant fixes

---

**Last Updated:** 10 Jun 2026  
**Author:** Cicicleta  
**Status:** Active documentation, continuously updated
