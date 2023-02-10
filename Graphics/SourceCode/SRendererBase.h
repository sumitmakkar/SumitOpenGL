#pragma once

//#include "SOGLWindow.h"

class SRendererBase
{
	public:
		SRendererBase();
		~SRendererBase();
		virtual void RenderScene()		   = 0;
		virtual void UpdateScene(float dt) = 0;
};