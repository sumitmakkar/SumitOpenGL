#pragma once

#include <SumitOGLMaths.h>

class SCamera
{
	private:
		Vector3f m_Pos;
		Vector3f m_Target;	//N of UVN Model (Front)
		Vector3f m_Up;		//V of UVN Model (Up). Note U (Right) will be calculated on the go
		float	 m_Speed = 1.0f;
		int		 m_WindowWidth;
		int		 m_WindowHeight;
		float	 m_AngleH;
		float	 m_AngleV;
		bool	 m_OnUpperEdge;
		bool     m_OnLowerEdge;
		bool	 m_OnLeftEdge;
		bool	 m_OnRightEdge;
		Vector2i m_MousePos;

	public:
		SCamera();
		SCamera(int windowWidth, int windowHeight, const Vector3f& pos, const Vector3f target, const Vector3f& up);
		SCamera(int windowWidth, int windowHeight);
		~SCamera();
		void SetPosition(float x, float y, float z);
		void OnKeyboard(unsigned char key);
		void OnMouse(int x, int y);
		void OnRender();
		Matrix4f GetMatrix();

	private:
		void Init();
		void Update();
};