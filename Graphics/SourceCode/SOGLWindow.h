#pragma once
#include "Glew\glew.h"
#include "FreeGlut\glut.h"
#include "FreeGlut\freeglut.h"
#include <iostream>
#include <string>
#include <SumitOGLMaths.h>
#include "SCamera.h"
#include "SRendererBase.h"

class SOGLWindow
{
	private:
		int			   m_WindowStartingXCoordinate;
		int			   m_WindowStartingYCoordinate;
		std::string    m_WindowTitleString;
					   
		int			   m_WindowWidth;
		int			   m_WindowHeight;
		Vector4f	   m_WindowBackgroundColour;

		SRendererBase* m_renderer = NULL;

	public:
		SOGLWindow(int argc, char* argv[], Vector4f windowBackgroundColour, SRendererBase* renderer, std::string windowTitleString = "OpenGlWindow");
		SOGLWindow(int windowWidth, int windowHeight, int windowStartingXCoordinate, int windowStartingYCoordinate, int argc, char* argv[], Vector4f windowBackgroundColour, SRendererBase* renderer, std::string windowTitleString = "OpenGlWindow");
		~SOGLWindow();
		void UpdateFrame();

	private:
		void CreateOpenGLWindow(int argc, char* argv[]);
		void InitializeWindow(int argc, char* argv[]);
		bool InitializeGlew();
		void SetWindowBackgroundColour();
		void EnableWindowParameters();
		// Static Functions
		static void RenderSceneCB();
		static void KeyboardCB(unsigned char key, int mouse_x, int mouse_y);
		static void SpecialKeyboardCB(int key, int mouse_x, int mouse_y);
};