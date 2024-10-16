//Haloing PS. Sphere barrier.
// ---- Created with geo-11 v0.6.193 on Sun May  5 19:17:31 2024
Texture2D<float4> t1 : register(t1);

Texture2D<float4> t0 : register(t0);

SamplerState s1_s : register(s1);

SamplerState s0_s : register(s0);

cbuffer cb1 : register(b1)
{
  float4 cb1[2];
}

cbuffer cb0 : register(b0)
{
  float4 cb0[13];
}




// 3Dmigoto declarations
#define cmp -
Texture1D<float4> IniParams : register(t120);
Texture2D<float4> StereoParams : register(t125);


void main(
  float4 v0 : SV_POSITION0,
  float4 v1 : TEXCOORD0,
  float4 v2 : TEXCOORD1,
  float4 v3 : TEXCOORD2,
  out float4 o0 : SV_Target0)
{
  float4 r0,r1,r2,r12,r13;
  uint4 bitmask, uiDest;
  float4 fDest;
  
  float4 stereo = StereoParams.Load(0);
  
  r0.xy = v1.xy * cb1[0].xy + cb1[0].zw;
  r0.xy = r0.xy * float2(2,2) + float2(-1,-1);
  r0.x = dot(r0.xy, r0.xy);
  r0.x = sqrt(r0.x);
  r0.x = min(1, r0.x);
  r0.x = 1 + -r0.x;
  r0.y = -cb0[12].x * cb1[1].z + 1;
  r0.yz = v1.xy * cb1[1].xy + r0.yy;
  r1.xyzw = t0.Sample(s1_s, r0.yz).xyzw;
  r0.w = r1.w * r0.x;
  r2.xy = v3.xy / v3.ww;
  
  v3.x+=stereo.x*(v3.w-stereo.y)*0.5;
  r12.xy = v3.xy / v3.ww;
  
  r1.xy = r1.xy * r1.ww + -r2.xy;
  r1.z = cb1[1].w * v2.w;
  r1.xy = r1.zz * r1.xy + r12.xy;
  r1.xyzw = t1.Sample(s0_s, r1.xy).xyzw;
  r0.xyz = r1.xyz;
  o0.xyzw = v2.xyzw * r0.xyzw;
  return;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Generated by Microsoft (R) D3D Shader Disassembler
//
//   using 3Dmigoto v0.6.193 on Sun May  5 19:17:31 2024
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_POSITION              0   xyzw        0      POS   float
// TEXCOORD                 0   xyzw        1     NONE   float   xy
// TEXCOORD                 1   xyzw        2     NONE   float   xyzw
// TEXCOORD                 2   xyzw        3     NONE   float   xy w
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Target                0   xyzw        0   TARGET   float   xyzw
//
ps_4_0
dcl_constantbuffer CB0[13], immediateIndexed
dcl_constantbuffer CB1[2], immediateIndexed
dcl_sampler s0, mode_default
dcl_sampler s1, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_input_ps linear v1.xy
dcl_input_ps linear v2.xyzw
dcl_input_ps linear v3.xyw
dcl_output o0.xyzw
dcl_temps 3
mad r0.xy, v1.xyxx, cb1[0].xyxx, cb1[0].zwzz
mad r0.xy, r0.xyxx, l(2.000000, 2.000000, 0.000000, 0.000000), l(-1.000000, -1.000000, 0.000000, 0.000000)
dp2 r0.x, r0.xyxx, r0.xyxx
sqrt r0.x, r0.x
min r0.x, r0.x, l(1.000000)
add r0.x, -r0.x, l(1.000000)
mad r0.y, -cb0[12].x, cb1[1].z, l(1.000000)
mad r0.yz, v1.xxyx, cb1[1].xxyx, r0.yyyy
sample r1.xyzw, r0.yzyy, t0.xyzw, s1
mul r0.w, r0.x, r1.w
div r2.xy, v3.xyxx, v3.wwww
mad r1.xy, r1.xyxx, r1.wwww, -r2.xyxx
mul r1.z, v2.w, cb1[1].w
mad r1.xy, r1.zzzz, r1.xyxx, r2.xyxx
sample r1.xyzw, r1.xyxx, t1.xyzw, s0
mov r0.xyz, r1.xyzx
mul o0.xyzw, r0.xyzw, v2.xyzw
ret
// Approximately 0 instruction slots used

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
