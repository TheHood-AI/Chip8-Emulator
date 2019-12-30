#include "GraphicsEngine.h"
#include <cassert>

CGraphicsEngine::CGraphicsEngine() : myWindowHandler()
{
}

bool CGraphicsEngine::Init(const CWindowHandler::SWindowData& aWindowData)
{
	if (!myWindowHandler.Init(aWindowData))
	{
		assert(false);
		return false;
	}
	if (!myFramework.Init(&myWindowHandler))
	{
		assert(false);
		return false;
	}
	if (!myRender.Init(&myFramework))
	{
		assert(false);
		return false;
	}

	return true;
}

void CGraphicsEngine::BegineFrame() const
{
	myFramework.BeginFrame({ 0,0,1,1 });
}

void CGraphicsEngine::EndFrame()
{
	myFramework.EndFrame();
}

void CGraphicsEngine::Render()
{
	myRender.Render();
}
