#include "SCamera.h"
#include <FreeGlut\freeglut.h>
#include <iostream>

SCamera::SCamera()
{
	m_Pos = Vector3f(0.0f, 0.0f, 0.0f);
	m_Target = Vector3f(0.0f, 0.0f, 1.0f);
	m_Up = Vector3f(0.0f, 1.0f, 0.0f);
}

SCamera::~SCamera()
{
}

void SCamera::SetPosition(float x, float y, float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

void SCamera::OnKeyboard(unsigned char key)
{
	Vector3f right, left;
	switch (key)
	{
	case GLUT_KEY_UP:
		m_Pos += (m_Target * m_Speed);
		break;

	case GLUT_KEY_DOWN:
		m_Pos -= (m_Target * m_Speed);
		break;

	case GLUT_KEY_LEFT:
		left = m_Target.Cross(m_Up);//Remember shot on point (Square off) by a right handed batsman shot rule, on the destination axis (i.e vector written in the parameters of the cross product).
		left.Normalize();
		left *= m_Speed;
		m_Pos += left;
		break;

	case GLUT_KEY_RIGHT:
		right = m_Up.Cross(m_Target);
		right.Normalize();
		right *= m_Speed;
		m_Pos += right;
		break;

	case GLUT_KEY_PAGE_UP:
		m_Pos.y += m_Speed;
		break;

	case GLUT_KEY_PAGE_DOWN:
		m_Pos.y -= m_Speed;
		break;

	case '+':
		m_Speed += 0.1f;
		break;

	case '-':
		m_Speed -= 0.1f;
		m_Speed = m_Speed < 0.1f ? 0.1f : m_Speed;
		std::cout << "Current Speed : " << m_Speed << std::endl;
		break;
	}

}

Matrix4f SCamera::GetMatrix()
{
	Matrix4f cameraTransformation;
	cameraTransformation.InitCameraTransform(m_Pos, m_Target, m_Up);		// Same as glm::LookAt().
	return cameraTransformation;
}
