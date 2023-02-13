#include "SCamera.h"
#include <FreeGlut\freeglut.h>
#include <iostream>

static int	 MARGIN	   = 10;
static float EDGE_STEP = 1.0f;

SCamera::SCamera()
{
	m_Pos	 = Vector3f(0.0f, 0.0f, 0.0f);
	m_Target = Vector3f(0.0f, 0.0f, 1.0f);
	m_Up	 = Vector3f(0.0f, 1.0f, 0.0f);
}

SCamera::SCamera(int windowWidth, int windowHeight, const Vector3f& pos, const Vector3f target, const Vector3f& up)
{
	m_WindowWidth  = windowWidth;
	m_WindowHeight = windowHeight;
	m_Pos		   = pos;
	m_Target	   = target;
	m_Up		   = up;
	m_Target.Normalize();
	m_Up.Normalize();
	Init();
}

SCamera::SCamera(int windowWidth, int windowHeight)
{
	m_WindowWidth  = windowWidth;
	m_WindowHeight = windowHeight;
	m_Pos		   = Vector3f(0.0f, 0.0f, 0.0f);
	m_Target	   = Vector3f(0.0f, 0.0f, 1.0f);
	m_Up		   = Vector3f(0.0f, 1.0f, 0.0f);
	Init();
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

void SCamera::OnMouse(int x, int y)
{
	int deltaX = x - m_MousePos.x;
	int deltaY = y - m_MousePos.y;

	m_MousePos.x = x;
	m_MousePos.y = y;

	m_AngleH += (float)deltaX / 20.0f;
	m_AngleV += (float)deltaY / 50.0f;

	// Checking for X (Horizontal)
	if (deltaX == 0)
	{
		if (x <= MARGIN) { m_OnLeftEdge = true; }
		else if (x >= (m_WindowWidth - MARGIN)) { m_OnRightEdge = true; }
	}
	else
	{
		m_OnLeftEdge = false;
		m_OnRightEdge = false;
	}

	//Checking for Y (Verical)
	if (deltaY == 0)
	{
		if (y <= MARGIN) { m_OnUpperEdge = true; }
		else if (y >= (m_WindowHeight - MARGIN)) { m_OnLowerEdge = true; }
	}
	else
	{
		m_OnUpperEdge = false;
		m_OnLowerEdge = false;
	}

	Update();
}

void SCamera::RenderForMouseEdgeCases()
{
	bool shouldUpdate = false;
	if (m_OnLeftEdge)
	{
		m_AngleH -= EDGE_STEP;
		shouldUpdate = true;
	}
	else if (m_OnRightEdge)
	{
		m_AngleH += EDGE_STEP;
		shouldUpdate = true;
	}

	if (m_OnUpperEdge && m_AngleV > -90.0f)
	{
		m_AngleV -= EDGE_STEP;
		shouldUpdate = true;
	}
	else if (m_OnLowerEdge && m_AngleV < 90.0f)
	{
		m_AngleV += EDGE_STEP;
		shouldUpdate = true;
	}

	if (shouldUpdate) { Update(); }
}

Matrix4f SCamera::GetMatrix()
{
	Matrix4f cameraTransformation;
	cameraTransformation.InitCameraTransform(m_Pos, m_Target, m_Up);		// Same as glm::LookAt().
	return cameraTransformation;
}

void SCamera::Init()
{
	Vector3f HTarget(m_Target.x, 0.0f, m_Target.z);
	HTarget.Normalize();

	float angle = ToDegree(asin(abs(HTarget.z)));

	if (HTarget.z >= 0)
	{
		if (HTarget.x >= 0) { m_AngleH = 360.0f - angle; }
		else { m_AngleH = 180.0f + angle; }
	}
	else
	{
		if (HTarget.x >= 0) { m_AngleH = angle; }
		else { m_AngleH = 180.0f - angle; }
	}

	m_AngleV = -ToDegree(abs(asin(m_Target.y)));

	m_OnLeftEdge = false;
	m_OnUpperEdge = false;
	m_OnRightEdge = false;
	m_OnLowerEdge = false;

	m_MousePos.x = m_WindowWidth / 2;
	m_MousePos.y = m_WindowHeight / 2;
}

void SCamera::Update()
{
	Vector3f yAxis(0.0f, 1.0f, 0.0f);

	//Rotate the View Vector by the horizontal angle around the vertical axis
	Vector3f view(1.0f, 0.0f, 0.0f);
	view.Rotate(m_AngleH, yAxis);
	view.Normalize();

	//Rotate the View Vector by the vertical angle around the horizontal axis
	Vector3f U = yAxis.Cross(view);	//U
	view.Rotate(m_AngleV, U);

	m_Target = view;
	m_Target.Normalize();	//N

	m_Up = m_Target.Cross(U);
	m_Up.Normalize();	//V
}