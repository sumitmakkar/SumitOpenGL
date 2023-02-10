#include "Renderer.h"
#include <iostream>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::RenderScene()
{
	std::cout << "Render Scene Called!!!!!!!" << std::endl;
}

void Renderer::UpdateScene(float dt)
{
	std::cout << "Update Scene Called!!!!!!!" << std::endl;
}