#pragma once
#include "FullScreenTexture.h"
#include <dxgiformat.h>

class CDirectXFramework;
struct ID3D11Texture2D;

class CFullScreenTextureFactory
{
public:
	CFullScreenTextureFactory();
	~CFullScreenTextureFactory();

	bool Init(CDirectXFramework* aFramework);

	CFullScreenTexture CreateTexture(float x, float y, DXGI_FORMAT aFormat);
	CFullScreenTexture CreateTexture(ID3D11Texture2D* aTexture);
	CFullScreenTexture CreateDepth(float x, float y, DXGI_FORMAT aFormat);

private:
	CDirectXFramework* myFramework = nullptr;
};

