#pragma once
#include "FullScreenTexture.h"
#include "FullScreenTextureFactory.h"
class CDirectXFramework;
struct ID3D11DeviceContext;
struct ID3D11Buffer;
struct ID3D11Device;
class CRenderer
{
public:
	CRenderer();
	~CRenderer() = default;
	bool Init(CDirectXFramework* aFramework);
	void Render();
private:
	void  Copy();
	void LoadCopyShader(ID3D11Device* aDevice);

	struct Color
	{
		float r;
		float g;
		float b;
		float a;
	};

	struct SFrameBuffer
	{
		CRenderer::Color myPixelData[64 * 32];
	} myFrameBufferData;

	ID3D11DeviceContext* myContext;
	struct ID3D11VertexShader* myVertexShader;
	struct ID3D11PixelShader* myPixelShader;
	struct ID3D11PixelShader* myCopyShader;
	ID3D11Buffer* myFrameBuffer;
	ID3D11Buffer* myObjectBuffer;
	CFullScreenTexture myBackBuffer;
	CFullScreenTexture myEmulatorTexture;
	CFullScreenTextureFactory* myFactory;
};

