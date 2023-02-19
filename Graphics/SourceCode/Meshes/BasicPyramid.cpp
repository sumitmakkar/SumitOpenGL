#include "BasicPyramid.h"

BasicPyramid::BasicPyramid(std::vector<Vertex> pyramidVertices, std::vector<unsigned int> pyramidIndices)
{
	CreateVertices(pyramidVertices);
	CreateIndices(pyramidIndices);
	SetAttributes();
}

BasicPyramid::~BasicPyramid()
{
}

void BasicPyramid::InitializeDefaultPyramidVertices(std::vector<Vertex>& vertices)
{
	Vector2f t00  = Vector2f(0.0f, 0.0f);
	Vector2f t050 = Vector2f(0.5f, 0.0f);
	Vector2f t10  = Vector2f(1.0f, 0.0f);
	Vector2f t051 = Vector2f(0.5f, 1.0f);
	vertices	  = { Vertex(&Vector3f(-1.0f, -1.0f,  0.5773f),  NULL, &t00),
				      Vertex(&Vector3f(0.0f,  -1.0f, -1.15475f), NULL, &t050),
				      Vertex(&Vector3f(1.0f,  -1.0f,  0.5773f),  NULL, &t10),
				      Vertex(&Vector3f(0.0f,   1.0f,  0.0f),	 NULL, &t051) };

	m_HasPosition = true;
	m_HasColour   = true;
	m_HasTexture  = true;
}

void BasicPyramid::InitializeDefaultPyramidIndices(std::vector<unsigned int>& indices)
{
	indices = { 0, 3, 1,
			    1, 3, 2,
			    2, 3, 0,
			    0, 1, 2 };
}

void BasicPyramid::CreateVertices(std::vector<Vertex> pyramidVertices)
{
	if (pyramidVertices.empty()) { InitializeDefaultPyramidVertices(pyramidVertices); }
	Vertex vertices[4];
	for (unsigned int i = 0; i < 4; i++) { vertices[i] = pyramidVertices[i]; }

	m_Vertices	   = vertices;
	m_VerticesSize = sizeof(vertices);
	CreateVertexBuffer();
}

void BasicPyramid::CreateIndices(std::vector<unsigned int> pyramidIndices)
{
	if (pyramidIndices.empty()) { InitializeDefaultPyramidIndices(pyramidIndices); }
	unsigned int indices[12];
	for (int i = 0; i < 12; i++) { indices[i] = pyramidIndices[i]; }

	m_Indices	  = indices;
	m_IndicesSize = sizeof(indices);
	CreateIndexBuffer();
}