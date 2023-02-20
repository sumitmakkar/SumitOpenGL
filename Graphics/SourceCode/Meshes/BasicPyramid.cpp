#include "BasicPyramid.h"

BasicPyramid::BasicPyramid(std::vector<Vector3f> pyramidVertices, std::vector<Vector4f> pyramidColours, std::vector<Vector2f> pyramidTextures, std::vector<Vector3f> pyramidNormals, std::vector<Vector4f> pyramidTangents, std::vector<GLuint> pyramidIndices)
{
	CreateVertices(pyramidVertices);
	CreateTextures(pyramidTextures);
	CreateIndices(pyramidIndices);
	SetAttributes();
}

BasicPyramid::~BasicPyramid()
{
	
}

void BasicPyramid::InitializeBasicPyramidVerticesData(std::vector<Vector3f>& pyramidVertices)
{
	pyramidVertices = {
						Vector3f(-1.0f, -1.0f,  0.5773f),
						Vector3f(0.0f, -1.0f, -1.15475f),
						Vector3f(1.0f, -1.0f,  0.5773f),
						Vector3f(0.0f,  1.0f,  0.0f)
					  };
}

void BasicPyramid::InitializeBasicPyramidTextureData(std::vector<Vector2f>& pyramidTexture)
{
	Vector2f t00   = Vector2f(0.0f, 0.0f);
	Vector2f t050  = Vector2f(0.5f, 0.0f);
	Vector2f t10   = Vector2f(1.0f, 0.0f);
	Vector2f t051  = Vector2f(0.5f, 1.0f);

	pyramidTexture = {
						t00,
						t050,
						t10,
						t051
					 };
}

void BasicPyramid::InitializeBasicPyramidIndicesData(std::vector<GLuint>& pyramidIndicesData)
{
	pyramidIndicesData = {
							0, 3, 1,
							1, 3, 2,
							2, 3, 0,
							0, 1, 2
						 };
}

void BasicPyramid::CreateVertices(std::vector<Vector3f> pyramidVertices)
{
	if (pyramidVertices.empty()) { InitializeBasicPyramidVerticesData(pyramidVertices); }
	int pyramidVerticesSize = (int)pyramidVertices.size();
	m_Vertices				= new Vector3f[pyramidVerticesSize];
	m_NumberOfVertices		= pyramidVerticesSize;
	for (int i = 0; i < pyramidVerticesSize; i++) { m_Vertices[i] = pyramidVertices[i]; }
}

void BasicPyramid::CreateColours(std::vector<Vector4f> pyramidColours)
{
}

void BasicPyramid::CreateTextures(std::vector<Vector2f> pyramidTextutres)
{
	if (pyramidTextutres.empty()) { InitializeBasicPyramidTextureData(pyramidTextutres); }
	int pyramidTextureSize = (int)pyramidTextutres.size();
	m_Textures			   = new Vector2f[pyramidTextureSize];
	for (int i = 0; i < pyramidTextureSize; i++) { m_Textures[i] = pyramidTextutres[i]; }
}

void BasicPyramid::CreateNormals(std::vector<Vector3f> pyramidNormals)
{
}

void BasicPyramid::CreateTangents(std::vector<Vector4f> pyramidTangents)
{
}

void BasicPyramid::CreateIndices(std::vector<GLuint> pyramidIndices)
{
	if (pyramidIndices.empty()) { InitializeBasicPyramidIndicesData(pyramidIndices); }
	int pyramidIndicesSize = (int)pyramidIndices.size();
	m_NumberOfIndices	   = pyramidIndicesSize;
	m_Indices			   = new GLuint[pyramidIndicesSize];
	for (int i = 0; i < pyramidIndicesSize; i++)
	{
		m_Indices[i] = pyramidIndices[i];
	}
}