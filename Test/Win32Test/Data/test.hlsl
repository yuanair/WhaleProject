

cbuffer cbPerFrame : register( b1 )
{
    // pixel
    float3        g_lightDir                : packoffset( c0 );
    float        g_ambient                  : packoffset( c0.w );
};

cbuffer cbPerObject : register( b0 )
{
    // pixel
    float4        g_objectColor             : packoffset( c0 );

    // vertex
    matrix        g_worldViewProjection     : packoffset( c0 );
    matrix        g_world                   : packoffset( c4 );
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
	float4 positionCS       : SV_POSITION;
	float4 color            : COLOR;
	float3 normalOS         : NORMAL;
    float2 texcoord         : TEXCOORD0;
};

Texture2D    g_MainTexture      : register( t0 );
SamplerState g_LinearSampler    : register( s0 );

void vertex(in Vertex input, out Pixel output)
{
    output.positionCS = input.positionOS;
    output.color = input.color;
    output.normalOS = input.normalOS;
    output.texcoord = input.texcoord;
}

float4 pixel(in Pixel input) : SV_TARGET
{
    return g_MainTexture.Sample(g_LinearSampler, input.texcoord);
    // return float4(input.texcoord, 0.0f, 1.0f);
    //return float4((input.positionCS.xyz + float3(0.5f, 0.5f, 0.5f)) * 0.1f, 1.0f);
    // return input.color;
}
