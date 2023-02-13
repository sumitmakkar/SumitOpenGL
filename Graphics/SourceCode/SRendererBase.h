#pragma once

//#include "SOGLWindow.h"

class SRendererBase
{
	public:
		SRendererBase();
		~SRendererBase();
		virtual void RenderScene()		   = 0;
		virtual void UpdateScene(float dt) = 0;
		virtual void HandleKeyboardEvents(unsigned char key, int mouse_x, int mouse_y) = 0;
		virtual void HandleKeyboardSpecialEvents(int key, int mouse_x, int mouse_y)    = 0;
		virtual void HandleMouseEvents(int x, int y) = 0;
};