struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 texcoord : TEXCOORD;
};

Texture2D Texture : register(t0);
sampler TextureSampler : register(s0);

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    return Texture.Sample(TextureSampler, input.texcoord);
}