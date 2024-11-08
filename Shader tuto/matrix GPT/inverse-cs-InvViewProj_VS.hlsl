cbuffer b0 : register(b0)
{
    struct
    {
        float4x4 random;
        float4x4 random2;
        float4x4 random3;
        float4x4 random4;
        float4 random5;
        float4x4 ViewToWorld;
    } shadow_decal_data : packoffset(c0);
}

RWBuffer<float4> InvScreenToModelOutputBuffer : register(u0);
float4 inverse_transpose_parallel(float4x4 m, uint pos)
{
    float4x4 invTranspose = transpose(inverse(m)); 
    return invTranspose[pos];
}

[numthreads(4, 1, 1)]
void main(uint3 tid : SV_DispatchThreadID)
{
    InvScreenToModelOutputBuffer[tid.x] = inverse_transpose_parallel(shadow_decal_data.ViewToWorld, tid.x);
}
