//HBAO+ PS 1.
// ---- Created with 3Dmigoto v0.6.163 on Thu Apr 20 22:30:31 2023
Texture2D<float4> t1 : register(t1);

Texture2DArray<float4> t0 : register(t0);

SamplerState s0_s : register(s0);

cbuffer cb1 : register(b1)
{
  float4 cb1[2];
}

cbuffer cb0 : register(b0)
{
  float4 cb0[14];
}




// 3Dmigoto declarations
#define cmp -
Texture1D<float4> IniParams : register(t120);
Texture2D<float4> StereoParams : register(t125);


void main(
  float4 v0 : SV_Position0,
  float2 v1 : TEXCOORD0,
  out float o0 : SV_TARGET0)
{
  float4 r0,r1,r2,r3,r4,r5,r6;
  uint4 bitmask, uiDest;
  float4 fDest;
  
  float4 stereo = StereoParams.Load(0);
  float fov = -cb0[2].z;
  
  r0.xy = floor(v0.xy);
  r0.xy = r0.xy * float2(4,4) + cb1[1].xy;
  r0.zw = cb0[1].xy * r0.xy;
  r1.xy = float2(0.25,0.25) * r0.zw;
  r1.z = 0;
  r2.z = t0.SampleLevel(s0_s, r1.xyz, 0).x;
  r0.z = cb0[3].x / r2.z;
  r0.w = cmp(r0.z < 1);
  if (r0.w != 0) {
    o0.x = 1;
    return;
  }
  r1.zw = cb0[2].xy * r1.xy + cb0[2].zw;
  r2.xy = r1.zw * r2.zz;
  
  r2.x-=stereo.x*(r2.z-stereo.y)*fov;
  
  r0.xy = cb0[7].xy + r0.xy;
  r3.xy = (int2)r0.xy;
  r3.zw = float2(0,0);
  r0.xyw = t1.Load(r3.xyz).xyz;
  r0.xyw = r0.xyw * cb0[13].xxx + cb0[13].yyy;
  r3.xyz = cb0[10].xyz * r0.yyy;
  r3.xyz = r0.xxx * cb0[9].xyz + r3.xyz;
  r0.xyw = r0.www * cb0[11].xyz + r3.xyz;
  r1.z = dot(r0.xyw, r0.xyw);
  r1.z = rsqrt(r1.z);
  r0.xyw = r1.zzz * r0.xyw;
  r1.z = 0.0500000007 * r0.z;
  r1.z = cb1[0].z * r1.z + 1;
  r3.xy = cb1[0].xy * r1.zz;
  r3.xy = round(r3.xy);
  r3.xy = r3.xy * cb0[1].xy + r1.xy;
  r3.z = 0;
  r4.z = t0.SampleLevel(s0_s, r3.xyz, 0).x;
  r3.xy = cb0[2].xy * r3.xy + cb0[2].zw;
  r4.xy = r3.xy * r4.zz;
  
  r4.x-=stereo.x*(r4.z-stereo.y)*fov;
  
  r1.w = r0.z * 0.0500000007 + r1.z;
  r3.xyz = r4.xyz + -r2.xyz;
  r2.w = dot(r3.xyz, r3.xyz);
  r3.x = dot(r0.xyw, r3.xyz);
  r3.y = rsqrt(r2.w);
  r3.x = saturate(r3.x * r3.y + -cb0[3].w);
  r2.w = saturate(r2.w * cb0[3].z + 1);
  r3.yz = cb1[0].xy * r1.ww;
  r3.yz = round(r3.yz);
  r4.xy = r3.yz * cb0[1].xy + r1.xy;
  r4.z = 0;
  r3.w = t0.SampleLevel(s0_s, r4.xyz, 0).x;
  r4.xy = cb0[2].xy * r4.xy + cb0[2].zw;
  r3.yz = r4.xy * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r4.x = r0.z * 0.0500000007 + r1.w;
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r4.yz = cb1[0].xy * r4.xx;
  r4.yz = round(r4.yz);
  r5.xy = r4.yz * cb0[1].xy + r1.xy;
  r5.z = 0;
  r4.w = t0.SampleLevel(s0_s, r5.xyz, 0).x;
  r5.xy = cb0[2].xy * r5.xy + cb0[2].zw;
  r4.yz = r5.xy * r4.ww;
  
  r4.y-=stereo.x*(r4.w-stereo.y)*fov;
  
  r0.z = r0.z * 0.0500000007 + r4.x;
  r4.yzw = r4.yzw + -r2.xyz;
  r3.w = dot(r4.yzw, r4.yzw);
  r4.y = dot(r0.xyw, r4.yzw);
  r4.z = rsqrt(r3.w);
  r4.y = saturate(r4.y * r4.z + -cb0[3].w);
  r3.w = saturate(r3.w * cb0[3].z + 1);
  r3.w = r4.y * r3.w;
  r3.y = r3.y * r3.z + r3.w;
  r3.zw = cb1[0].xy * r0.zz;
  r3.zw = round(r3.zw);
  r5.xy = r3.zw * cb0[1].xy + r1.xy;
  r5.z = 0;
  r4.w = t0.SampleLevel(s0_s, r5.xyz, 0).x;
  r3.zw = cb0[2].xy * r5.xy + cb0[2].zw;
  r4.yz = r3.zw * r4.ww;
  
  r4.y-=stereo.x*(r4.w-stereo.y)*fov;
  
  r4.yzw = r4.yzw + -r2.xyz;
  r3.z = dot(r4.yzw, r4.yzw);
  r3.w = dot(r0.xyw, r4.yzw);
  r4.y = rsqrt(r3.z);
  r3.w = saturate(r3.w * r4.y + -cb0[3].w);
  r3.z = saturate(r3.z * cb0[3].z + 1);
  r3.y = r3.w * r3.z + r3.y;
  r3.zw = float2(0.707106769,0.707106769) * cb1[0].xy;
  r5.x = cb1[0].x * 0.707106769 + -r3.w;
  r5.y = r3.w + r3.z;
  r4.yz = r5.xy * r1.zz;
  r4.yz = round(r4.yz);
  r6.xy = r4.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r4.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r5.zw = cb0[2].xy * r6.xy + cb0[2].zw;
  r4.yz = r5.zw * r4.ww;
  
  r4.y-=stereo.x*(r4.w-stereo.y)*fov;
  
  r4.yzw = r4.yzw + -r2.xyz;
  r5.z = dot(r4.yzw, r4.yzw);
  r4.y = dot(r0.xyw, r4.yzw);
  r4.z = rsqrt(r5.z);
  r4.y = saturate(r4.y * r4.z + -cb0[3].w);
  r4.z = saturate(r5.z * cb0[3].z + 1);
  r4.y = r4.y * r4.z;
  r2.w = r3.x * r2.w + r4.y;
  r4.yz = r5.xy * r1.ww;
  r4.yz = round(r4.yz);
  r6.xy = r4.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r4.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r5.zw = cb0[2].xy * r6.xy + cb0[2].zw;
  r4.yz = r5.zw * r4.ww;
  
  r4.y-=stereo.x*(r4.w-stereo.y)*fov;
  
  r4.yzw = r4.yzw + -r2.xyz;
  r3.x = dot(r4.yzw, r4.yzw);
  r4.y = dot(r0.xyw, r4.yzw);
  r4.z = rsqrt(r3.x);
  r4.y = saturate(r4.y * r4.z + -cb0[3].w);
  r3.x = saturate(r3.x * cb0[3].z + 1);
  r3.x = r4.y * r3.x + r3.y;
  r4.yz = r5.xy * r4.xx;
  r4.yz = round(r4.yz);
  r6.xy = r4.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r4.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r5.zw = cb0[2].xy * r6.xy + cb0[2].zw;
  r4.yz = r5.zw * r4.ww;
  
  r4.y-=stereo.x*(r4.w-stereo.y)*fov;
  
  r4.yzw = r4.yzw + -r2.xyz;
  r3.y = dot(r4.yzw, r4.yzw);
  r4.y = dot(r0.xyw, r4.yzw);
  r4.z = rsqrt(r3.y);
  r4.y = saturate(r4.y * r4.z + -cb0[3].w);
  r3.y = saturate(r3.y * cb0[3].z + 1);
  r3.x = r4.y * r3.y + r3.x;
  r4.yz = r5.xy * r0.zz;
  r4.yz = round(r4.yz);
  r5.xy = r4.yz * cb0[1].xy + r1.xy;
  r5.z = 0;
  r4.w = t0.SampleLevel(s0_s, r5.xyz, 0).x;
  r5.xy = cb0[2].xy * r5.xy + cb0[2].zw;
  r4.yz = r5.xy * r4.ww;
  
  r4.y-=stereo.x*(r4.w-stereo.y)*fov;
  
  r4.yzw = r4.yzw + -r2.xyz;
  r3.y = dot(r4.yzw, r4.yzw);
  r4.y = dot(r0.xyw, r4.yzw);
  r4.z = rsqrt(r3.y);
  r4.y = saturate(r4.y * r4.z + -cb0[3].w);
  r3.y = saturate(r3.y * cb0[3].z + 1);
  r3.x = r4.y * r3.y + r3.x;
  r5.x = cb1[0].x * -4.37113883e-08 + -cb1[0].y;
  r5.y = cb1[0].y * -4.37113883e-08 + cb1[0].x;
  r4.yz = r5.xy * r1.zz;
  r4.yz = round(r4.yz);
  r6.xy = r4.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r4.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r5.zw = cb0[2].xy * r6.xy + cb0[2].zw;
  r4.yz = r5.zw * r4.ww;
  
  r4.y-=stereo.x*(r4.w-stereo.y)*fov;
  
  r4.yzw = r4.yzw + -r2.xyz;
  r3.y = dot(r4.yzw, r4.yzw);
  r4.y = dot(r0.xyw, r4.yzw);
  r4.z = rsqrt(r3.y);
  r4.y = saturate(r4.y * r4.z + -cb0[3].w);
  r3.y = saturate(r3.y * cb0[3].z + 1);
  r2.w = r4.y * r3.y + r2.w;
  r4.yz = r5.xy * r1.ww;
  r4.yz = round(r4.yz);
  r6.xy = r4.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r4.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r5.zw = cb0[2].xy * r6.xy + cb0[2].zw;
  r4.yz = r5.zw * r4.ww;
  
  r4.y-=stereo.x*(r4.w-stereo.y)*fov;
  
  r4.yzw = r4.yzw + -r2.xyz;
  r3.y = dot(r4.yzw, r4.yzw);
  r4.y = dot(r0.xyw, r4.yzw);
  r4.z = rsqrt(r3.y);
  r4.y = saturate(r4.y * r4.z + -cb0[3].w);
  r3.y = saturate(r3.y * cb0[3].z + 1);
  r3.x = r4.y * r3.y + r3.x;
  r4.yz = r5.xy * r4.xx;
  r4.yz = round(r4.yz);
  r6.xy = r4.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r4.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r5.zw = cb0[2].xy * r6.xy + cb0[2].zw;
  r4.yz = r5.zw * r4.ww;
  
  r4.y-=stereo.x*(r4.w-stereo.y)*fov;
  
  r4.yzw = r4.yzw + -r2.xyz;
  r3.y = dot(r4.yzw, r4.yzw);
  r4.y = dot(r0.xyw, r4.yzw);
  r4.z = rsqrt(r3.y);
  r4.y = saturate(r4.y * r4.z + -cb0[3].w);
  r3.y = saturate(r3.y * cb0[3].z + 1);
  r3.x = r4.y * r3.y + r3.x;
  r4.yz = r5.xy * r0.zz;
  r4.yz = round(r4.yz);
  r5.xy = r4.yz * cb0[1].xy + r1.xy;
  r5.z = 0;
  r4.w = t0.SampleLevel(s0_s, r5.xyz, 0).x;
  r5.xy = cb0[2].xy * r5.xy + cb0[2].zw;
  r4.yz = r5.xy * r4.ww;
  
  r4.y-=stereo.x*(r4.w-stereo.y)*fov;
  
  r4.yzw = r4.yzw + -r2.xyz;
  r3.y = dot(r4.yzw, r4.yzw);
  r4.y = dot(r0.xyw, r4.yzw);
  r4.z = rsqrt(r3.y);
  r4.y = saturate(r4.y * r4.z + -cb0[3].w);
  r3.y = saturate(r3.y * cb0[3].z + 1);
  r3.x = r4.y * r3.y + r3.x;
  r5.x = cb1[0].x * -0.707106769 + -r3.w;
  r5.y = cb1[0].y * -0.707106769 + r3.z;
  r3.yz = r5.xy * r1.zz;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r2.w = r3.y * r3.z + r2.w;
  r3.yz = r5.xy * r1.ww;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r3.yz = r5.xy * r4.xx;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r3.yz = r5.xy * r0.zz;
  r3.yz = round(r3.yz);
  r5.xy = r3.yz * cb0[1].xy + r1.xy;
  r5.z = 0;
  r3.w = t0.SampleLevel(s0_s, r5.xyz, 0).x;
  r4.yz = cb0[2].xy * r5.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r5.x = -cb1[0].y * -8.74227766e-08 + -cb1[0].x;
  r5.y = cb1[0].x * -8.74227766e-08 + -cb1[0].y;
  r3.yz = r5.xy * r1.zz;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r2.w = r3.y * r3.z + r2.w;
  r3.yz = r5.xy * r1.ww;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r3.yz = r5.xy * r4.xx;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r3.yz = r5.xy * r0.zz;
  r3.yz = round(r3.yz);
  r5.xy = r3.yz * cb0[1].xy + r1.xy;
  r5.z = 0;
  r3.w = t0.SampleLevel(s0_s, r5.xyz, 0).x;
  r4.yz = cb0[2].xy * r5.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r3.y = -0.707106888 * cb1[0].y;
  r5.x = cb1[0].x * -0.70710665 + -r3.y;
  r5.y = dot(cb1[0].yx, float2(-0.70710665,-0.707106888));
  r3.yz = r5.xy * r1.zz;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r2.w = r3.y * r3.z + r2.w;
  r3.yz = r5.xy * r1.ww;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r3.yz = r5.xy * r4.xx;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r3.yz = r5.xy * r0.zz;
  r3.yz = round(r3.yz);
  r5.xy = r3.yz * cb0[1].xy + r1.xy;
  r5.z = 0;
  r3.w = t0.SampleLevel(s0_s, r5.xyz, 0).x;
  r4.yz = cb0[2].xy * r5.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r5.x = cb1[0].x * 1.19248806e-08 + cb1[0].y;
  r5.y = cb1[0].y * 1.19248806e-08 + -cb1[0].x;
  r3.yz = r5.xy * r1.zz;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r2.w = r3.y * r3.z + r2.w;
  r3.yz = r5.xy * r1.ww;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r3.yz = r5.xy * r4.xx;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r3.yz = r5.xy * r0.zz;
  r3.yz = round(r3.yz);
  r5.xy = r3.yz * cb0[1].xy + r1.xy;
  r5.z = 0;
  r3.w = t0.SampleLevel(s0_s, r5.xyz, 0).x;
  r4.yz = cb0[2].xy * r5.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r4.y = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r4.y);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r3.z = saturate(r4.y * cb0[3].z + 1);
  r3.x = r3.y * r3.z + r3.x;
  r3.y = -0.707106531 * cb1[0].y;
  r5.x = cb1[0].x * 0.707107008 + -r3.y;
  r5.y = dot(cb1[0].yx, float2(0.707107008,-0.707106531));
  r3.yz = r5.xy * r1.zz;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r1.z = dot(r3.yzw, r3.yzw);
  r3.y = dot(r0.xyw, r3.yzw);
  r3.z = rsqrt(r1.z);
  r3.y = saturate(r3.y * r3.z + -cb0[3].w);
  r1.z = saturate(r1.z * cb0[3].z + 1);
  r1.z = r3.y * r1.z + r2.w;
  r3.yz = r5.xy * r1.ww;
  r3.yz = round(r3.yz);
  r6.xy = r3.yz * cb0[1].xy + r1.xy;
  r6.z = 0;
  r3.w = t0.SampleLevel(s0_s, r6.xyz, 0).x;
  r4.yz = cb0[2].xy * r6.xy + cb0[2].zw;
  r3.yz = r4.yz * r3.ww;
  
  r3.y-=stereo.x*(r3.w-stereo.y)*fov;
  
  r3.yzw = r3.yzw + -r2.xyz;
  r1.w = dot(r3.yzw, r3.yzw);
  r2.w = dot(r0.xyw, r3.yzw);
  r3.y = rsqrt(r1.w);
  r2.w = saturate(r2.w * r3.y + -cb0[3].w);
  r1.w = saturate(r1.w * cb0[3].z + 1);
  r1.w = r2.w * r1.w + r3.x;
  r3.xy = r5.xy * r4.xx;
  r3.xy = round(r3.xy);
  r3.xy = r3.xy * cb0[1].xy + r1.xy;
  r3.z = 0;
  r4.z = t0.SampleLevel(s0_s, r3.xyz, 0).x;
  r3.xy = cb0[2].xy * r3.xy + cb0[2].zw;
  r4.xy = r3.xy * r4.zz;
  
  r4.x-=stereo.x*(r4.z-stereo.y)*fov;
  
  r3.xyz = r4.xyz + -r2.xyz;
  r2.w = dot(r3.xyz, r3.xyz);
  r3.x = dot(r0.xyw, r3.xyz);
  r3.y = rsqrt(r2.w);
  r3.x = saturate(r3.x * r3.y + -cb0[3].w);
  r2.w = saturate(r2.w * cb0[3].z + 1);
  r1.w = r3.x * r2.w + r1.w;
  r3.xy = r5.xy * r0.zz;
  r3.xy = round(r3.xy);
  r3.xy = r3.xy * cb0[1].xy + r1.xy;
  r3.z = 0;
  r4.z = t0.SampleLevel(s0_s, r3.xyz, 0).x;
  r1.xy = cb0[2].xy * r3.xy + cb0[2].zw;
  r4.xy = r1.xy * r4.zz;
  
  r4.x-=stereo.x*(r4.z-stereo.y)*fov;
  
  r2.xyw = r4.xyz + -r2.xyz;
  r0.z = dot(r2.xyw, r2.xyw);
  r0.x = dot(r0.xyw, r2.xyw);
  r0.y = rsqrt(r0.z);
  r0.x = saturate(r0.x * r0.y + -cb0[3].w);
  r0.y = saturate(r0.z * cb0[3].z + 1);
  r0.x = r0.x * r0.y + r1.w;
  r0.x = cb0[4].y * r0.x;
  r0.x = r1.z * cb0[4].x + r0.x;
  r0.x = 0.03125 * r0.x;
  r0.y = r2.z * cb0[7].z + 1;
  r0.y = saturate(cb0[7].w * r0.y);
  r0.x = dot(r0.xx, r0.yy);
  o0.x = saturate(1 + -r0.x);
  return;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Generated by Microsoft (R) D3D Shader Disassembler
//
//   using 3Dmigoto v0.6.163 on Thu Apr 20 22:30:31 2023
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Position              0   xyzw        0      POS   float   xy
// TEXCOORD                 0   xy          1     NONE   float
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_TARGET                0   x           0   TARGET   float   x
//
ps_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB0[14], immediateIndexed
dcl_constantbuffer CB1[2], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2darray (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_input_ps_siv linear noperspective v0.xy, position
dcl_output o0.x
dcl_temps 7
round_ni r0.xy, v0.xyxx
mad r0.xy, r0.xyxx, l(4.000000, 4.000000, 0.000000, 0.000000), cb1[1].xyxx
mul r0.zw, r0.xxxy, cb0[1].xxxy
mul r1.xy, r0.zwzz, l(0.250000, 0.250000, 0.000000, 0.000000)
mov r1.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r2.z, r1.xyzx, t0.yzxw, s0, l(0.000000)
div r0.z, cb0[3].x, r2.z
lt r0.w, r0.z, l(1.000000)
if_nz r0.w
  mov o0.x, l(1.000000)
  ret
endif
mad r1.zw, cb0[2].xxxy, r1.xxxy, cb0[2].zzzw
mul r2.xy, r2.zzzz, r1.zwzz
add r0.xy, r0.xyxx, cb0[7].xyxx
ftoi r3.xy, r0.xyxx
mov r3.zw, l(0,0,0,0)
ld_indexable(texture2d)(float,float,float,float) r0.xyw, r3.xyzw, t1.xywz
mad r0.xyw, r0.xyxw, cb0[13].xxxx, cb0[13].yyyy
mul r3.xyz, r0.yyyy, cb0[10].xyzx
mad r3.xyz, r0.xxxx, cb0[9].xyzx, r3.xyzx
mad r0.xyw, r0.wwww, cb0[11].xyxz, r3.xyxz
dp3 r1.z, r0.xywx, r0.xywx
rsq r1.z, r1.z
mul r0.xyw, r0.xyxw, r1.zzzz
mul r1.z, r0.z, l(0.050000)
mad r1.z, cb1[0].z, r1.z, l(1.000000)
mul r3.xy, r1.zzzz, cb1[0].xyxx
round_ne r3.xy, r3.xyxx
mad r3.xy, r3.xyxx, cb0[1].xyxx, r1.xyxx
mov r3.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.z, r3.xyzx, t0.yzxw, s0, l(0.000000)
mad r3.xy, cb0[2].xyxx, r3.xyxx, cb0[2].zwzz
mul r4.xy, r4.zzzz, r3.xyxx
mad r1.w, r0.z, l(0.050000), r1.z
add r3.xyz, -r2.xyzx, r4.xyzx
dp3 r2.w, r3.xyzx, r3.xyzx
dp3 r3.x, r0.xywx, r3.xyzx
rsq r3.y, r2.w
mad_sat r3.x, r3.x, r3.y, -cb0[3].w
mad_sat r2.w, r2.w, cb0[3].z, l(1.000000)
mul r3.yz, r1.wwww, cb1[0].xxyx
round_ne r3.yz, r3.yyzy
mad r4.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r4.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r4.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.xy, cb0[2].xyxx, r4.xyxx, cb0[2].zwzz
mul r3.yz, r3.wwww, r4.xxyx
mad r4.x, r0.z, l(0.050000), r1.w
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mul r4.yz, r4.xxxx, cb1[0].xxyx
round_ne r4.yz, r4.yyzy
mad r5.xy, r4.yzyy, cb0[1].xyxx, r1.xyxx
mov r5.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.w, r5.xyzx, t0.wyzx, s0, l(0.000000)
mad r5.xy, cb0[2].xyxx, r5.xyxx, cb0[2].zwzz
mul r4.yz, r4.wwww, r5.xxyx
mad r0.z, r0.z, l(0.050000), r4.x
add r4.yzw, -r2.xxyz, r4.yyzw
dp3 r3.w, r4.yzwy, r4.yzwy
dp3 r4.y, r0.xywx, r4.yzwy
rsq r4.z, r3.w
mad_sat r4.y, r4.y, r4.z, -cb0[3].w
mad_sat r3.w, r3.w, cb0[3].z, l(1.000000)
mul r3.w, r3.w, r4.y
mad r3.y, r3.y, r3.z, r3.w
mul r3.zw, r0.zzzz, cb1[0].xxxy
round_ne r3.zw, r3.zzzw
mad r5.xy, r3.zwzz, cb0[1].xyxx, r1.xyxx
mov r5.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.w, r5.xyzx, t0.wyzx, s0, l(0.000000)
mad r3.zw, cb0[2].xxxy, r5.xxxy, cb0[2].zzzw
mul r4.yz, r4.wwww, r3.zzwz
add r4.yzw, -r2.xxyz, r4.yyzw
dp3 r3.z, r4.yzwy, r4.yzwy
dp3 r3.w, r0.xywx, r4.yzwy
rsq r4.y, r3.z
mad_sat r3.w, r3.w, r4.y, -cb0[3].w
mad_sat r3.z, r3.z, cb0[3].z, l(1.000000)
mad r3.y, r3.w, r3.z, r3.y
mul r3.zw, cb1[0].xxxy, l(0.000000, 0.000000, 0.707106769, 0.707106769)
mad r5.x, cb1[0].x, l(0.707106769), -r3.w
add r5.y, r3.z, r3.w
mul r4.yz, r1.zzzz, r5.xxyx
round_ne r4.yz, r4.yyzy
mad r6.xy, r4.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r5.zw, cb0[2].xxxy, r6.xxxy, cb0[2].zzzw
mul r4.yz, r4.wwww, r5.zzwz
add r4.yzw, -r2.xxyz, r4.yyzw
dp3 r5.z, r4.yzwy, r4.yzwy
dp3 r4.y, r0.xywx, r4.yzwy
rsq r4.z, r5.z
mad_sat r4.y, r4.y, r4.z, -cb0[3].w
mad_sat r4.z, r5.z, cb0[3].z, l(1.000000)
mul r4.y, r4.z, r4.y
mad r2.w, r3.x, r2.w, r4.y
mul r4.yz, r1.wwww, r5.xxyx
round_ne r4.yz, r4.yyzy
mad r6.xy, r4.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r5.zw, cb0[2].xxxy, r6.xxxy, cb0[2].zzzw
mul r4.yz, r4.wwww, r5.zzwz
add r4.yzw, -r2.xxyz, r4.yyzw
dp3 r3.x, r4.yzwy, r4.yzwy
dp3 r4.y, r0.xywx, r4.yzwy
rsq r4.z, r3.x
mad_sat r4.y, r4.y, r4.z, -cb0[3].w
mad_sat r3.x, r3.x, cb0[3].z, l(1.000000)
mad r3.x, r4.y, r3.x, r3.y
mul r4.yz, r4.xxxx, r5.xxyx
round_ne r4.yz, r4.yyzy
mad r6.xy, r4.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r5.zw, cb0[2].xxxy, r6.xxxy, cb0[2].zzzw
mul r4.yz, r4.wwww, r5.zzwz
add r4.yzw, -r2.xxyz, r4.yyzw
dp3 r3.y, r4.yzwy, r4.yzwy
dp3 r4.y, r0.xywx, r4.yzwy
rsq r4.z, r3.y
mad_sat r4.y, r4.y, r4.z, -cb0[3].w
mad_sat r3.y, r3.y, cb0[3].z, l(1.000000)
mad r3.x, r4.y, r3.y, r3.x
mul r4.yz, r0.zzzz, r5.xxyx
round_ne r4.yz, r4.yyzy
mad r5.xy, r4.yzyy, cb0[1].xyxx, r1.xyxx
mov r5.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.w, r5.xyzx, t0.wyzx, s0, l(0.000000)
mad r5.xy, cb0[2].xyxx, r5.xyxx, cb0[2].zwzz
mul r4.yz, r4.wwww, r5.xxyx
add r4.yzw, -r2.xxyz, r4.yyzw
dp3 r3.y, r4.yzwy, r4.yzwy
dp3 r4.y, r0.xywx, r4.yzwy
rsq r4.z, r3.y
mad_sat r4.y, r4.y, r4.z, -cb0[3].w
mad_sat r3.y, r3.y, cb0[3].z, l(1.000000)
mad r3.x, r4.y, r3.y, r3.x
mad r5.x, cb1[0].x, l(-4.371138829E-08), -cb1[0].y
mad r5.y, cb1[0].y, l(-4.371138829E-08), cb1[0].x
mul r4.yz, r1.zzzz, r5.xxyx
round_ne r4.yz, r4.yyzy
mad r6.xy, r4.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r5.zw, cb0[2].xxxy, r6.xxxy, cb0[2].zzzw
mul r4.yz, r4.wwww, r5.zzwz
add r4.yzw, -r2.xxyz, r4.yyzw
dp3 r3.y, r4.yzwy, r4.yzwy
dp3 r4.y, r0.xywx, r4.yzwy
rsq r4.z, r3.y
mad_sat r4.y, r4.y, r4.z, -cb0[3].w
mad_sat r3.y, r3.y, cb0[3].z, l(1.000000)
mad r2.w, r4.y, r3.y, r2.w
mul r4.yz, r1.wwww, r5.xxyx
round_ne r4.yz, r4.yyzy
mad r6.xy, r4.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r5.zw, cb0[2].xxxy, r6.xxxy, cb0[2].zzzw
mul r4.yz, r4.wwww, r5.zzwz
add r4.yzw, -r2.xxyz, r4.yyzw
dp3 r3.y, r4.yzwy, r4.yzwy
dp3 r4.y, r0.xywx, r4.yzwy
rsq r4.z, r3.y
mad_sat r4.y, r4.y, r4.z, -cb0[3].w
mad_sat r3.y, r3.y, cb0[3].z, l(1.000000)
mad r3.x, r4.y, r3.y, r3.x
mul r4.yz, r4.xxxx, r5.xxyx
round_ne r4.yz, r4.yyzy
mad r6.xy, r4.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r5.zw, cb0[2].xxxy, r6.xxxy, cb0[2].zzzw
mul r4.yz, r4.wwww, r5.zzwz
add r4.yzw, -r2.xxyz, r4.yyzw
dp3 r3.y, r4.yzwy, r4.yzwy
dp3 r4.y, r0.xywx, r4.yzwy
rsq r4.z, r3.y
mad_sat r4.y, r4.y, r4.z, -cb0[3].w
mad_sat r3.y, r3.y, cb0[3].z, l(1.000000)
mad r3.x, r4.y, r3.y, r3.x
mul r4.yz, r0.zzzz, r5.xxyx
round_ne r4.yz, r4.yyzy
mad r5.xy, r4.yzyy, cb0[1].xyxx, r1.xyxx
mov r5.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.w, r5.xyzx, t0.wyzx, s0, l(0.000000)
mad r5.xy, cb0[2].xyxx, r5.xyxx, cb0[2].zwzz
mul r4.yz, r4.wwww, r5.xxyx
add r4.yzw, -r2.xxyz, r4.yyzw
dp3 r3.y, r4.yzwy, r4.yzwy
dp3 r4.y, r0.xywx, r4.yzwy
rsq r4.z, r3.y
mad_sat r4.y, r4.y, r4.z, -cb0[3].w
mad_sat r3.y, r3.y, cb0[3].z, l(1.000000)
mad r3.x, r4.y, r3.y, r3.x
mad r5.x, cb1[0].x, l(-0.707106769), -r3.w
mad r5.y, cb1[0].y, l(-0.707106769), r3.z
mul r3.yz, r1.zzzz, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r2.w, r3.y, r3.z, r2.w
mul r3.yz, r1.wwww, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mul r3.yz, r4.xxxx, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mul r3.yz, r0.zzzz, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r5.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r5.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r5.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r5.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mad r5.x, -cb1[0].y, l(-8.742277657E-08), -cb1[0].x
mad r5.y, cb1[0].x, l(-8.742277657E-08), -cb1[0].y
mul r3.yz, r1.zzzz, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r2.w, r3.y, r3.z, r2.w
mul r3.yz, r1.wwww, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mul r3.yz, r4.xxxx, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mul r3.yz, r0.zzzz, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r5.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r5.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r5.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r5.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mul r3.y, cb1[0].y, l(-0.707106888)
mad r5.x, cb1[0].x, l(-0.707106650), -r3.y
dp2 r5.y, cb1[0].yxyy, l(-0.707106650, -0.707106888, 0.000000, 0.000000)
mul r3.yz, r1.zzzz, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r2.w, r3.y, r3.z, r2.w
mul r3.yz, r1.wwww, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mul r3.yz, r4.xxxx, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mul r3.yz, r0.zzzz, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r5.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r5.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r5.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r5.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mad r5.x, cb1[0].x, l(1.192488064E-08), cb1[0].y
mad r5.y, cb1[0].y, l(1.192488064E-08), -cb1[0].x
mul r3.yz, r1.zzzz, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r2.w, r3.y, r3.z, r2.w
mul r3.yz, r1.wwww, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mul r3.yz, r4.xxxx, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mul r3.yz, r0.zzzz, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r5.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r5.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r5.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r5.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r4.y, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r4.y
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r3.z, r4.y, cb0[3].z, l(1.000000)
mad r3.x, r3.y, r3.z, r3.x
mul r3.y, cb1[0].y, l(-0.707106531)
mad r5.x, cb1[0].x, l(0.707107), -r3.y
dp2 r5.y, cb1[0].yxyy, l(0.707107, -0.707106531, 0.000000, 0.000000)
mul r3.yz, r1.zzzz, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r1.z, r3.yzwy, r3.yzwy
dp3 r3.y, r0.xywx, r3.yzwy
rsq r3.z, r1.z
mad_sat r3.y, r3.y, r3.z, -cb0[3].w
mad_sat r1.z, r1.z, cb0[3].z, l(1.000000)
mad r1.z, r3.y, r1.z, r2.w
mul r3.yz, r1.wwww, r5.xxyx
round_ne r3.yz, r3.yyzy
mad r6.xy, r3.yzyy, cb0[1].xyxx, r1.xyxx
mov r6.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r3.w, r6.xyzx, t0.wyzx, s0, l(0.000000)
mad r4.yz, cb0[2].xxyx, r6.xxyx, cb0[2].zzwz
mul r3.yz, r3.wwww, r4.yyzy
add r3.yzw, -r2.xxyz, r3.yyzw
dp3 r1.w, r3.yzwy, r3.yzwy
dp3 r2.w, r0.xywx, r3.yzwy
rsq r3.y, r1.w
mad_sat r2.w, r2.w, r3.y, -cb0[3].w
mad_sat r1.w, r1.w, cb0[3].z, l(1.000000)
mad r1.w, r2.w, r1.w, r3.x
mul r3.xy, r4.xxxx, r5.xyxx
round_ne r3.xy, r3.xyxx
mad r3.xy, r3.xyxx, cb0[1].xyxx, r1.xyxx
mov r3.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.z, r3.xyzx, t0.yzxw, s0, l(0.000000)
mad r3.xy, cb0[2].xyxx, r3.xyxx, cb0[2].zwzz
mul r4.xy, r4.zzzz, r3.xyxx
add r3.xyz, -r2.xyzx, r4.xyzx
dp3 r2.w, r3.xyzx, r3.xyzx
dp3 r3.x, r0.xywx, r3.xyzx
rsq r3.y, r2.w
mad_sat r3.x, r3.x, r3.y, -cb0[3].w
mad_sat r2.w, r2.w, cb0[3].z, l(1.000000)
mad r1.w, r3.x, r2.w, r1.w
mul r3.xy, r0.zzzz, r5.xyxx
round_ne r3.xy, r3.xyxx
mad r3.xy, r3.xyxx, cb0[1].xyxx, r1.xyxx
mov r3.z, l(0)
sample_l_indexable(texture2darray)(float,float,float,float) r4.z, r3.xyzx, t0.yzxw, s0, l(0.000000)
mad r1.xy, cb0[2].xyxx, r3.xyxx, cb0[2].zwzz
mul r4.xy, r4.zzzz, r1.xyxx
add r2.xyw, -r2.xyxz, r4.xyxz
dp3 r0.z, r2.xywx, r2.xywx
dp3 r0.x, r0.xywx, r2.xywx
rsq r0.y, r0.z
mad_sat r0.x, r0.x, r0.y, -cb0[3].w
mad_sat r0.y, r0.z, cb0[3].z, l(1.000000)
mad r0.x, r0.x, r0.y, r1.w
mul r0.x, r0.x, cb0[4].y
mad r0.x, r1.z, cb0[4].x, r0.x
mul r0.x, r0.x, l(0.031250)
mad r0.y, r2.z, cb0[7].z, l(1.000000)
mul_sat r0.y, r0.y, cb0[7].w
dp2 r0.x, r0.xxxx, r0.yyyy
add_sat o0.x, -r0.x, l(1.000000)
ret
// Approximately 0 instruction slots used

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
