#pragma once

#include <SRendererBase.h>

class Renderer : public SRendererBase
{
	public:
		Renderer();
		~Renderer();
		void RenderScene() override;
		void UpdateScene(float dt) override;
};