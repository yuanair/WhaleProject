
struct Vertex
{
    float4 positionOS : POSITION;
    float4 color : COLOR;
};

struct Pixel
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

void vertex(in Vertex input, out Pixel output)
{
    output.position = input.positionOS;
    output.color = input.color;
}

float4 pixel(in Pixel input) : SV_TARGET
{
    return input.color;
}
