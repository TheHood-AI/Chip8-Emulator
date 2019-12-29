#include "ShaderStructs.hlsli"

PixelOutput main(VertexToPixel input)
{
	PixelOutput returnValue;
	float3 resource = FullscreenTexture1.Sample(DefaultSampler, input.myUV.xy).rgb;

	returnValue.myColor.rgb = resource;

	returnValue.myColor.a = 1.0f;
	return returnValue;
}