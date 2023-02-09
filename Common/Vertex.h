#pragma once

#include "SumitOGLMaths.h"

struct Vertex
{
	Vector3f pos;
	Vector3f colour;
	
	Vertex() {}
	
	Vertex(float x, float y, float z = 0.0f)
	{
		pos = Vector3f(x, y, z);
		float red   = (float)rand() / (float)RAND_MAX;
		float green = (float)rand() / (float)RAND_MAX;
		float blue  = (float)rand() / (float)RAND_MAX;

		colour		= Vector3f(red, green, blue);
	}
};