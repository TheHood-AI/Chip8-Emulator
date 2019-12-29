#include "ShaderStructs.hlsli"

PixelOutput main(VertexToPixel input, float4 pixelPosition : SV_Position)
{
	PixelOutput returnValue;
	returnValue.myColor.rgb = float3(0, 0, 0);
	int x = floor(pixelPosition.x) * ( 64.f / 600.f  );
	int y = floor(pixelPosition.y) * (32.f / 480.f  );
	int index = y * 64 + x;
	//j * 4 + i
	if (pixelData[index].r == 1) {
		returnValue.myColor.rgb = float3(0, 1, 1);
	}
	returnValue.myColor.a = 1.0f;
	return returnValue;
}