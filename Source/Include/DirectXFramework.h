#pragma once
#include <array>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
class CWindowHandler;

class CDirectXFramework
{
public:
	CDirectXFramework();
	~CDirectXFramework();
	bool Init(CWindowHandler* aWindowHandler);
	ID3D11Texture2D* GetBackBuffer();
	void BeginFrame(std::array<float, 4> aClearColor)const;
	void EndFrame() const;
	ID3D11DeviceContext* GetContext()const;
	ID3D11Device* GetDevice()const;
private:
	IDXGISwapChain* mySwapChain;
	ID3D11Device* myDevice;
	ID3D11DeviceContext* myDeviceContext;
	ID3D11RenderTargetView* myBackBuffer;
};

