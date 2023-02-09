#pragma once

#include <SumitOGLMaths.h>

class SCamera
{
	private:
		Vector3f m_Pos;
		Vector3f m_Target;	//N of UVN Model (Front)
		Vector3f m_Up;		//V of UVN Model (Up). Note U (Right) will be calculated on the go
		float	 m_Speed = 1.0f;

	public:
		SCamera();
		~SCamera();
		void SetPosition(float x, float y, float z);
		void OnKeyboard(unsigned char key);
		Matrix4f GetMatrix();
};