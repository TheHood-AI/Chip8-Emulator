#include "FullScreenTextureFactory.h"
#include <cassert>
#include <d3d11.h>
#include "DirectXFramework.h"
#pragma warning(disable : 26812)
CFullScreenTextureFactory::CFullScreenTextureFactory()
{
}

CFullScreenTextureFactory::~CFullScreenTextureFactory()
{
}

bool CFullScreenTextureFactory::Init(CDirectXFramework* aFramework)
{
	if (!aFramework)
	{
		return false;
	}
	myFramework = aFramework;
	return true;
}

CFullScreenTexture CFullScreenTextureFactory::CreateTexture(float x, float y, DXGI_FORMAT aFormat)
{
	HRESULT result;

	D3D11_TEXTURE2D_DESC textureDesc = { 0 };
	textureDesc.Width = static_cast<unsigned int>(x);
	textureDesc.Height = static_cast<unsigned int>(y);
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = aFormat;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	ID3D11Texture2D* texture = nullptr;
	result = myFramework->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &texture);
	if (FAILED(result))
	{
		assert(false);
	}

	CFullScreenTexture returnTexture;
	returnTexture = CreateTexture(texture);

	ID3D11ShaderResourceView* shaderResource = nullptr;
	result = myFramework->GetDevice()->CreateShaderResourceView(texture, nullptr, &shaderResource);
	if (FAILED(result))
	{
		assert(false);
	}
	returnTexture.myShaderResource = shaderResource;
	return returnTexture;
}

CFullScreenTexture CFullScreenTextureFactory::CreateTexture(ID3D11Texture2D* aTexture)
{
	HRESULT result;

	ID3D11RenderTargetView* renderTarget = nullptr;
	result = myFramework->GetDevice()->CreateRenderTargetView(aTexture, nullptr, &renderTarget);
	if (FAILED(result))
	{
		assert(false);
	}

	D3D11_VIEWPORT* viewport = nullptr;
	if (aTexture)
	{
		D3D11_TEXTURE2D_DESC textureDescription;
		aTexture->GetDesc(&textureDescription);
		viewport = new D3D11_VIEWPORT({ 0.0f, 0.0f, static_cast<float>(textureDescription.Width), static_cast<float>(textureDescription.Height), 0.0f, 1.0f });
	}
	CFullScreenTexture returnTexture;
	returnTexture.myContext = myFramework->GetContext();
	returnTexture.myTexture = aTexture;
	returnTexture.myRenderTarget = renderTarget;
	returnTexture.myViewport = viewport;
	return returnTexture;

}

CFullScreenTexture CFullScreenTextureFactory::CreateDepth(float x, float y, DXGI_FORMAT aFormat)
{
	HRESULT result;

	D3D11_TEXTURE2D_DESC textureDesc = { 0 };
	textureDesc.Width = static_cast<unsigned int>(x);
	textureDesc.Height = static_cast<unsigned int>(y);
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = aFormat;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	ID3D11Texture2D* texture = nullptr;
	result = myFramework->GetDevice()->CreateTexture2D(&textureDesc, nullptr, &texture);
	if (FAILED(result))
	{
		assert(false);
	}

	ID3D11DepthStencilView* depth = nullptr;
	result = myFramework->GetDevice()->CreateDepthStencilView(texture, nullptr, &depth);
	if (FAILED(result))
	{
		assert(false);
	}

	D3D11_VIEWPORT* viewport = new D3D11_VIEWPORT({ 0.0f, 0.0f, x, y, 0.0f, 1.0f });

	CFullScreenTexture returnDepth;
	returnDepth.myContext = myFramework->GetContext();
	returnDepth.myTexture = texture;
	returnDepth.myDepth = depth;
	returnDepth.myViewport = viewport;
	return returnDepth;
}
