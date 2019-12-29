#include "Renderer.h"
#include "DirectXFramework.h"
#include <d3d11.h>
#include <fstream>
#include <cassert>
#include "Chip8.h"

CRenderer::CRenderer()
	: myContext(nullptr)
	, myFrameBuffer(nullptr)
	, myObjectBuffer(nullptr)
	, myFactory(new CFullScreenTextureFactory())
	, myCopyShader(nullptr)
	, myFrameBufferData()
	, myPixelShader(nullptr)
	, myVertexShader(nullptr)
{
}

bool CRenderer::Init(CDirectXFramework* aFramework)
{
	if (!aFramework)
		return false;

	myContext = aFramework->GetContext();

	if (!myContext)
		return false;

	ID3D11Device* device = aFramework->GetDevice();
	if (!device)
		return false;

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	bufferDesc.ByteWidth = sizeof(SFrameBuffer);
	HRESULT result = device->CreateBuffer(&bufferDesc, nullptr, &myFrameBuffer);
	if (FAILED(result))
		return false;

	std::ifstream vsFile;
	vsFile.open("../Workbed/Shaders/VertexShader.cso", std::ios::binary);
	std::string vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	ID3D11VertexShader* vertexShader;
	result = device->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);

	if (FAILED(result))
	{
		return false;
	}
	vsFile.close();

	std::ifstream psFile;
	psFile.open("../Workbed/Shaders/PixelShader.cso", std::ios::binary);
	std::string psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };
	ID3D11PixelShader* pixelShader;
	result = device->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);
	if (FAILED(result))
	{
		return false;
	}
	psFile.close();

	LoadCopyShader(device);


	ID3D11Texture2D* backbufferTexture = aFramework->GetBackBuffer();
	if (!backbufferTexture)
	{
		assert(false);
		return false;
	}

	if (!myFactory->Init(aFramework))
	{
		assert(false);
	}

	myBackBuffer = myFactory->CreateTexture(backbufferTexture);
	myEmulatorTexture = myFactory->CreateTexture(600, 480, DXGI_FORMAT_R8G8B8A8_UNORM);


	myVertexShader = vertexShader;
	myPixelShader = pixelShader;

	return true;
}

void CRenderer::Render()
{
	D3D11_MAPPED_SUBRESOURCE bufferData;
	/*windowData.myHeight = 480;
	windowData.myWidth = 600;*/
	for (int i = 0; i < 64 * 32; ++i)
	{
		myFrameBufferData.myPixelData[i].r = Chip8::myGfx[i];
		myFrameBufferData.myPixelData[i].g = Chip8::myGfx[i];
		myFrameBufferData.myPixelData[i].b = Chip8::myGfx[i];
		myFrameBufferData.myPixelData[i].a = Chip8::myGfx[i];

		//myFrameBufferData.myPixelData[i].r = 0;
		//myFrameBufferData.myPixelData[i].g = 0;
		//myFrameBufferData.myPixelData[i].b = 0;
		//myFrameBufferData.myPixelData[i].a = 0;
	}

	//for (int i = 0; i < 64; ++i)
	//{
	//	myFrameBufferData.myPixelData[i].r = 1;
	//	myFrameBufferData.myPixelData[i].g = 1;
	//	myFrameBufferData.myPixelData[i].b = 1;
	//	myFrameBufferData.myPixelData[i].a = 1;
	//}
	/*myFrameBufferData.myPixelData[2].r = 1;
	myFrameBufferData.myPixelData[2].g = 1;
	myFrameBufferData.myPixelData[2].b = 1;
	myFrameBufferData.myPixelData[2].a = 1;

	myFrameBufferData.myPixelData[3].r = 1;
	myFrameBufferData.myPixelData[3].g = 1;
	myFrameBufferData.myPixelData[3].b = 1;
	myFrameBufferData.myPixelData[3].a = 1;*/

	/*int t = 0;
	for (int i = 0; i < 32; ++i)
	{
		for (int j = 0; j < 64; ++j)
		{
			int index = i * 32 + j;
			auto temp = myFrameBufferData.myPixelData[index];
			t = temp;
		}
	}*/

	myEmulatorTexture.SetAsActiveTarget();

	ZeroMemory(&bufferData, sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT result = myContext->Map(myFrameBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &bufferData);
	if (FAILED(result))
		return;
	memcpy(bufferData.pData, &myFrameBufferData, sizeof(SFrameBuffer));
	myContext->Unmap(myFrameBuffer, 0);

	myContext->PSSetConstantBuffers(0, 1, &myFrameBuffer);

	myContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	myContext->IASetInputLayout(nullptr);
	myContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	myContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);

	myContext->VSSetShader(myVertexShader, nullptr, 0);
	myContext->PSSetShader(myPixelShader, nullptr, 0);

	myContext->Draw(3, 0);


	Copy();


}

void CRenderer::Copy()
{
	myBackBuffer.SetAsActiveTarget();
	myEmulatorTexture.SetAsResourceOnSlot(0);
	myContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	myContext->IASetInputLayout(nullptr);
	myContext->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
	myContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);

	myContext->VSSetShader(myVertexShader, nullptr, 0);
	myContext->PSSetShader(myCopyShader, nullptr, 0);

	myContext->Draw(3, 0);
}

void CRenderer::LoadCopyShader(ID3D11Device* aDevice)
{
	std::ifstream copyFile;
	copyFile.open("../Workbed/Shaders/CopyShader.cso", std::ios::binary);
	std::string copyData = { std::istreambuf_iterator<char>(copyFile), std::istreambuf_iterator<char>() };
	ID3D11PixelShader* copyShader;
	HRESULT result = aDevice->CreatePixelShader(copyData.data(), copyData.size(), nullptr, &copyShader);
	if (FAILED(result))
	{
		assert(false);
	}
	copyFile.close();
	myCopyShader = copyShader;
}
