#include <iostream>
#include <SOGLWindow.h>
#include <SumitOGLMaths.h>
#include <SCamera.h>
#include "Renderer.h"

int main(int argc, char* argv[])
{
    //Game Window must be created first because it has glew init
    SOGLWindow gameWindow(1600, 800, 0, 0, argc, argv, Vector4f(0.0f, 0.0f, 0.0f, 1.0f), "Sumit OpenGL Window");
    Renderer*  renderer = new Renderer();
    gameWindow.UpdateRenderer(renderer);//Update renderer must be called because Game Window need it to call render and update methods
    gameWindow.UpdateFrame();
 	return 0;
}