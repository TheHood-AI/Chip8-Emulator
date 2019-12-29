Texture2D FullscreenTexture1 : register(t0);
Texture2D FullscreenTexture2: register(t1);

SamplerState DefaultSampler	: register(s0);

cbuffer FrameBuffer : register(b0)
{
	float4 pixelData[64*32];
}

struct VertexInput
{
	unsigned int myIndex : SV_VertexID;
};

struct VertexToPixel
{
	float4 myPosition : SV_POSITION;
	float2 myUV : UV;
};

struct PixelOutput
{
	float4 myColor : SV_TARGET;
};