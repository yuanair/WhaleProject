

cbuffer cbPerFrame : register( b1 )
{
    // pixel
    float3        g_lightDir                : packoffset( c0 );
    float        g_ambient                : packoffset( c0.w );
};

cbuffer cbPerObject : register( b0 )
{
    // pixel
    float4        g_objectColor            : packoffset( c0 );

    // vertex
    matrix        g_worldViewProjection    : packoffset( c0 );
    matrix        g_world                : packoffset( c4 );
};

struct Vertex
{
    float4 positionOS       : POSITION;
    float4 color            : COLOR;
    float3 normalOS         : NORMAL;
    float2 texcoord         : TEXCOORD0;
};

struct Pixel
{
	float4 position         : SV_POSITION;
	float4 color            : COLOR;
	float3 normal           : NORMAL;
    float2 texcoord         : TEXCOORD0;
};

Texture2D    g_txDiffuse    : register( t0 );
SamplerState g_samLinear    : register( s0 );

void vertex(in Vertex input, out Pixel output)
{
    output.position = input.positionOS;
    output.color = input.color;
    output.normal = input.normalOS;
    output.texcoord = input.texcoord;
}

float4 pixel(in Pixel input) : SV_TARGET
{
    return float4(input.texcoord, 0.0f, 1.0f);
}
