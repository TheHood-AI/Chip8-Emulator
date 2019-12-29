#pragma once
#include "WindowHandler.h"
#include "DirectXFramework.h"
#include "Renderer.h"
class CGraphicsEngine
{
public:
	CGraphicsEngine();
	bool Init(const CWindowHandler::SWindowData& aWindowData);
	void BegineFrame()const;
	void EndFrame();
	void Render();
private:
	CWindowHandler myWindowHandler;
	CDirectXFramework myFramework;
	CRenderer myRender;
};

