#include <iostream>
#include <SOGLWindow.h>
#include <SumitOGLMaths.h>
#include <SCamera.h>
#include "Renderer.h"

int main(int argc, char* argv[])
{
    Renderer* renderer = new Renderer();
    SOGLWindow win(1600, 800, 0, 0, argc, argv, Vector4f(0.5f, 0.5f, 0.5f, 1.0f), renderer, "Sumit OpenGL Window");
    renderer->InitShaders();
    win.Update();
 	return 0;
}