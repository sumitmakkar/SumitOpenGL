#pragma once
#include "Glew\glew.h"
#include "FreeGlut\glut.h"
#include "FreeGlut\freeglut.h"
#include <iostream>
#include <string>

class SOGLWindow
{
	private:
		int			 m_WindowStartingXCoordinate;
		int			 m_WindowStartingYCoordinate;
		std::string  m_WindowTitleString;

		int			 m_WindowWidth;
		int			 m_WindowHeight;
		

	public:
		SOGLWindow(int argc, char* argv[], std::string windowTitleString = "OpenGlWindow");
		SOGLWindow(int windowWidth, int windowHeight, int windowStartingXCoordinate, int windowStartingYCoordinate, int argc, char* argv[], std::string windowTitleString = "OpenGlWindow");
		~SOGLWindow();

	private:
		void CreateOpenGLWindow(int argc, char* argv[]);
		void InitializeWindow(int argc, char* argv[]);
		bool InitializeGlew();
		void SetWindowBackgroundColour();
		void EnableWindowParameters();
		void InitializeGlutCallbacks();
		static void RenderSceneCB();
};