#include "BasicCube.h"

BasicCube::BasicCube(std::vector<Vertex> cubeVertices, std::vector<unsigned int> cubeIndices)
{
	CreateVertices(cubeVertices);
	CreateIndices(cubeIndices);
	SetAttributes();
}

BasicCube::~BasicCube()
{
}

void BasicCube::InitializeDefaultCubeVertices(std::vector<Vertex>& vertices)
{
	Vector2f t00 = Vector2f(0.0f, 0.0f);  // Bottom left
	Vector2f t01 = Vector2f(0.0f, 1.0f);  // Top left
	Vector2f t10 = Vector2f(1.0f, 0.0f);  // Bottom right
	Vector2f t11 = Vector2f(1.0f, 1.0f);  // Top right

	vertices = {
				Vertex(&Vector3f(0.5f, 0.5f, 0.5f),    NULL, &t00),
				Vertex(&Vector3f(-0.5f, 0.5f, -0.5f),  NULL, &t01),
				Vertex(&Vector3f(-0.5f, 0.5f, 0.5f),   NULL, &t10),
				Vertex(&Vector3f(0.5f, -0.5f, -0.5f),  NULL, &t11),
				Vertex(&Vector3f(-0.5f, -0.5f, -0.5f), NULL, &t00),
				Vertex(&Vector3f(0.5f, 0.5f, -0.5f),   NULL, &t10),
				Vertex(&Vector3f(0.5f, -0.5f, 0.5f),   NULL, &t01),
				Vertex(&Vector3f(-0.5f, -0.5f, 0.5f),  NULL, &t11)
	};

	m_HasPosition = true;
	m_HasColour	  = true;
	m_HasTexture  = true;
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
