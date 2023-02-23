#pragma once

#include <SRendererBase.h>
#include <SShadersBase.h>
#include <Meshes\BasicCube.h>
#include <Meshes\BasicPyramid.h>
#include <SCamera.h>
#include <SOGLTextureBase.h>
#include "Meshes\FileMeshLoader\SFileMeshLoader.h"

class Renderer : public SRendererBase
{
	private:
		SShadersBase	 m_BasicShader;
		const char*		 m_VSFileName = "Shaders/Shader.vs";
		const char*		 m_FSFileName = "Shaders/Shader.fs";
		BasicCube*		 m_Cube;
		BasicPyramid*	 m_Pyramid;
		SFileMeshLoader* m_SpiderMesh;
		SCamera			 m_GameCamera;
		PersProjInfo	 m_PersProjInfo;
		GLuint			 m_gWVPLocation;

		float 			 m_fov;
		float 			 m_ZNear;
		float 			 m_ZFar;
		int				 m_WindowWidth;
		int				 m_WindowHeight;
		SOGLTextureBase* m_Texture = NULL;
		GLuint			 m_gSamplerLocation;

		Vector3f		 m_CameraPos	= Vector3f(0.0f, 0.0f, -1.0f);
		Vector3f		 m_CameraTarget = Vector3f(1.0f, 0.0f, 1.0f);
		Vector3f		 m_CameraUp		= Vector3f(0.0f, 1.0f, 0.0f);

		SMeshBase*		 m_CurrentMesh  = NULL;

	public:
		Renderer(int windowWidth = 1600, int windowHeight = 800);
		~Renderer();
		void RenderScene() override;
		void UpdateScene(float dt) override;
		void HandleKeyboardEvents(unsigned char key, int mouse_x, int mouse_y) override;
		void HandleKeyboardSpecialEvents(int key, int mouse_x, int mouse_y) override;
		void HandleMouseEvents(int x, int y) override;

	private:
		void InitializeShaderAndObjects();
		void LoadShaderUniformVariables();
		void LoadTexture();

		//Objects Update Methods
		void UpdateCurrentMesh();
};