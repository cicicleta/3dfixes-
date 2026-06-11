# Unity Decals Proyectados con Profundidad Recíproca
## Corrección Estéreo Convergence-Invariant

**Fecha:** 10 Jun 2026  
**Aplicación:** Huellas de nieve (Snow Footprints Decal)  
**Motor:** Unity  
**Estado:** Verificado (funciona con cualquier convergencia)

---

## Resumen

Corrección estéreo para decals proyectados en shaders Unity que usan profundidad recíproca (`1/z`) en lugar de profundidad lineal. La técnica es **invariante a convergencia** porque el factor de corrección es dinámico respecto a la profundidad.

---

## Contexto: ¿Por qué Reciprocal Depth?

Los engines modernos (Unity, UE4) optimizan la precisión del Z-buffer usando profundidad recíproca:
- En lugar de guardar `z` directamente
- Guardan `1/z` (reciprocal)
- Esto mejora distribución de precisión en profundidad

En el clip-space post-proyección:
- `r0.w` = `1/depth` (no `-depth`)
- Las matrices de proyección (`cb0[80-83]`) ya contienen esta transformación

---

## Fórmula Clásica vs Reciprocal

### Fórmula Clásica (profundidad lineal):
```glsl
offset = separation * (1 - convergence / depth)
```

### Reescrita (usando reciprocal):
```glsl
offset = separation * (1 - convergence * reciprocal_depth)
```

**Donde:**
- `reciprocal_depth = 1 / depth = r0.w`
- `convergence = s.y`
- `separation = s.x`

### En HLSL (Unity):
```hlsl
r0.x -= s.x * (1.0 - s.y * r0.w) * calibration_factor;
```

---

## Implementación Completa

**Shader context:** Decal de nieve proyectado, muestreo de heightmap + color + normales.

```hlsl
// [Proyección perspectiva del decal]
r0.xy = cb0[120].zw * v0.xy;
r0.xy = r0.xy * float2(2,2) + float2(-1,-1);
r1.xyzw = cb0[81].xyzw * -r0.yyyy;
r0.xyzw = cb0[80].xyzw * r0.xxxx + r1.xyzw;

// [Muestreo de alturas]
r1.xy = (uint2)v0.xy;
r1.zw = float2(0,0);
r1.x = t2.Load(r1.xyz).x;
r0.xyzw = cb0[82].xyzw * r1.xxxx + r0.xyzw;
r0.xyzw = cb0[83].xyzw + r0.xyzw;

// ========== CORRECCIÓN ESTÉREO ==========
// Aplicar ANTES de división perspectiva (/r0.www)
// Formula: offset = sep * (1 - conv * reciprocal_depth) * calibration
float4 s = StereoParams.Load(0);
r0.x -= s.x * (1.0 - s.y * r0.w) * 1.02999938;
// ========================================

// [Perspectiva divide y resto del shader]
r0.xyz = r0.xyz / r0.www;
r1.xyz = cb1[5].xyz * r0.yyy;
r0.xyw = cb1[4].xyz * r0.xxx + r1.xyz;
r0.xyz = cb1[6].xyz * r0.zzz + r0.xyw;
r0.xyz = cb1[7].xyz + r0.xyz;

// [Construcción de normales, sampleo de texturas, outputs...]
```

---

## Puntos Clave

### 1. **Timing Crítico**
- Aplicar corrección **ANTES** de `/r0.www`
- Esto es clip-space pre-divide
- Después no funciona (coordenadas ya normalizadas)

### 2. **Invariancia a Convergencia**
```
Convergencia=0 cm:     s.y=0     → (1 - 0*depth) = 1     → corrección base
Convergencia=+5 cm:    s.y≠0     → (1 - s.y*depth) varía → corrección escalada
Convergencia=-5 cm:    s.y≠0     → (1 - s.y*depth) varía → corrección escalada
```
El factor `(1.0 - s.y * r0.w)` ajusta automáticamente según profundidad Y convergencia.

### 3. **Factor de Calibración**
- Base teórica: `1.0`
- Empiricamente calibrado: `1.02999938`
- Varía por:
  - Escala de unidades del juego
  - Rango de profundidades del decal
  - Geometría de proyección específica

**Metodología de calibración:**
1. Fijar convergencia en valor de prueba (ej: 0 cm)
2. Ajustar factor hasta que profundidad se alinee visualmente
3. Probar en múltiples convergencias (debe no variar)
4. Iterar si oscila en rangos de convergencia

### 4. **Profundidad Recíproca**
Confirmado por presencia de `rsqrt()` u otros indicadores en el shader:
```hlsl
r0.w = rsqrt(r0.w);  // normalized (reciprocal sqrt)
r0.w = 1.0 / r0.w;   // invert to get 1/z
```

---

## Validación

✅ **Funciona con cualquier convergencia:**
- Rango de prueba: -10 cm a +10 cm
- Comportamiento consistente
- Sin oscilación ni divergencia

✅ **Aplicable a:**
- Decals proyectados en clip-space
- Shaders que usan profundidad recíproca post-matriz
- Unity (y posiblemente UE4 con variantes)

---

## Notas Técnicas

### ¿Por qué `s.y * r0.w` y no `s.y / r0.w`?
Porque `r0.w = 1/depth`. Entonces:
- `s.y * (1/depth)` = `s.y / depth` ✓
- Es la misma fórmula, solo con reciprocal ya pre-calculado

### ¿Qué pasa si r0.w es negativo?
En algunos engines (reversed-Z):
- Puede ser que `r0.w < 0`
- Probar con `abs()` o ajustar signo del factor

### Alternativas (si esto no funciona):
1. Probar `r0.x -= s.x * (1.0 - s.y / r0.w) * factor` (división clásica)
2. Usar profundidad del heightmap muestreado (`r1.x`) como referencia
3. Investigar si hay compute shader donde se calcula profundidad lineal

---

## Referencias Relacionadas

- **Base estéreo clásica:** `r0.x -= s.x * (1 - s.y / depth)`
- **Variante clip-space pre-divide:** Este documento
- **Aplicaciones previas:** 
  - Death's Door (Unity isometric): ice reflection VS fix
  - Forever Skies (UE4): lens flare volumetric PS fix
  - Mount & Blade: Warband (CryEngine): water planar reflection

---

## Histórico de Calibración

| Convergencia | Factor | Status | Notas |
|---|---|---|---|
| 0 cm | 1.02999938 | ✓ | Base de calibración |
| +5 cm | 1.02999938 | ✓ | Consistente |
| -5 cm | 1.02999938 | ✓ | Consistente |
| Rango completo | 1.02999938 | ✓ | Invariante comprobado |

---

**Última actualización:** 10 Jun 2026  
**Autor:** Cicicleta  
**Estado:** Documentado y verificado
