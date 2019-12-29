#include "DirectXFramework.h"
#include <d3d11.h>
#include "WindowHandler.h"

CDirectXFramework::CDirectXFramework()
{
	myDevice = nullptr;
	myDeviceContext = nullptr;
	myBackBuffer = nullptr;
	mySwapChain = nullptr;
}

CDirectXFramework::~CDirectXFramework()
{
	myDevice = nullptr;
	myDeviceContext = nullptr;
	myBackBuffer = nullptr;
	mySwapChain = nullptr;
}

bool CDirectXFramework::Init(CWindowHandler* aWindowHandler)
{
	DXGI_SWAP_CHAIN_DESC swapchainDescription = {};
	swapchainDescription.BufferCount = 1;
	swapchainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDescription.OutputWindow = aWindowHandler->GetWindowHandle();
	swapchainDescription.SampleDesc.Count = 1;
	swapchainDescription.Windowed = true;

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		nullptr, 0, D3D11_SDK_VERSION,
		&swapchainDescription, &mySwapChain,
		&myDevice, nullptr, &myDeviceContext);

	if (FAILED(result))
	{
		return false;
	}

	ID3D11Texture2D* backbufferTexture;
	result = mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbufferTexture);
	if (FAILED(result))
	{
		return false;
	}
	result = myDevice->CreateRenderTargetView(backbufferTexture, nullptr, &myBackBuffer);
	if (FAILED(result))
	{
		return false;
	}

	result = backbufferTexture->Release();

	if (FAILED(result))
	{
		return false;
	}

	myDeviceContext->OMSetRenderTargets(1, &myBackBuffer, nullptr);
	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(aWindowHandler->GetWidth());
	viewport.Height = static_cast<float>(aWindowHandler->GetHeight());
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	myDeviceContext->RSSetViewports(1, &viewport);

	//DXGI_MODE_DESC temp;
	//temp.Width = 64;
	//temp.Height = 32;
	//temp.Scaling = DXGI_MODE_SCALING_STRETCHED;
	//
	//result = mySwapChain->ResizeTarget(&temp);


	return true;
}

ID3D11Texture2D* CDirectXFramework::GetBackBuffer()
{
	ID3D11Texture2D* backbuffer;
	mySwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
	return backbuffer;
}

void CDirectXFramework::BeginFrame(std::array<float, 4> aClearColor)const
{
	myDeviceContext->ClearRenderTargetView(myBackBuffer, &aClearColor[0]);
}

void CDirectXFramework::EndFrame() const
{
	mySwapChain->Present(1, 0);
}

ID3D11DeviceContext* CDirectXFramework::GetContext() const
{
	return myDeviceContext;
}

ID3D11Device* CDirectXFramework::GetDevice() const
{
	return myDevice;
}


