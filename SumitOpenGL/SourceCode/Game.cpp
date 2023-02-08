#include <iostream>
#include "SOGLWindow.h"
#include "SumitOGLMaths.h"

int main(int argc, char* argv[])
{
    Vector2f v(2, 3);
    std::cout << v.x << ", y = " << v.y << std::endl;
    SOGLWindow win(1600, 800, 0, 0, argc, argv, Vector4f(1.0f, 0.0f, 1.0f, 1.0f), "Sumit OpenGL Window");
 	return 0;
}