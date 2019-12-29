#pragma once
struct ID3D11DeviceContext;
struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11ShaderResourceView;
struct D3D11_VIEWPORT;
class CFullScreenTexture
{
public:
	friend class CFullScreenTextureFactory;

	CFullScreenTexture() = default;
	~CFullScreenTexture() = default;


	void ClearTexture(float r, float g, float b, float a);
	void ClearDepth(const float aClearDepth = 1.0f, const unsigned int aClearStencil = 0);
	void SetAsActiveTarget(CFullScreenTexture* aDepth = nullptr);
	void SetAsResourceOnSlot(const unsigned int aSlot);
	void SetViewPort(float aTopLeftX, float aTopLeftY, float aWidth, float aHeight, float aMinDepth = 0.f, float aMaxDepth = 1.f);
	ID3D11RenderTargetView* GetRenderTarget();

	ID3D11DepthStencilView* GetDepth();
private:
	ID3D11DeviceContext* myContext = nullptr;
	ID3D11Texture2D* myTexture = nullptr;
	union
	{
		ID3D11RenderTargetView* myRenderTarget = nullptr;
		ID3D11DepthStencilView* myDepth;
	};
	ID3D11ShaderResourceView* myShaderResource = nullptr;
	D3D11_VIEWPORT* myViewport = nullptr;
};

