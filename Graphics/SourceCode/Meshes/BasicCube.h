#pragma once

#include <vector>
#include "../SMeshBase.h"
#include "Vertex.h"

class BasicCube : public SMeshBase
{
	public:
		BasicCube(std::vector<Vertex> cubeVertices = std::vector<Vertex>(), std::vector<unsigned int> cubeIndices = std::vector<unsigned int>());
		~BasicCube();

	private:
		void InitializeDefaultCubeVertices(std::vector<Vertex>& vertices);
		void InitializeDefaultCubeIndices(std::vector<unsigned int>& indices);
		void CreateVertices(std::vector<Vertex> cubeVertices);
		void CreateIndices(std::vector<unsigned int> cubeIndices);
};