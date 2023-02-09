#pragma once

#include <SumitOGLMaths.h>

class SWorldTransform
{
	private:
		float	 m_Scale = 1.0f;
		Vector3f m_Rotation = Vector3f(0.0f, 0.0f, 0.0f);
		Vector3f m_Position = Vector3f(0.0f, 0.0f, 0.0f);

	public:
		SWorldTransform();
		~SWorldTransform();

		void SetPosition(float x, float y, float z);
		void SetScale(float scale);
		void SetRotation(float x, float y, float z);

		void Rotate(float x, float y, float z);

		Matrix4f GetMatrix();
};