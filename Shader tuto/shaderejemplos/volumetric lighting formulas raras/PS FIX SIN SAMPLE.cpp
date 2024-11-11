//HUD VS 5. Bottom screen button in pause menu.
// ---- Created with 3Dmigoto v0.6.163 on Sun Jun 23 22:00:10 2024
cbuffer cb2 : register(b2)
{
  float4 cb2[21];
}

cbuffer cb1 : register(b1)
{
  float4 cb1[4];
}

cbuffer cb0 : register(b0)
{
  float4 cb0[6];
}




// 3Dmigoto declarations
#define cmp -
Texture1D<float4> IniParams : register(t120);
Texture2D<float4> StereoParams : register(t125);
Texture2DArray<float> DepthBuffer : register(t110);

static const float near = 0.00001;
static const float far = 1;

float world_z_from_depth_buffer(float x, float y, int eye)
{
    uint width, height, elements = 0;
    float z;

    DepthBuffer.GetDimensions(width, height, elements);

    x = min(max((x / 2 + 0.5) * width, 0), width - 1);
    y = min(max((-y / 2 + 0.5) * height, 0), height - 1);
    z = DepthBuffer.Load(int4(x, y, eye, 0)).x;
    if (z == 0)
        return 0;

  return (far*near/((z)*near) + (far*z));
}

float adjust_from_depth_buffer(float x, float y, float numsamples, float convmult)
{
    float4 stereo = StereoParams.Load(0);
    float separation = stereo.x; float convergence = stereo.y;
    float old_offset, offset, w, sampled_w, distance;
    uint i;

    // Stereo cursor: To improve the accuracy of the stereo cursor, we
    // sample a number of points on the depth buffer, starting at the near
    // clipping plane and working towards original x + separation.
    //
    // You can think of this as a line in three dimensional space that
    // starts at each eye and stretches out towards infinity. We sample 255
    // points along this line (evenly spaced in the X axis) and compare
    // with the depth buffer to find where the line is first intersected.
    //
    // Note: The reason for sampling 255 points came from a restriction in
    // DX9/SM3 where loops had to run a constant number of iterations and
    // there was no way to set that number from within the shader itself.
    // I'm not sure if the same restriction applies in DX11 with SM4/5 - if
    // it doesn't, we could change this to check each pixel instead for
    // better accuracy.
    //
    // Based on DarkStarSword's stereo crosshair code originally developed
    // for Miasmata, adapted to Unity, then translated to HLSL.

    offset = (near - convergence) * separation*0.2; // Z = X offset from center
    distance = separation - offset;         // Total distance to cover (separation - starting X offset)

    old_offset = offset;
    for (i = 0; i < numsamples; i++) {
        offset += distance / numsamples;

        // Calculate depth for this point on the line:
        w = (separation * convergence*convmult) / (separation - offset);
		
		//sampled_w = world_z_from_depth_buffer(x + offset, y);
        //sampled_w = world_z_from_depth_buffer(x + offset * stereo.z, y);
		
		float left = min((x + offset * stereo.z), 0);
        float right = max((x - offset * stereo.z), 0);
        float left_sampled_w = world_z_from_depth_buffer(left, y, 0);
        float right_sampled_w = world_z_from_depth_buffer(right, y, 1);
        sampled_w = max(left_sampled_w, right_sampled_w);
		
        if (sampled_w == 0)
            return separation;

        // If the sampled depth is closer than the calculated depth,
        // we have found something that intersects the line, so exit
        // the loop and return the last point that was not intersected:
        if (w > sampled_w)
            break;

        old_offset = offset;
    }

    return old_offset;
}

void main(
  float4 v0 : POSITION0,
  float4 v1 : COLOR0,
  float2 v2 : TEXCOORD0,
  out float4 o0 : SV_POSITION0,
  out float4 o1 : COLOR0,
  out float4 o2 : TEXCOORD0,
  out float4 o3 : TEXCOORD1)
{
  float4 r0,r1;
  uint4 bitmask, uiDest;
  float4 fDest;
  
  float4 iniparams11 = IniParams.Load(int2(11,0));
  
  r0.xyzw = cb1[1].xyzw * v0.yyyy;
  r0.xyzw = cb1[0].xyzw * v0.xxxx + r0.xyzw;
  r0.xyzw = cb1[2].xyzw * v0.zzzz + r0.xyzw;
  r0.xyzw = cb1[3].xyzw + r0.xyzw;
  r1.xyzw = cb2[18].xyzw * r0.yyyy;
  r1.xyzw = cb2[17].xyzw * r0.xxxx + r1.xyzw;
  r1.xyzw = cb2[19].xyzw * r0.zzzz + r1.xyzw;
  o0.xyzw = cb2[20].xyzw * r0.wwww + r1.xyzw;
  
  if (o0.w==1 && iniparams11.x==1) {
    o0.x+=adjust_from_depth_buffer(0,0.5,300,10.0);
  }
  
  o1.xyzw = cb0[2].xyzw * v1.xyzw;
  o2.xy = v2.xy * cb0[5].xy + cb0[5].zw;
  o3.xyzw = v0.xyzw;
  return;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Generated by Microsoft (R) D3D Shader Disassembler
//
//   using 3Dmigoto v0.6.163 on Sun Jun 23 22:00:10 2024
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// POSITION                 0   xyzw        0     NONE   float   xyzw
// COLOR                    0   xyzw        1     NONE   float   xyzw
// TEXCOORD                 0   xy          2     NONE   float   xy
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_POSITION              0   xyzw        0      POS   float   xyzw
// COLOR                    0   xyzw        1     NONE   float   xyzw
// TEXCOORD                 0   xy          2     NONE   float   xy
// TEXCOORD                 1   xyzw        3     NONE   float   xyzw
//
vs_4_0
dcl_constantbuffer CB0[6], immediateIndexed
dcl_constantbuffer CB1[4], immediateIndexed
dcl_constantbuffer CB2[21], immediateIndexed
dcl_input v0.xyzw
dcl_input v1.xyzw
dcl_input v2.xy
dcl_output_siv o0.xyzw, position
dcl_output o1.xyzw
dcl_output o2.xy
dcl_output o3.xyzw
dcl_temps 2
mul r0.xyzw, v0.yyyy, cb1[1].xyzw
mad r0.xyzw, cb1[0].xyzw, v0.xxxx, r0.xyzw
mad r0.xyzw, cb1[2].xyzw, v0.zzzz, r0.xyzw
add r0.xyzw, r0.xyzw, cb1[3].xyzw
mul r1.xyzw, r0.yyyy, cb2[18].xyzw
mad r1.xyzw, cb2[17].xyzw, r0.xxxx, r1.xyzw
mad r1.xyzw, cb2[19].xyzw, r0.zzzz, r1.xyzw
mad o0.xyzw, cb2[20].xyzw, r0.wwww, r1.xyzw
mul o1.xyzw, v1.xyzw, cb0[2].xyzw
mad o2.xy, v2.xyxx, cb0[5].xyxx, cb0[5].zwzz
mov o3.xyzw, v0.xyzw
ret
// Approximately 0 instruction slots used

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/