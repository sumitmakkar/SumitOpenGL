#pragma once

#include <vector>
#include "../SMeshBase.h"
#include "Vertex.h"

class BasicPyramid : public SMeshBase
{
	private:
		GLuint m_VAO;

	public:
		BasicPyramid(std::vector<Vertex> pyramidVertices = std::vector<Vertex>(), std::vector<unsigned int> pyramidIndices = std::vector<unsigned int>());
		~BasicPyramid();

	private:
		void InitializeDefaultPyramidVertices(std::vector<Vertex>& vertices);
		void InitializeDefaultPyramidIndices(std::vector<unsigned int>& indices);
		void CreateVertices(std::vector<Vertex> pyramidVertices);
		void CreateIndices(std::vector<unsigned int> pyramidIndices);
};