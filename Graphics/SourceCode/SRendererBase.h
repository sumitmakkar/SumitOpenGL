#pragma once

//#include "SOGLWindow.h"

class SRendererBase
{
	public:
		SRendererBase();
		~SRendererBase();
		virtual void RenderScene()		   = 0;
		virtual void UpdateScene(float dt) = 0;
		virtual void HandleMouseAndKeyboardEvents(unsigned char key, int mouse_x, int mouse_y) = 0;
		virtual void HandleMoouseAndKeyboardSpecialEvents(int key, int mouse_x, int mouse_y)   = 0;
};