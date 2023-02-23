#include "Renderer.h"
#include "SWorldTransform.h"
#include <iostream>

Renderer::Renderer(int windowWidth, int windowHeight)
{
	m_fov		   = 45.0f;
	m_ZNear		   = 1.0f;
	m_ZFar		   = 100.0f;
	m_WindowWidth  = windowWidth;
	m_WindowHeight = windowHeight;
	m_PersProjInfo = { m_fov, (float)m_WindowWidth, (float)m_WindowHeight, m_ZNear, m_ZFar };
	m_GameCamera   = SCamera(m_WindowWidth, m_WindowHeight, m_CameraPos, m_CameraTarget, m_CameraUp);
	InitializeShaderAndObjects();
}

Renderer::~Renderer()
{
}

void Renderer::InitializeShaderAndObjects()
{
	std::vector<std::string> uniformNamesVector = { "gWorldViewPosition", "gSampler"};
	m_BasicShader								= SShadersBase(m_VSFileName, m_FSFileName, uniformNamesVector);
	m_Pyramid									= new BasicPyramid();
	m_Cube										= new BasicCube();
	m_SpiderMesh								= new SFileMeshLoader();
	m_SpiderMesh->LoadMesh("Assets/Content/spider.obj");
	LoadShaderUniformVariables();
	LoadTexture();
	m_CurrentMesh = m_Cube;
}

void Renderer::LoadShaderUniformVariables()
{
	m_gSamplerLocation = m_BasicShader.GetUniformVariableLocation("gSampler");
	m_gWVPLocation	   = m_BasicShader.GetUniformVariableLocation("gWorldViewPosition");
}

void Renderer::LoadTexture()
{
	m_Texture = new SOGLTextureBase(GL_TEXTURE_2D, "Assets/bricks.jpg");
	if (!m_Texture->Load()) { return; }
}

void Renderer::UpdateCurrentMesh()
{
#ifdef _WIN64
	float YRotationAngle = 0.5f;
#else
	float YRotationAngle = 0.2f;
#endif

	SWorldTransform& currentSelectedMeshWorldTransform = m_CurrentMesh->GetWorldTransform();
	if (m_CurrentMesh == m_SpiderMesh) { currentSelectedMeshWorldTransform.SetScale(0.01f); }
	currentSelectedMeshWorldTransform.SetPosition(0.0f, 0.0f, 2.0f);
	currentSelectedMeshWorldTransform.Rotate(0.0f, YRotationAngle, 0.0f);
	Matrix4f world = currentSelectedMeshWorldTransform.GetMatrix();

	Matrix4f view  = m_GameCamera.GetMatrix();

	Matrix4f projection;
	projection.InitPersProjTransform(m_PersProjInfo);

	Matrix4f finalMatrix = projection * view * world;

	glUniformMatrix4fv(m_gWVPLocation, 1, GL_TRUE, &finalMatrix.m[0][0]);
}

void Renderer::RenderScene()
{
	if (!m_CurrentMesh) { return; }
	m_BasicShader.UseShader();
	m_CurrentMesh->RenderMesh();
}

void Renderer::UpdateScene(float dt)
{
	m_GameCamera.RenderForMouseEdgeCases();		//Called if the mouse is resting in the margins.

	UpdateCurrentMesh();

	//Binding Texture
	m_Texture->Bind(GL_TEXTURE0);
	glUniform1i(m_gSamplerLocation, 0);
}

void Renderer::HandleKeyboardEvents(unsigned char key, int mouse_x, int mouse_y)
{
	m_GameCamera.OnKeyboard(key);
	switch (key)
	{
		case '1':
			m_CurrentMesh = m_Cube;
			break;
		case '2':
			m_CurrentMesh = m_Pyramid;
			break;
		case '3':
			m_CurrentMesh = m_SpiderMesh;
			break;
	}
}

void Renderer::HandleKeyboardSpecialEvents(int key, int mouse_x, int mouse_y)
{
	m_GameCamera.OnKeyboard(key);
}

void Renderer::HandleMouseEvents(int x, int y)
{
	m_GameCamera.OnMouse(x, y);
}
