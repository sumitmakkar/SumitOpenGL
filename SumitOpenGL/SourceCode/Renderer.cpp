#include "Renderer.h"
#include "SWorldTransform.h"
#include <iostream>

Renderer::Renderer(int windowWidth, int windowHeight)
{
	m_fov		   = 45.0f;
	m_ZNear		   = 1.0f;
	m_ZFar		   = 10.0f;
	m_WindowWidth  = windowWidth;
	m_WindowHeight = windowHeight;
	m_PersProjInfo = { m_fov, (float)m_WindowWidth, (float)m_WindowHeight, m_ZNear, m_ZFar };
}

Renderer::~Renderer()
{
}

void Renderer::InitShaders()
{
	m_BasicShader = SShadersBase(m_VSFileName, m_FSFileName);
	m_Cube = new BasicCube();
}

void Renderer::RenderScene()
{
	if (!m_Cube) { return; }
	m_BasicShader.UseShader();
	m_Cube->RenderMesh();
}

void Renderer::UpdateScene(float dt)
{
#ifdef _WIN64
	float YRotationAngle = 0.5f;
#else
	float YRotationAngle = 0.2f;
#endif

	SWorldTransform& cubeWorldTransform = m_Cube->GetWorldTransform();
	cubeWorldTransform.SetPosition(0.0f, 0.0f, 2.0f);
	cubeWorldTransform.Rotate(0.0f, YRotationAngle, 0.0f);
	Matrix4f world = cubeWorldTransform.GetMatrix();

	Matrix4f view = m_GameCamera.GetMatrix();

	Matrix4f projection;
	projection.InitPersProjTransform(m_PersProjInfo);

	Matrix4f finalMatrix = projection * view * world;

	m_gWVPLocation = m_BasicShader.GetUniformVariableLocation("gWorldViewProjection");

	glUniformMatrix4fv(m_gWVPLocation, 1, GL_TRUE, &finalMatrix.m[0][0]);
}

void Renderer::HandleMouseAndKeyboardEvents(unsigned char key, int mouse_x, int mouse_y)
{
	m_GameCamera.OnKeyboard(key);
}

void Renderer::HandleMoouseAndKeyboardSpecialEvents(int key, int mouse_x, int mouse_y)
{
	m_GameCamera.OnKeyboard(key);
}
