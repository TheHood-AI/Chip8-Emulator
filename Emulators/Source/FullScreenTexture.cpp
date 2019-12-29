#include "FullScreenTexture.h"
#include <d3d11.h>

void CFullScreenTexture::ClearTexture(float r, float g, float b, float a)
{
	FLOAT color[4];
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
	myContext->ClearRenderTargetView(myRenderTarget, &color[0]);
}

void CFullScreenTexture::ClearDepth(const float aClearDepth, const unsigned int aClearStencil)
{
	myContext->ClearDepthStencilView(myDepth, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, aClearDepth, static_cast<UINT8>(aClearStencil));
}

void CFullScreenTexture::SetAsActiveTarget(CFullScreenTexture* aDepth)
{
	if (aDepth)
	{
		myContext->OMSetRenderTargets(1, &myRenderTarget, aDepth->myDepth);
	}
	else
	{
		myContext->OMSetRenderTargets(1, &myRenderTarget, nullptr);
	}
	myContext->RSSetViewports(1, myViewport);
}

void CFullScreenTexture::SetAsResourceOnSlot(const unsigned int aSlot)
{
	myContext->PSSetShaderResources(aSlot, 1, &myShaderResource);
}

void CFullScreenTexture::SetViewPort(float aTopLeftX, float aTopLeftY, float aWidth, float aHeight, float aMinDepth, float aMaxDepth)
{
	ZeroMemory(&myViewport, sizeof(D3D11_VIEWPORT));

	myViewport->TopLeftX = aTopLeftX;
	myViewport->TopLeftY = aTopLeftY;
	myViewport->Width = aWidth;
	myViewport->Height = aHeight;
	myViewport->MinDepth = aMinDepth;
	myViewport->MaxDepth = aMaxDepth;

	myContext->RSSetViewports(1, myViewport);
}

ID3D11RenderTargetView* CFullScreenTexture::GetRenderTarget()
{
	return myRenderTarget;
}

ID3D11DepthStencilView* CFullScreenTexture::GetDepth()
{
	return myDepth;
}
