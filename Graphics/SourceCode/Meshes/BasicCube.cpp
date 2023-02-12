#include "BasicCube.h"

BasicCube::BasicCube(std::vector<Vertex> cubeVertices, std::vector<unsigned int> cubeIndices)
{
	CreateVertices(cubeVertices);
	CreateIndices(cubeIndices);
}

BasicCube::~BasicCube()
{
}

void BasicCube::InitializeDefaultCubeVertices(std::vector<Vertex>& vertices)
{
	vertices = {
				Vertex(0.5f, 0.5f, 0.5f),
				Vertex(-0.5f, 0.5f, -0.5f),
				Vertex(-0.5f, 0.5f, 0.5f),
				Vertex(0.5f, -0.5f, -0.5f),
				Vertex(-0.5f, -0.5f, -0.5f),
				Vertex(0.5f, 0.5f, -0.5f),
				Vertex(0.5f, -0.5f, 0.5f),
				Vertex(-0.5f, -0.5f, 0.5f)
			   };
}

void BasicCube::InitializeDefaultCubeIndices(std::vector<unsigned int>& indices)
{
	indices = {
				0, 1, 2,
				1, 3, 4,
				5, 6, 3,
				7, 3, 6,
				2, 4, 7,
				0, 7, 6,
				0, 5, 1,
				1, 5, 3,
				5, 0, 6,
				7, 4, 3,
				2, 1, 4,
				0, 2, 7
			  };
}

void BasicCube::CreateVertices(std::vector<Vertex> cubeVertices)
{
	if (cubeVertices.empty()) { InitializeDefaultCubeVertices(cubeVertices); }
	Vertex vertices[8];
	for (unsigned int i = 0; i < 8; i++) { vertices[i] = cubeVertices[i]; }

	m_Vertices	   = vertices;
	m_VerticesSize = sizeof(vertices);
	CreateVertexBuffer();
}

void BasicCube::CreateIndices(std::vector<unsigned int> cubeIndices)
{
	if (cubeIndices.empty()) { InitializeDefaultCubeIndices(cubeIndices); }
	unsigned int indices[36];
	for (int i = 0; i < 36; i++) { indices[i] = cubeIndices[i]; }
	
	m_Indices	  = indices;
	m_IndicesSize = sizeof(indices);
	CreateIndexBuffer();
}
