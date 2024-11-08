// Spot lights (in cave after loading game before diver swims into view)

// ---- Created with 3Dmigoto v1.2.51 on Sat Dec 24 06:45:42 2016
Texture2D<float4> t7 : register(t7);

Texture2D<float4> t6 : register(t6);

Texture2D<float4> t5 : register(t5);

Texture2D<float4> t4 : register(t4);

Texture2D<float4> t3 : register(t3);

Texture2D<float4> t2 : register(t2);

Texture2D<float4> t1 : register(t1);

Texture2D<float4> t0 : register(t0);

SamplerState s7_s : register(s7);

SamplerState s6_s : register(s6);

SamplerState s5_s : register(s5);

SamplerState s4_s : register(s4);

SamplerState s3_s : register(s3);

SamplerState s2_s : register(s2);

SamplerState s1_s : register(s1);

SamplerState s0_s : register(s0);

cbuffer cb2 : register(b2)
{
  float4 cb2[7];
}

cbuffer cb1 : register(b1)
{
  float4 cb1[33];
}

cbuffer cb0 : register(b0)
{
  float4 cb0[54];
}




// 3Dmigoto declarations
#define cmp -
Texture1D<float4> IniParams : register(t120);
Texture2D<float4> StereoParams : register(t125);

#include "matrix.hlsl"

void main( 
  float4 v0 : TEXCOORD0,
  float4 v1 : SV_POSITION0,
  out float4 o0 : SV_Target0)
{
  float4 r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14;
  uint4 bitmask, uiDest;
  float4 fDest;

  r0.xy = v0.xy / v0.ww;
  r0.zw = r0.xy * cb0[52].xy + cb0[52].wz;
  r1.xyzw = t1.SampleLevel(s1_s, r0.zw, 0).xzyw;
  r1.w = 255 * r1.w;
  r1.w = round(r1.w);
  r1.w = (uint)r1.w;
  r2.x = (int)r1.w & 15;
  if (r2.x != 0) {
    r2.yzw = t0.SampleLevel(s0_s, r0.zw, 0).xyz;
    r2.yzw = r2.yzw * float3(2,2,2) + float3(-1,-1,-1);
    r3.x = dot(r2.yzw, r2.yzw);
    r3.x = rsqrt(r3.x);
    r2.yzw = r3.xxx * r2.yzw;
    r3.x = t4.SampleLevel(s4_s, r0.zw, 0).x;
    r3.x = r3.x * cb0[51].z + -cb0[51].w;
    r3.x = 1 / r3.x;
    r0.xy = r3.xx * r0.xy;

// Lights:
float4 s = StereoParams.Load(0);
r0.x -= s.x * (r3.x - s.y);

    r4.xyzw = cb0[41].xyzw * r0.yyyy;
    r4.xyzw = r0.xxxx * cb0[40].xyzw + r4.xyzw;
    r3.xyzw = r3.xxxx * cb0[42].xyzw + r4.xyzw;
    r3.xyzw = cb0[43].xyzw + r3.xyzw;
    r3.xyz = r3.xyz / r3.www;
    r4.xyz = -cb0[53].xyz + r3.xyz;

// Specular:
r4.xyz -= mul(float4(s.x * s.y, 0, 0, 0), MATRIX(cb0, 40)).xyz;

    r0.x = dot(r4.xyz, r4.xyz);
    r0.x = rsqrt(r0.x);
    r4.xyz = r4.xyz * r0.xxx;
    r0.x = t5.SampleLevel(s5_s, r0.zw, 0).z;
    r0.x = r0.x * r0.x;
    r5.xyz = cb2[0].xyz + -r3.xyz;
    r0.y = dot(r5.xyz, r5.xyz);
    r0.y = rsqrt(r0.y);
    r6.xyz = r5.xyz * r0.yyy;
    r3.w = saturate(dot(r2.yzw, r6.xyz));
    r7.xyz = cb2[0].www * r5.xyz;
    r4.w = dot(r7.xyz, r7.xyz);
    r4.w = min(1, r4.w);
    r4.w = 1 + -r4.w;
    r4.w = log2(r4.w);
    r4.w = cb2[1].w * r4.w;
    r4.w = exp2(r4.w);
    r5.w = dot(r6.xyz, cb2[2].xyz);
    r5.w = -cb2[3].x + r5.w;
    r5.w = saturate(cb2[3].y * r5.w);
    r5.w = r5.w * r5.w;
    r6.x = cmp(0 < r4.w);
    r6.y = cmp(0 < r5.w);
    r6.x = r6.y ? r6.x : 0;
    if (r6.x != 0) {
      r6.xyz = t2.SampleLevel(s2_s, r0.zw, 0).xyz;
      r7.xyzw = t3.SampleLevel(s3_s, r0.zw, 0).xyzw;
      r8.xy = cb1[3].xy * r0.zw;
      r8.xy = (uint2)r8.xy;
      r8.z = (uint)cb1[32].x;
      r8.x = (int)r8.x + (int)r8.y;
      r8.x = (int)r8.x + (int)r8.z;
      r8.x = (int)r8.x & 1;
      r8.y = (int)r1.w & 16;
      r7.xyzw = r8.yyyy ? float4(0,0,0,0) : r7.xyzw;
      r8.y = cmp((int)r2.x == 5);
      r9.xyzw = r8.xxxx ? float4(1,1,1,0) : float4(0,0,0,1);
      r6.w = r1.z;
      r6.xyzw = r8.yyyy ? r9.xyzw : r6.xyzw;
      r8.xyz = -r6.xyz * r1.xxx + r6.xyz;
      r8.w = 0.0799999982 * r6.w;
      r6.xyz = -r6.www * float3(0.0799999982,0.0799999982,0.0799999982) + r6.xyz;
      r6.xyz = r1.xxx * r6.xyz + r8.www;
      r8.xyz = r8.xyz * cb1[5].www + cb1[5].xyz;
      r6.xyz = r6.xyz * cb1[6].www + cb1[6].xyz;
      if (cb2[6].x != 0) {
        r9.xy = (int2)r1.ww & int2(32,64);
        r1.w = r9.y ? 0 : 1;
        r1.w = r9.x ? r1.w : 1;
        r6.w = dot(cb2[5].xyzw, float4(1,1,1,1));
        r1.w = dot(r1.wwww, cb2[5].xyzw);
        r1.w = -1 + r1.w;
        r1.w = r6.w * r1.w + 1;
        r0.x = r1.w * r0.x;
      } else {
        r0.x = t6.SampleLevel(s6_s, r0.zw, 0).x;
      }
      r0.z = r5.w * r4.w;
      r0.x = r0.z * r0.x;
      r1.x = r7.y;
      r1.z = 1;
      r1.xyz = max(cb2[4].xxx, r1.xyz);
      r9.xyz = r1.xyz * r1.xyz;
      r0.z = dot(r4.xyz, r2.yzw);
      r0.z = r0.z + r0.z;
      r10.xyz = r2.yzw * -r0.zzz + r4.xyz;
      r0.zw = cmp(float2(0,0) < cb2[3].wz);
      if (r0.z != 0) {
        r0.z = cb2[3].w * r0.y;
        r0.z = min(1, r0.z);
        r11.xyz = r0.zzz * float3(0.5,0.5,0.5) + r9.xyz;
        r11.xyz = min(float3(1,1,1), r11.xyz);
        r11.xyz = r9.xyz / r11.xyz;
        r12.xyz = cb2[3].www * cb2[2].xyz;
        r13.xyz = -r12.xyz * float3(0.5,0.5,0.5) + r5.xyz;
        r0.z = dot(r10.xyz, r12.xyz);
        r14.xyz = r0.zzz * r10.xyz + -r12.xyz;
        r1.z = dot(r13.xyz, r14.xyz);
        r0.z = r0.z * r0.z;
        r0.z = cb2[3].w * cb2[3].w + -r0.z;
        r0.z = saturate(r1.z / r0.z);
        r5.xyz = r0.zzz * r12.xyz + r13.xyz;
      } else {
        r11.xyz = float3(1,1,1);
      }
      if (r0.w != 0) {
        r0.y = cb2[3].z * r0.y;
        r0.y = min(1, r0.y);
        r0.yzw = r0.yyy * float3(0.5,0.5,0.5) + r9.xyz;
        r0.yzw = min(float3(1,1,1), r0.yzw);
        r0.yzw = r9.xyz / r0.yzw;
        r0.yzw = r0.yzw * r0.yzw;
        r11.xyz = r11.xyz * r0.yzw;
        r0.y = dot(r5.xyz, r10.xyz);
        r0.yzw = r0.yyy * r10.xyz + -r5.xyz;
        r1.z = dot(r0.yzw, r0.yzw);
        r1.z = rsqrt(r1.z);
        r1.z = cb2[3].z * r1.z;
        r1.z = min(1, r1.z);
        r5.xyz = r0.yzw * r1.zzz + r5.xyz;
      }
      r0.y = dot(r5.xyz, r5.xyz);
      r0.y = rsqrt(r0.y);
      r9.xyz = r5.xyz * r0.yyy;
      switch (r2.x) {
        case 1 :        case 2 :        case 3 :        case 5 :        case 6 :        r12.xyz = r11.zzz * r8.xyz;
        r10.xyz = float3(0.318309873,0.318309873,0.318309873) * r12.xyz;
        break;
        case 4 :        r12.xyz = r5.xyz * r0.yyy + -r4.xyz;
        r0.z = dot(r12.xyz, r12.xyz);
        r0.z = rsqrt(r0.z);
        r12.xyz = r12.xyz * r0.zzz;
        r0.z = saturate(dot(r2.yzw, r9.xyz));
        r0.w = dot(r2.yzw, -r4.xyz);
        r0.w = max(9.99999975e-006, r0.w);
        r1.z = saturate(dot(r2.yzw, r12.xyz));
        r1.w = saturate(dot(-r4.xyz, r12.xyz));
        r12.xy = r1.xy * r1.xy;
        r12.xz = r12.xy * r12.xy;
        r13.xy = r1.zz * r12.xz + -r1.zz;
        r13.xy = r13.xy * r1.zz + float2(1,1);
        r13.xy = r13.xy * r13.xy;
        r13.xy = float2(3.14159274,3.14159274) * r13.xy;
        r12.xz = r12.xz / r13.xy;
        r1.z = r12.x * r11.x;
        r4.w = r1.w * r1.w;
        r4.w = r4.w * 4 + 9.99999975e-006;
        r4.w = rcp(r4.w);
        r1.w = 1 + -r1.w;
        r5.w = r1.w * r1.w;
        r5.w = r5.w * r5.w;
        r6.w = r5.w * r1.w;
        r1.w = -r5.w * r1.w + 1;
        r5.w = r1.w * 0.0399999991 + r6.w;
        r8.w = r5.w * r7.x;
        r1.z = r4.w * r1.z;
        r4.w = -r5.w * r7.x + 1;
        r5.w = r12.z * r11.y;
        r9.w = 0.5 * r12.y;
        r10.w = -r12.y * 0.5 + 1;
        r0.w = r0.w * r10.w + r9.w;
        r0.z = r0.z * r10.w + r9.w;
        r0.z = r0.w * r0.z;
        r0.z = 0.25 / r0.z;
        r0.w = saturate(50 * r6.y);
        r12.xyz = r1.www * r6.xyz;
        r12.xyz = r0.www * r6.www + r12.xyz;
        r13.xyz = r11.zzz * r8.xyz;
        r0.z = r5.w * r0.z;
        r12.xyz = r0.zzz * r12.xyz;
        r12.xyz = r13.xyz * float3(0.318309873,0.318309873,0.318309873) + r12.xyz;
        r12.xyz = r12.xyz * r4.www;
        r10.xyz = r1.zzz * r8.www + r12.xyz;
        break;
        case 8 :        r12.xyzw = saturate(r7.xyzw);
        r13.xyz = r5.xyz * r0.yyy + -r4.xyz;
        r0.z = dot(r13.xyz, r13.xyz);
        r0.z = rsqrt(r0.z);
        r13.xyz = r13.xyz * r0.zzz;
        r0.z = saturate(dot(r2.yzw, r9.xyz));
        r0.w = dot(r2.yzw, -r4.xyz);
        r0.w = max(9.99999975e-006, r0.w);
        r1.z = saturate(dot(r2.yzw, r13.xyz));
        r1.w = saturate(dot(-r4.xyz, r13.xyz));
        r13.xyz = r11.zzz * r8.xyz;
        r1.w = 1 + -r1.w;
        r4.w = r1.w * r1.w;
        r4.w = r4.w * r4.w;
        r5.w = r4.w * r1.w;
        r6.w = 50 * r12.y;
        r6.w = min(1, r6.w);
        r1.w = -r4.w * r1.w + 1;
        r12.xyz = r1.www * r12.xyz;
        r12.xyz = r6.www * r5.www + r12.xyz;
        r4.w = r1.y * r1.y;
        r6.w = r4.w * r4.w;
        r8.w = -r6.w * r1.z + r1.z;
        r8.w = r8.w * r1.z + r6.w;
        r9.w = 4 * r6.w;
        r10.w = r6.w * 4 + 1;
        r10.w = 3.14159274 * r10.w;
        r10.w = rcp(r10.w);
        r9.w = r9.w * r6.w;
        r8.w = r8.w * r8.w;
        r8.w = r9.w / r8.w;
        r8.w = 1 + r8.w;
        r8.w = r10.w * r8.w;
        r9.w = r0.z + r0.w;
        r9.w = -r0.z * r0.w + r9.w;
        r9.w = 4 * r9.w;
        r9.w = rcp(r9.w);
        r8.w = r9.w * r8.w;
        r9.w = saturate(50 * r6.y);
        r14.xyz = r1.www * r6.xyz;
        r14.xyz = r9.www * r5.www + r14.xyz;
        r1.w = r6.w * r1.z + -r1.z;
        r1.z = r1.w * r1.z + 1;
        r1.z = r1.z * r1.z;
        r1.z = 3.14159274 * r1.z;
        r1.z = r6.w / r1.z;
        r1.z = r1.z * r11.y;
        r1.w = -r1.y * r1.y + 1;
        r5.w = r0.w * r1.w + r4.w;
        r1.w = r0.z * r1.w + r4.w;
        r0.w = r1.w * r0.w;
        r0.z = r0.z * r5.w + r0.w;
        r0.z = rcp(r0.z);
        r0.z = r1.z * r0.z;
        r0.z = 0.5 * r0.z;
        r14.xyz = r0.zzz * r14.xyz;
        r12.xyz = r8.www * r12.xyz + -r14.xyz;
        r12.xyz = r12.www * r12.xyz + r14.xyz;
        r10.xyz = r13.xyz * float3(0.318309873,0.318309873,0.318309873) + r12.xyz;
        break;
        case 9 :        r12.xyz = r5.xyz * r0.yyy + -r4.xyz;
        r0.z = dot(r12.xyz, r12.xyz);
        r0.z = rsqrt(r0.z);
        r12.xyz = r12.xyz * r0.zzz;
        r0.z = saturate(dot(r2.yzw, r9.xyz));
        r0.w = dot(r2.yzw, -r4.xyz);
        r0.w = max(9.99999975e-006, r0.w);
        r1.z = saturate(dot(r2.yzw, r12.xyz));
        r1.w = saturate(dot(-r4.xyz, r12.xyz));
        r4.w = r1.y * r1.y;
        r5.w = r4.w * r4.w;
        r6.w = r1.z * r5.w + -r1.z;
        r1.z = r6.w * r1.z + 1;
        r1.z = r1.z * r1.z;
        r1.z = 3.14159274 * r1.z;
        r1.z = r5.w / r1.z;
        r1.z = r1.z * r11.y;
        r5.w = -r1.y * r1.y + 1;
        r6.w = r0.w * r5.w + r4.w;
        r4.w = r0.z * r5.w + r4.w;
        r0.w = r4.w * r0.w;
        r0.z = r0.z * r6.w + r0.w;
        r0.z = rcp(r0.z);
        r0.z = r1.z * r0.z;
        r0.w = 1 + -r1.w;
        r1.z = r0.w * r0.w;
        r1.z = r1.z * r1.z;
        r1.w = r1.z * r0.w;
        r4.w = saturate(50 * r6.y);
        r0.w = -r1.z * r0.w + 1;
        r12.xyz = r0.www * r6.xyz;
        r12.xyz = r4.www * r1.www + r12.xyz;
        r0.z = 0.5 * r0.z;
        r10.xyz = r0.zzz * r12.xyz;
        break;
        default :
        r10.xyz = float3(0,0,0);
        break;
      }
      switch (r2.x) {
        case 1 :        case 2 :        case 3 :        case 5 :        case 6 :        r13.xyz = r5.xyz * r0.yyy + -r4.xyz;
        r0.z = dot(r13.xyz, r13.xyz);
        r0.z = rsqrt(r0.z);
        r13.xyz = r13.xyz * r0.zzz;
        r0.z = saturate(dot(r2.yzw, r9.xyz));
        r0.w = dot(r2.yzw, -r4.xyz);
        r0.w = max(9.99999975e-006, r0.w);
        r1.z = saturate(dot(r2.yzw, r13.xyz));
        r1.w = saturate(dot(-r4.xyz, r13.xyz));
        r2.x = r1.y * r1.y;
        r4.w = r2.x * r2.x;
        r5.w = r1.z * r4.w + -r1.z;
        r1.z = r5.w * r1.z + 1;
        r1.z = r1.z * r1.z;
        r1.z = 3.14159274 * r1.z;
        r1.z = r4.w / r1.z;
        r1.z = r1.z * r11.y;
        r4.w = -r1.y * r1.y + 1;
        r5.w = r0.w * r4.w + r2.x;
        r2.x = r0.z * r4.w + r2.x;
        r0.w = r2.x * r0.w;
        r0.z = r0.z * r5.w + r0.w;
        r0.z = rcp(r0.z);
        r0.z = r1.z * r0.z;
        r0.w = 1 + -r1.w;
        r1.z = r0.w * r0.w;
        r1.z = r1.z * r1.z;
        r1.w = r1.z * r0.w;
        r2.x = saturate(50 * r6.y);
        r0.w = -r1.z * r0.w + 1;
        r13.xyz = r0.www * r6.xyz;
        r13.xyz = r2.xxx * r1.www + r13.xyz;
        r0.z = 0.5 * r0.z;
        r12.xyz = r0.zzz * r13.xyz;
        break;
        case 4 :        r13.xyz = r5.xyz * r0.yyy + -r4.xyz;
        r0.z = dot(r13.xyz, r13.xyz);
        r0.z = rsqrt(r0.z);
        r13.xyz = r13.xyz * r0.zzz;
        r0.z = saturate(dot(r2.yzw, r9.xyz));
        r0.w = dot(r2.yzw, -r4.xyz);
        r0.w = max(9.99999975e-006, r0.w);
        r1.z = saturate(dot(r2.yzw, r13.xyz));
        r1.w = saturate(dot(-r4.xyz, r13.xyz));
        r13.xy = r1.xy * r1.xy;
        r13.xz = r13.xy * r13.xy;
        r14.xy = r1.zz * r13.xz + -r1.zz;
        r1.xz = r14.xy * r1.zz + float2(1,1);
        r1.xz = r1.xz * r1.xz;
        r1.xz = float2(3.14159274,3.14159274) * r1.xz;
        r1.xz = r13.xz / r1.xz;
        r1.xz = r1.xz * r11.xy;
        r2.x = r1.w * r1.w;
        r2.x = r2.x * 4 + 9.99999975e-006;
        r2.x = rcp(r2.x);
        r1.w = 1 + -r1.w;
        r4.w = r1.w * r1.w;
        r4.w = r4.w * r4.w;
        r5.w = r4.w * r1.w;
        r1.w = -r4.w * r1.w + 1;
        r4.w = r1.w * 0.0399999991 + r5.w;
        r6.w = r4.w * r7.x;
        r1.x = r2.x * r1.x;
        r2.x = -r4.w * r7.x + 1;
        r4.w = 0.5 * r13.y;
        r8.w = -r13.y * 0.5 + 1;
        r0.w = r0.w * r8.w + r4.w;
        r0.z = r0.z * r8.w + r4.w;
        r0.z = r0.w * r0.z;
        r0.z = 0.25 / r0.z;
        r0.w = saturate(50 * r6.y);
        r13.xyz = r1.www * r6.xyz;
        r13.xyz = r0.www * r5.www + r13.xyz;
        r14.xyz = r11.zzz * r8.xyz;
        r0.z = r1.z * r0.z;
        r13.xyz = r0.zzz * r13.xyz;
        r13.xyz = r14.xyz * float3(0.318309873,0.318309873,0.318309873) + r13.xyz;
        r13.xyz = r13.xyz * r2.xxx;
        r12.xyz = r1.xxx * r6.www + r13.xyz;
        break;
        case 8 :        r7.xyzw = saturate(r7.xyzw);
        r1.xzw = r5.xyz * r0.yyy + -r4.xyz;
        r0.z = dot(r1.xzw, r1.xzw);
        r0.z = rsqrt(r0.z);
        r1.xzw = r1.xzw * r0.zzz;
        r0.z = saturate(dot(r2.yzw, r9.xyz));
        r0.w = dot(r2.yzw, -r4.xyz);
        r0.w = max(9.99999975e-006, r0.w);
        r2.x = saturate(dot(r2.yzw, r1.xzw));
        r1.x = saturate(dot(-r4.xyz, r1.xzw));
        r8.xyz = r11.zzz * r8.xyz;
        r1.x = 1 + -r1.x;
        r1.z = r1.x * r1.x;
        r1.z = r1.z * r1.z;
        r1.w = r1.z * r1.x;
        r4.w = 50 * r7.y;
        r4.w = min(1, r4.w);
        r1.x = -r1.z * r1.x + 1;
        r7.xyz = r1.xxx * r7.xyz;
        r7.xyz = r4.www * r1.www + r7.xyz;
        r1.z = r1.y * r1.y;
        r4.w = r1.z * r1.z;
        r5.w = -r4.w * r2.x + r2.x;
        r5.w = r5.w * r2.x + r4.w;
        r6.w = 4 * r4.w;
        r8.w = r4.w * 4 + 1;
        r8.w = 3.14159274 * r8.w;
        r8.w = rcp(r8.w);
        r6.w = r6.w * r4.w;
        r5.w = r5.w * r5.w;
        r5.w = r6.w / r5.w;
        r5.w = 1 + r5.w;
        r5.w = r8.w * r5.w;
        r6.w = r0.z + r0.w;
        r6.w = -r0.z * r0.w + r6.w;
        r6.w = 4 * r6.w;
        r6.w = rcp(r6.w);
        r5.w = r6.w * r5.w;
        r6.w = saturate(50 * r6.y);
        r11.xzw = r1.xxx * r6.xyz;
        r11.xzw = r6.www * r1.www + r11.xzw;
        r1.x = r4.w * r2.x + -r2.x;
        r1.x = r1.x * r2.x + 1;
        r1.x = r1.x * r1.x;
        r1.x = 3.14159274 * r1.x;
        r1.x = r4.w / r1.x;
        r1.x = r1.x * r11.y;
        r1.w = -r1.y * r1.y + 1;
        r2.x = r0.w * r1.w + r1.z;
        r1.z = r0.z * r1.w + r1.z;
        r0.w = r1.z * r0.w;
        r0.z = r0.z * r2.x + r0.w;
        r0.z = rcp(r0.z);
        r0.z = r1.x * r0.z;
        r0.z = 0.5 * r0.z;
        r1.xzw = r0.zzz * r11.xzw;
        r7.xyz = r5.www * r7.xyz + -r1.xzw;
        r1.xzw = r7.www * r7.xyz + r1.xzw;
        r12.xyz = r8.xyz * float3(0.318309873,0.318309873,0.318309873) + r1.xzw;
        break;
        case 9 :        r0.yzw = r5.xyz * r0.yyy + -r4.xyz;
        r1.x = dot(r0.yzw, r0.yzw);
        r1.x = rsqrt(r1.x);
        r0.yzw = r1.xxx * r0.yzw;
        r1.x = saturate(dot(r2.yzw, r9.xyz));
        r1.z = dot(r2.yzw, -r4.xyz);
        r1.z = max(9.99999975e-006, r1.z);
        r1.w = saturate(dot(r2.yzw, r0.yzw));
        r0.y = saturate(dot(-r4.xyz, r0.yzw));
        r0.z = r1.y * r1.y;
        r0.w = r0.z * r0.z;
        r2.x = r1.w * r0.w + -r1.w;
        r1.w = r2.x * r1.w + 1;
        r1.w = r1.w * r1.w;
        r1.w = 3.14159274 * r1.w;
        r0.w = r0.w / r1.w;
        r0.w = r0.w * r11.y;
        r1.y = -r1.y * r1.y + 1;
        r1.w = r1.z * r1.y + r0.z;
        r0.z = r1.x * r1.y + r0.z;
        r0.z = r1.z * r0.z;
        r0.z = r1.x * r1.w + r0.z;
        r0.z = rcp(r0.z);
        r0.z = r0.w * r0.z;
        r0.y = 1 + -r0.y;
        r0.w = r0.y * r0.y;
        r0.w = r0.w * r0.w;
        r1.x = r0.w * r0.y;
        r1.y = saturate(50 * r6.y);
        r0.y = -r0.w * r0.y + 1;
        r2.xyz = r0.yyy * r6.xyz;
        r1.xyz = r1.yyy * r1.xxx + r2.xyz;
        r0.y = 0.5 * r0.z;
        r12.xyz = r0.yyy * r1.xyz;
        break;
        default :
        r12.xyz = float3(0,0,0);
        break;
      }
      r0.x = r3.w * r0.x;
      r0.xyz = cb2[1].xyz * r0.xxx;
      r1.xyz = r12.xyz + r10.xyz;
      r0.xyz = r1.xyz * r0.xyz;
    } else {
      r0.xyz = float3(0,0,0);
    }
    r1.xyz = -cb2[0].xyz + r3.xyz;
    r0.w = dot(r1.xyz, r1.xyz);
    r0.w = rsqrt(r0.w);
    r1.xyz = r1.xyz * r0.www;
    r0.w = dot(r1.xyz, cb2[2].xyz);
    r1.x = 1 + -abs(r0.w);
    r1.x = sqrt(r1.x);
    r1.y = abs(r0.w) * -0.0187292993 + 0.0742610022;
    r1.y = r1.y * abs(r0.w) + -0.212114394;
    r1.y = r1.y * abs(r0.w) + 1.57072878;
    r1.z = r1.y * r1.x;
    r1.z = r1.z * -2 + 3.14159274;
    r0.w = cmp(r0.w < -r0.w);
    r0.w = r0.w ? r1.z : 0;
    r0.w = r1.y * r1.x + r0.w;
    r0.w = 1.57079637 + -r0.w;
    r1.x = r0.w * 0.318309873 + 0.5;
    r1.y = 0;
    r0.w = t7.SampleLevel(s7_s, r1.xy, 0).x;
    o0.xyz = r0.xyz * r0.www;
    o0.w = 0;
  } else {
    o0.xyzw = float4(0,0,0,0);
  }
  return;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Generated by Microsoft (R) D3D Shader Disassembler
//
//   using 3Dmigoto v1.2.51 on Sat Dec 24 06:45:42 2016
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// TEXCOORD                 0   xyzw        0     NONE   float   xy w
// SV_POSITION              0   xyzw        1      POS   float       
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Target                0   xyzw        0   TARGET   float   xyzw
//
ps_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer cb0[54], immediateIndexed
dcl_constantbuffer cb1[33], immediateIndexed
dcl_constantbuffer cb2[7], immediateIndexed
dcl_sampler s0, mode_default
dcl_sampler s1, mode_default
dcl_sampler s2, mode_default
dcl_sampler s3, mode_default
dcl_sampler s4, mode_default
dcl_sampler s5, mode_default
dcl_sampler s6, mode_default
dcl_sampler s7, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_resource_texture2d (float,float,float,float) t2
dcl_resource_texture2d (float,float,float,float) t3
dcl_resource_texture2d (float,float,float,float) t4
dcl_resource_texture2d (float,float,float,float) t5
dcl_resource_texture2d (float,float,float,float) t6
dcl_resource_texture2d (float,float,float,float) t7
dcl_input_ps linear v0.xyw
dcl_output o0.xyzw
dcl_temps 15
div r0.xy, v0.xyxx, v0.wwww
mad r0.zw, r0.xxxy, cb0[52].xxxy, cb0[52].wwwz
sample_l_indexable(texture2d)(float,float,float,float) r1.xyzw, r0.zwzz, t1.xzyw, s1, l(0.000000)
mul r1.w, r1.w, l(255.000000)
round_ne r1.w, r1.w
ftou r1.w, r1.w
and r2.x, r1.w, l(15)
if_nz r2.x
  sample_l_indexable(texture2d)(float,float,float,float) r2.yzw, r0.zwzz, t0.wxyz, s0, l(0.000000)
  mad r2.yzw, r2.yyzw, l(0.000000, 2.000000, 2.000000, 2.000000), l(0.000000, -1.000000, -1.000000, -1.000000)
  dp3 r3.x, r2.yzwy, r2.yzwy
  rsq r3.x, r3.x
  mul r2.yzw, r2.yyzw, r3.xxxx
  sample_l_indexable(texture2d)(float,float,float,float) r3.x, r0.zwzz, t4.xyzw, s4, l(0.000000)
  mad r3.x, r3.x, cb0[51].z, -cb0[51].w
  div r3.x, l(1.000000, 1.000000, 1.000000, 1.000000), r3.x
  mul r0.xy, r0.xyxx, r3.xxxx
  mul r4.xyzw, r0.yyyy, cb0[41].xyzw
  mad r4.xyzw, r0.xxxx, cb0[40].xyzw, r4.xyzw
  mad r3.xyzw, r3.xxxx, cb0[42].xyzw, r4.xyzw
  add r3.xyzw, r3.xyzw, cb0[43].xyzw
  div r3.xyz, r3.xyzx, r3.wwww
  add r4.xyz, r3.xyzx, -cb0[53].xyzx
  dp3 r0.x, r4.xyzx, r4.xyzx
  rsq r0.x, r0.x
  mul r4.xyz, r0.xxxx, r4.xyzx
  sample_l_indexable(texture2d)(float,float,float,float) r0.x, r0.zwzz, t5.zxyw, s5, l(0.000000)
  mul r0.x, r0.x, r0.x
  add r5.xyz, -r3.xyzx, cb2[0].xyzx
  dp3 r0.y, r5.xyzx, r5.xyzx
  rsq r0.y, r0.y
  mul r6.xyz, r0.yyyy, r5.xyzx
  dp3_sat r3.w, r2.yzwy, r6.xyzx
  mul r7.xyz, r5.xyzx, cb2[0].wwww
  dp3 r4.w, r7.xyzx, r7.xyzx
  min r4.w, r4.w, l(1.000000)
  add r4.w, -r4.w, l(1.000000)
  log r4.w, r4.w
  mul r4.w, r4.w, cb2[1].w
  exp r4.w, r4.w
  dp3 r5.w, r6.xyzx, cb2[2].xyzx
  add r5.w, r5.w, -cb2[3].x
  mul_sat r5.w, r5.w, cb2[3].y
  mul r5.w, r5.w, r5.w
  lt r6.x, l(0.000000), r4.w
  lt r6.y, l(0.000000), r5.w
  and r6.x, r6.y, r6.x
  if_nz r6.x
    sample_l_indexable(texture2d)(float,float,float,float) r6.xyz, r0.zwzz, t2.xyzw, s2, l(0.000000)
    sample_l_indexable(texture2d)(float,float,float,float) r7.xyzw, r0.zwzz, t3.xyzw, s3, l(0.000000)
    mul r8.xy, r0.zwzz, cb1[3].xyxx
    ftou r8.xy, r8.xyxx
    ftou r8.z, cb1[32].x
    iadd r8.x, r8.x, r8.y
    iadd r8.x, r8.x, r8.z
    and r8.x, r8.x, l(1)
    and r8.y, r1.w, l(16)
    movc r7.xyzw, r8.yyyy, l(0,0,0,0), r7.xyzw
    ieq r8.y, r2.x, l(5)
    movc r9.xyzw, r8.xxxx, l(1.000000,1.000000,1.000000,0), l(0,0,0,1.000000)
    mov r6.w, r1.z
    movc r6.xyzw, r8.yyyy, r9.xyzw, r6.xyzw
    mad r8.xyz, -r6.xyzx, r1.xxxx, r6.xyzx
    mul r8.w, r6.w, l(0.080000)
    mad r6.xyz, -r6.wwww, l(0.080000, 0.080000, 0.080000, 0.000000), r6.xyzx
    mad r6.xyz, r1.xxxx, r6.xyzx, r8.wwww
    mad r8.xyz, r8.xyzx, cb1[5].wwww, cb1[5].xyzx
    mad r6.xyz, r6.xyzx, cb1[6].wwww, cb1[6].xyzx
    if_nz cb2[6].x
      and r9.xy, r1.wwww, l(32, 64, 0, 0)
      movc r1.w, r9.y, l(0), l(1.000000)
      movc r1.w, r9.x, r1.w, l(1.000000)
      dp4 r6.w, cb2[5].xyzw, l(1.000000, 1.000000, 1.000000, 1.000000)
      dp4 r1.w, r1.wwww, cb2[5].xyzw
      add r1.w, r1.w, l(-1.000000)
      mad r1.w, r6.w, r1.w, l(1.000000)
      mul r0.x, r0.x, r1.w
    else 
      sample_l_indexable(texture2d)(float,float,float,float) r0.x, r0.zwzz, t6.xyzw, s6, l(0.000000)
    endif 
    mul r0.z, r4.w, r5.w
    mul r0.x, r0.x, r0.z
    mov r1.x, r7.y
    mov r1.z, l(1.000000)
    max r1.xyz, r1.xyzx, cb2[4].xxxx
    mul r9.xyz, r1.xyzx, r1.xyzx
    dp3 r0.z, r4.xyzx, r2.yzwy
    add r0.z, r0.z, r0.z
    mad r10.xyz, r2.yzwy, -r0.zzzz, r4.xyzx
    lt r0.zw, l(0.000000, 0.000000, 0.000000, 0.000000), cb2[3].wwwz
    if_nz r0.z
      mul r0.z, r0.y, cb2[3].w
      min r0.z, r0.z, l(1.000000)
      mad r11.xyz, r0.zzzz, l(0.500000, 0.500000, 0.500000, 0.000000), r9.xyzx
      min r11.xyz, r11.xyzx, l(1.000000, 1.000000, 1.000000, 0.000000)
      div r11.xyz, r9.xyzx, r11.xyzx
      mul r12.xyz, cb2[2].xyzx, cb2[3].wwww
      mad r13.xyz, -r12.xyzx, l(0.500000, 0.500000, 0.500000, 0.000000), r5.xyzx
      dp3 r0.z, r10.xyzx, r12.xyzx
      mad r14.xyz, r0.zzzz, r10.xyzx, -r12.xyzx
      dp3 r1.z, r13.xyzx, r14.xyzx
      mul r0.z, r0.z, r0.z
      mad r0.z, cb2[3].w, cb2[3].w, -r0.z
      div_sat r0.z, r1.z, r0.z
      mad r5.xyz, r0.zzzz, r12.xyzx, r13.xyzx
    else 
      mov r11.xyz, l(1.000000,1.000000,1.000000,0)
    endif 
    if_nz r0.w
      mul r0.y, r0.y, cb2[3].z
      min r0.y, r0.y, l(1.000000)
      mad r0.yzw, r0.yyyy, l(0.000000, 0.500000, 0.500000, 0.500000), r9.xxyz
      min r0.yzw, r0.yyzw, l(0.000000, 1.000000, 1.000000, 1.000000)
      div r0.yzw, r9.xxyz, r0.yyzw
      mul r0.yzw, r0.yyzw, r0.yyzw
      mul r11.xyz, r0.yzwy, r11.xyzx
      dp3 r0.y, r5.xyzx, r10.xyzx
      mad r0.yzw, r0.yyyy, r10.xxyz, -r5.xxyz
      dp3 r1.z, r0.yzwy, r0.yzwy
      rsq r1.z, r1.z
      mul r1.z, r1.z, cb2[3].z
      min r1.z, r1.z, l(1.000000)
      mad r5.xyz, r0.yzwy, r1.zzzz, r5.xyzx
    endif 
    dp3 r0.y, r5.xyzx, r5.xyzx
    rsq r0.y, r0.y
    mul r9.xyz, r0.yyyy, r5.xyzx
    switch r2.x
      case l(1)
      case l(2)
      case l(3)
      case l(5)
      case l(6)
      mul r12.xyz, r8.xyzx, r11.zzzz
      mul r10.xyz, r12.xyzx, l(0.318309873, 0.318309873, 0.318309873, 0.000000)
      break 
      case l(4)
      mad r12.xyz, r5.xyzx, r0.yyyy, -r4.xyzx
      dp3 r0.z, r12.xyzx, r12.xyzx
      rsq r0.z, r0.z
      mul r12.xyz, r0.zzzz, r12.xyzx
      dp3_sat r0.z, r2.yzwy, r9.xyzx
      dp3 r0.w, r2.yzwy, -r4.xyzx
      max r0.w, r0.w, l(0.000010)
      dp3_sat r1.z, r2.yzwy, r12.xyzx
      dp3_sat r1.w, -r4.xyzx, r12.xyzx
      mul r12.xy, r1.xyxx, r1.xyxx
      mul r12.xz, r12.xxyx, r12.xxyx
      mad r13.xy, r1.zzzz, r12.xzxx, -r1.zzzz
      mad r13.xy, r13.xyxx, r1.zzzz, l(1.000000, 1.000000, 0.000000, 0.000000)
      mul r13.xy, r13.xyxx, r13.xyxx
      mul r13.xy, r13.xyxx, l(3.14159274, 3.14159274, 0.000000, 0.000000)
      div r12.xz, r12.xxzx, r13.xxyx
      mul r1.z, r11.x, r12.x
      mul r4.w, r1.w, r1.w
      mad r4.w, r4.w, l(4.000000), l(0.000010)
      rcp r4.w, r4.w
      add r1.w, -r1.w, l(1.000000)
      mul r5.w, r1.w, r1.w
      mul r5.w, r5.w, r5.w
      mul r6.w, r1.w, r5.w
      mad r1.w, -r5.w, r1.w, l(1.000000)
      mad r5.w, r1.w, l(0.040000), r6.w
      mul r8.w, r7.x, r5.w
      mul r1.z, r1.z, r4.w
      mad r4.w, -r5.w, r7.x, l(1.000000)
      mul r5.w, r11.y, r12.z
      mul r9.w, r12.y, l(0.500000)
      mad r10.w, -r12.y, l(0.500000), l(1.000000)
      mad r0.w, r0.w, r10.w, r9.w
      mad r0.z, r0.z, r10.w, r9.w
      mul r0.z, r0.z, r0.w
      div r0.z, l(0.250000), r0.z
      mul_sat r0.w, r6.y, l(50.000000)
      mul r12.xyz, r6.xyzx, r1.wwww
      mad r12.xyz, r0.wwww, r6.wwww, r12.xyzx
      mul r13.xyz, r8.xyzx, r11.zzzz
      mul r0.z, r0.z, r5.w
      mul r12.xyz, r12.xyzx, r0.zzzz
      mad r12.xyz, r13.xyzx, l(0.318309873, 0.318309873, 0.318309873, 0.000000), r12.xyzx
      mul r12.xyz, r4.wwww, r12.xyzx
      mad r10.xyz, r1.zzzz, r8.wwww, r12.xyzx
      break 
      case l(8)
      mov_sat r12.xyzw, r7.xyzw
      mad r13.xyz, r5.xyzx, r0.yyyy, -r4.xyzx
      dp3 r0.z, r13.xyzx, r13.xyzx
      rsq r0.z, r0.z
      mul r13.xyz, r0.zzzz, r13.xyzx
      dp3_sat r0.z, r2.yzwy, r9.xyzx
      dp3 r0.w, r2.yzwy, -r4.xyzx
      max r0.w, r0.w, l(0.000010)
      dp3_sat r1.z, r2.yzwy, r13.xyzx
      dp3_sat r1.w, -r4.xyzx, r13.xyzx
      mul r13.xyz, r8.xyzx, r11.zzzz
      add r1.w, -r1.w, l(1.000000)
      mul r4.w, r1.w, r1.w
      mul r4.w, r4.w, r4.w
      mul r5.w, r1.w, r4.w
      mul r6.w, r12.y, l(50.000000)
      min r6.w, r6.w, l(1.000000)
      mad r1.w, -r4.w, r1.w, l(1.000000)
      mul r12.xyz, r12.xyzx, r1.wwww
      mad r12.xyz, r6.wwww, r5.wwww, r12.xyzx
      mul r4.w, r1.y, r1.y
      mul r6.w, r4.w, r4.w
      mad r8.w, -r6.w, r1.z, r1.z
      mad r8.w, r8.w, r1.z, r6.w
      mul r9.w, r6.w, l(4.000000)
      mad r10.w, r6.w, l(4.000000), l(1.000000)
      mul r10.w, r10.w, l(3.14159274)
      rcp r10.w, r10.w
      mul r9.w, r6.w, r9.w
      mul r8.w, r8.w, r8.w
      div r8.w, r9.w, r8.w
      add r8.w, r8.w, l(1.000000)
      mul r8.w, r8.w, r10.w
      add r9.w, r0.w, r0.z
      mad r9.w, -r0.z, r0.w, r9.w
      mul r9.w, r9.w, l(4.000000)
      rcp r9.w, r9.w
      mul r8.w, r8.w, r9.w
      mul_sat r9.w, r6.y, l(50.000000)
      mul r14.xyz, r6.xyzx, r1.wwww
      mad r14.xyz, r9.wwww, r5.wwww, r14.xyzx
      mad r1.w, r6.w, r1.z, -r1.z
      mad r1.z, r1.w, r1.z, l(1.000000)
      mul r1.z, r1.z, r1.z
      mul r1.z, r1.z, l(3.14159274)
      div r1.z, r6.w, r1.z
      mul r1.z, r11.y, r1.z
      mad r1.w, -r1.y, r1.y, l(1.000000)
      mad r5.w, r0.w, r1.w, r4.w
      mad r1.w, r0.z, r1.w, r4.w
      mul r0.w, r0.w, r1.w
      mad r0.z, r0.z, r5.w, r0.w
      rcp r0.z, r0.z
      mul r0.z, r0.z, r1.z
      mul r0.z, r0.z, l(0.500000)
      mul r14.xyz, r14.xyzx, r0.zzzz
      mad r12.xyz, r8.wwww, r12.xyzx, -r14.xyzx
      mad r12.xyz, r12.wwww, r12.xyzx, r14.xyzx
      mad r10.xyz, r13.xyzx, l(0.318309873, 0.318309873, 0.318309873, 0.000000), r12.xyzx
      break 
      case l(9)
      mad r12.xyz, r5.xyzx, r0.yyyy, -r4.xyzx
      dp3 r0.z, r12.xyzx, r12.xyzx
      rsq r0.z, r0.z
      mul r12.xyz, r0.zzzz, r12.xyzx
      dp3_sat r0.z, r2.yzwy, r9.xyzx
      dp3 r0.w, r2.yzwy, -r4.xyzx
      max r0.w, r0.w, l(0.000010)
      dp3_sat r1.z, r2.yzwy, r12.xyzx
      dp3_sat r1.w, -r4.xyzx, r12.xyzx
      mul r4.w, r1.y, r1.y
      mul r5.w, r4.w, r4.w
      mad r6.w, r1.z, r5.w, -r1.z
      mad r1.z, r6.w, r1.z, l(1.000000)
      mul r1.z, r1.z, r1.z
      mul r1.z, r1.z, l(3.14159274)
      div r1.z, r5.w, r1.z
      mul r1.z, r11.y, r1.z
      mad r5.w, -r1.y, r1.y, l(1.000000)
      mad r6.w, r0.w, r5.w, r4.w
      mad r4.w, r0.z, r5.w, r4.w
      mul r0.w, r0.w, r4.w
      mad r0.z, r0.z, r6.w, r0.w
      rcp r0.z, r0.z
      mul r0.z, r0.z, r1.z
      add r0.w, -r1.w, l(1.000000)
      mul r1.z, r0.w, r0.w
      mul r1.z, r1.z, r1.z
      mul r1.w, r0.w, r1.z
      mul_sat r4.w, r6.y, l(50.000000)
      mad r0.w, -r1.z, r0.w, l(1.000000)
      mul r12.xyz, r6.xyzx, r0.wwww
      mad r12.xyz, r4.wwww, r1.wwww, r12.xyzx
      mul r0.z, r0.z, l(0.500000)
      mul r10.xyz, r12.xyzx, r0.zzzz
      break 
      default 
      mov r10.xyz, l(0,0,0,0)
      break 
    endswitch 
    switch r2.x
      case l(1)
      case l(2)
      case l(3)
      case l(5)
      case l(6)
      mad r13.xyz, r5.xyzx, r0.yyyy, -r4.xyzx
      dp3 r0.z, r13.xyzx, r13.xyzx
      rsq r0.z, r0.z
      mul r13.xyz, r0.zzzz, r13.xyzx
      dp3_sat r0.z, r2.yzwy, r9.xyzx
      dp3 r0.w, r2.yzwy, -r4.xyzx
      max r0.w, r0.w, l(0.000010)
      dp3_sat r1.z, r2.yzwy, r13.xyzx
      dp3_sat r1.w, -r4.xyzx, r13.xyzx
      mul r2.x, r1.y, r1.y
      mul r4.w, r2.x, r2.x
      mad r5.w, r1.z, r4.w, -r1.z
      mad r1.z, r5.w, r1.z, l(1.000000)
      mul r1.z, r1.z, r1.z
      mul r1.z, r1.z, l(3.14159274)
      div r1.z, r4.w, r1.z
      mul r1.z, r11.y, r1.z
      mad r4.w, -r1.y, r1.y, l(1.000000)
      mad r5.w, r0.w, r4.w, r2.x
      mad r2.x, r0.z, r4.w, r2.x
      mul r0.w, r0.w, r2.x
      mad r0.z, r0.z, r5.w, r0.w
      rcp r0.z, r0.z
      mul r0.z, r0.z, r1.z
      add r0.w, -r1.w, l(1.000000)
      mul r1.z, r0.w, r0.w
      mul r1.z, r1.z, r1.z
      mul r1.w, r0.w, r1.z
      mul_sat r2.x, r6.y, l(50.000000)
      mad r0.w, -r1.z, r0.w, l(1.000000)
      mul r13.xyz, r6.xyzx, r0.wwww
      mad r13.xyz, r2.xxxx, r1.wwww, r13.xyzx
      mul r0.z, r0.z, l(0.500000)
      mul r12.xyz, r13.xyzx, r0.zzzz
      break 
      case l(4)
      mad r13.xyz, r5.xyzx, r0.yyyy, -r4.xyzx
      dp3 r0.z, r13.xyzx, r13.xyzx
      rsq r0.z, r0.z
      mul r13.xyz, r0.zzzz, r13.xyzx
      dp3_sat r0.z, r2.yzwy, r9.xyzx
      dp3 r0.w, r2.yzwy, -r4.xyzx
      max r0.w, r0.w, l(0.000010)
      dp3_sat r1.z, r2.yzwy, r13.xyzx
      dp3_sat r1.w, -r4.xyzx, r13.xyzx
      mul r13.xy, r1.xyxx, r1.xyxx
      mul r13.xz, r13.xxyx, r13.xxyx
      mad r14.xy, r1.zzzz, r13.xzxx, -r1.zzzz
      mad r1.xz, r14.xxyx, r1.zzzz, l(1.000000, 0.000000, 1.000000, 0.000000)
      mul r1.xz, r1.xxzx, r1.xxzx
      mul r1.xz, r1.xxzx, l(3.14159274, 0.000000, 3.14159274, 0.000000)
      div r1.xz, r13.xxzx, r1.xxzx
      mul r1.xz, r11.xxyx, r1.xxzx
      mul r2.x, r1.w, r1.w
      mad r2.x, r2.x, l(4.000000), l(0.000010)
      rcp r2.x, r2.x
      add r1.w, -r1.w, l(1.000000)
      mul r4.w, r1.w, r1.w
      mul r4.w, r4.w, r4.w
      mul r5.w, r1.w, r4.w
      mad r1.w, -r4.w, r1.w, l(1.000000)
      mad r4.w, r1.w, l(0.040000), r5.w
      mul r6.w, r7.x, r4.w
      mul r1.x, r1.x, r2.x
      mad r2.x, -r4.w, r7.x, l(1.000000)
      mul r4.w, r13.y, l(0.500000)
      mad r8.w, -r13.y, l(0.500000), l(1.000000)
      mad r0.w, r0.w, r8.w, r4.w
      mad r0.z, r0.z, r8.w, r4.w
      mul r0.z, r0.z, r0.w
      div r0.z, l(0.250000), r0.z
      mul_sat r0.w, r6.y, l(50.000000)
      mul r13.xyz, r6.xyzx, r1.wwww
      mad r13.xyz, r0.wwww, r5.wwww, r13.xyzx
      mul r14.xyz, r8.xyzx, r11.zzzz
      mul r0.z, r0.z, r1.z
      mul r13.xyz, r13.xyzx, r0.zzzz
      mad r13.xyz, r14.xyzx, l(0.318309873, 0.318309873, 0.318309873, 0.000000), r13.xyzx
      mul r13.xyz, r2.xxxx, r13.xyzx
      mad r12.xyz, r1.xxxx, r6.wwww, r13.xyzx
      break 
      case l(8)
      mov_sat r7.xyzw, r7.xyzw
      mad r1.xzw, r5.xxyz, r0.yyyy, -r4.xxyz
      dp3 r0.z, r1.xzwx, r1.xzwx
      rsq r0.z, r0.z
      mul r1.xzw, r0.zzzz, r1.xxzw
      dp3_sat r0.z, r2.yzwy, r9.xyzx
      dp3 r0.w, r2.yzwy, -r4.xyzx
      max r0.w, r0.w, l(0.000010)
      dp3_sat r2.x, r2.yzwy, r1.xzwx
      dp3_sat r1.x, -r4.xyzx, r1.xzwx
      mul r8.xyz, r8.xyzx, r11.zzzz
      add r1.x, -r1.x, l(1.000000)
      mul r1.z, r1.x, r1.x
      mul r1.z, r1.z, r1.z
      mul r1.w, r1.x, r1.z
      mul r4.w, r7.y, l(50.000000)
      min r4.w, r4.w, l(1.000000)
      mad r1.x, -r1.z, r1.x, l(1.000000)
      mul r7.xyz, r7.xyzx, r1.xxxx
      mad r7.xyz, r4.wwww, r1.wwww, r7.xyzx
      mul r1.z, r1.y, r1.y
      mul r4.w, r1.z, r1.z
      mad r5.w, -r4.w, r2.x, r2.x
      mad r5.w, r5.w, r2.x, r4.w
      mul r6.w, r4.w, l(4.000000)
      mad r8.w, r4.w, l(4.000000), l(1.000000)
      mul r8.w, r8.w, l(3.14159274)
      rcp r8.w, r8.w
      mul r6.w, r4.w, r6.w
      mul r5.w, r5.w, r5.w
      div r5.w, r6.w, r5.w
      add r5.w, r5.w, l(1.000000)
      mul r5.w, r5.w, r8.w
      add r6.w, r0.w, r0.z
      mad r6.w, -r0.z, r0.w, r6.w
      mul r6.w, r6.w, l(4.000000)
      rcp r6.w, r6.w
      mul r5.w, r5.w, r6.w
      mul_sat r6.w, r6.y, l(50.000000)
      mul r11.xzw, r6.xxyz, r1.xxxx
      mad r11.xzw, r6.wwww, r1.wwww, r11.xxzw
      mad r1.x, r4.w, r2.x, -r2.x
      mad r1.x, r1.x, r2.x, l(1.000000)
      mul r1.x, r1.x, r1.x
      mul r1.x, r1.x, l(3.14159274)
      div r1.x, r4.w, r1.x
      mul r1.x, r11.y, r1.x
      mad r1.w, -r1.y, r1.y, l(1.000000)
      mad r2.x, r0.w, r1.w, r1.z
      mad r1.z, r0.z, r1.w, r1.z
      mul r0.w, r0.w, r1.z
      mad r0.z, r0.z, r2.x, r0.w
      rcp r0.z, r0.z
      mul r0.z, r0.z, r1.x
      mul r0.z, r0.z, l(0.500000)
      mul r1.xzw, r11.xxzw, r0.zzzz
      mad r7.xyz, r5.wwww, r7.xyzx, -r1.xzwx
      mad r1.xzw, r7.wwww, r7.xxyz, r1.xxzw
      mad r12.xyz, r8.xyzx, l(0.318309873, 0.318309873, 0.318309873, 0.000000), r1.xzwx
      break 
      case l(9)
      mad r0.yzw, r5.xxyz, r0.yyyy, -r4.xxyz
      dp3 r1.x, r0.yzwy, r0.yzwy
      rsq r1.x, r1.x
      mul r0.yzw, r0.yyzw, r1.xxxx
      dp3_sat r1.x, r2.yzwy, r9.xyzx
      dp3 r1.z, r2.yzwy, -r4.xyzx
      max r1.z, r1.z, l(0.000010)
      dp3_sat r1.w, r2.yzwy, r0.yzwy
      dp3_sat r0.y, -r4.xyzx, r0.yzwy
      mul r0.z, r1.y, r1.y
      mul r0.w, r0.z, r0.z
      mad r2.x, r1.w, r0.w, -r1.w
      mad r1.w, r2.x, r1.w, l(1.000000)
      mul r1.w, r1.w, r1.w
      mul r1.w, r1.w, l(3.14159274)
      div r0.w, r0.w, r1.w
      mul r0.w, r11.y, r0.w
      mad r1.y, -r1.y, r1.y, l(1.000000)
      mad r1.w, r1.z, r1.y, r0.z
      mad r0.z, r1.x, r1.y, r0.z
      mul r0.z, r0.z, r1.z
      mad r0.z, r1.x, r1.w, r0.z
      rcp r0.z, r0.z
      mul r0.z, r0.z, r0.w
      add r0.y, -r0.y, l(1.000000)
      mul r0.w, r0.y, r0.y
      mul r0.w, r0.w, r0.w
      mul r1.x, r0.y, r0.w
      mul_sat r1.y, r6.y, l(50.000000)
      mad r0.y, -r0.w, r0.y, l(1.000000)
      mul r2.xyz, r6.xyzx, r0.yyyy
      mad r1.xyz, r1.yyyy, r1.xxxx, r2.xyzx
      mul r0.y, r0.z, l(0.500000)
      mul r12.xyz, r1.xyzx, r0.yyyy
      break 
      default 
      mov r12.xyz, l(0,0,0,0)
      break 
    endswitch 
    mul r0.x, r0.x, r3.w
    mul r0.xyz, r0.xxxx, cb2[1].xyzx
    add r1.xyz, r10.xyzx, r12.xyzx
    mul r0.xyz, r0.xyzx, r1.xyzx
  else 
    mov r0.xyz, l(0,0,0,0)
  endif 
  add r1.xyz, r3.xyzx, -cb2[0].xyzx
  dp3 r0.w, r1.xyzx, r1.xyzx
  rsq r0.w, r0.w
  mul r1.xyz, r0.wwww, r1.xyzx
  dp3 r0.w, r1.xyzx, cb2[2].xyzx
  add r1.x, -|r0.w|, l(1.000000)
  sqrt r1.x, r1.x
  mad r1.y, |r0.w|, l(-0.0187292993), l(0.074261)
  mad r1.y, r1.y, |r0.w|, l(-0.212114394)
  mad r1.y, r1.y, |r0.w|, l(1.57072878)
  mul r1.z, r1.x, r1.y
  mad r1.z, r1.z, l(-2.000000), l(3.14159274)
  lt r0.w, r0.w, -r0.w
  and r0.w, r0.w, r1.z
  mad r0.w, r1.y, r1.x, r0.w
  add r0.w, -r0.w, l(1.57079637)
  mad r1.x, r0.w, l(0.318309873), l(0.500000)
  mov r1.y, l(0)
  sample_l_indexable(texture2d)(float,float,float,float) r0.w, r1.xyxx, t7.yzwx, s7, l(0.000000)
  mul o0.xyz, r0.wwww, r0.xyzx
  mov o0.w, l(0)
else 
  mov o0.xyzw, l(0,0,0,0)
endif 
ret 
// Approximately 0 instruction slots used

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
