#include <iostream>
#include <SOGLWindow.h>
#include <SumitOGLMaths.h>
#include <SCamera.h>
#include "Renderer.h"

int main(int argc, char* argv[])
{
    SCamera* camera    = new SCamera();
    Renderer* renderer = new Renderer();
    SOGLWindow win(1600, 800, 0, 0, argc, argv, Vector4f(1.0f, 0.0f, 1.0f, 1.0f), camera, renderer, "Sumit OpenGL Window");
 	return 0;
}