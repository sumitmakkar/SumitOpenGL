#pragma once

#include "SumitOGLMaths.h"

struct Vertex
{
	Vector3f pos;
	Vector3f colour;
	Vector2f texture;
	
	Vertex() {}

	Vertex(Vector3f* position, Vector3f* col, Vector2f* tex)
	{
		if (position) { pos     = *position; }
		if (col)	  { colour  = *col; }
		else
		{
			float red = (float)rand() / (float)RAND_MAX;
			float green = (float)rand() / (float)RAND_MAX;
			float blue = (float)rand() / (float)RAND_MAX;

			colour = Vector3f(red, green, blue);
		}
		if (tex)	  { texture = *tex; }
	}
	
	/*Vertex(float x, float y, float z = 0.0f)
	{
		pos = Vector3f(x, y, z);
		float red   = (float)rand() / (float)RAND_MAX;
		float green = (float)rand() / (float)RAND_MAX;
		float blue  = (float)rand() / (float)RAND_MAX;

		colour		= Vector3f(red, green, blue);
	}*/
};