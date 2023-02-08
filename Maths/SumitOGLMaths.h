#pragma once
#include <iostream>

struct Vector2f
{
	float x, y;

	Vector2f(float xValue, float yValue) : x(xValue), y(yValue) {}
};

struct Vector3f
{
	float x;
	float y;
	float z;

	Vector3f(float xValue, float yValue, float zValue) : x(xValue), y(yValue), z(zValue) {}
};

struct Vector4f
{
	float x;
	float y;
	float z;
	float w;

	Vector4f(float xValue, float yValue, float zValue, float wValue) : x(xValue), y(yValue), z(zValue), w(wValue) {}
};

class SumitOGLMaths
{
	
};