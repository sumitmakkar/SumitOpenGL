#include "BasicCube.h"

BasicCube::BasicCube(std::vector<Vector3f> cubeVertices,
					 std::vector<Vector4f> cubeColours,
				     std::vector<Vector2f> cubeTextures,
					 std::vector<Vector3f> cubeNormals,
					 std::vector<Vector4f> cubeTangents,
					 std::vector<GLuint>   cubeIndices)
{
	CreateVertices(cubeVertices);
	CreateTextures(cubeTextures);
	CreateIndices(cubeIndices);
	SetAttributes();
}

BasicCube::~BasicCube()
{
}

void BasicCube::InitializeBasicCubeVerticesData(std::vector<Vector3f>& cubeVertices)
{
	cubeVertices = {
						Vector3f( 0.5f,  0.5f,  0.5f),
						Vector3f(-0.5f,  0.5f, -0.5f),
						Vector3f(-0.5f,  0.5f,  0.5f),
						Vector3f( 0.5f, -0.5f, -0.5f),
						Vector3f(-0.5f, -0.5f, -0.5f),
						Vector3f( 0.5f,  0.5f, -0.5f),
						Vector3f( 0.5f, -0.5f,  0.5f),
						Vector3f(-0.5f, -0.5f,  0.5f)
				   };
}

void BasicCube::InitializeBasicCubeTextureData(std::vector<Vector2f>& cubeTexture)
{
	Vector2f t00 = Vector2f(0.0f, 0.0f);  // Bottom left
	Vector2f t01 = Vector2f(0.0f, 1.0f);  // Top left
	Vector2f t10 = Vector2f(1.0f, 0.0f);  // Bottom right
	Vector2f t11 = Vector2f(1.0f, 1.0f);  // Top right

	cubeTexture = {
					t00,
					t01,
					t10,
					t11,
					t00,
					t10,
					t01,
					t11
				  };
}

void BasicCube::InitializeBasicCubeIndicesData(std::vector<GLuint>& indicesData)
{
	indicesData = {
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

void BasicCube::CreateVertices(std::vector<Vector3f> cubeVertices)
{
	if (cubeVertices.empty()) { InitializeBasicCubeVerticesData(cubeVertices); }
	int cubeVerticesSize = (int)cubeVertices.size();
	m_Vertices			 = new Vector3f[cubeVerticesSize];
	m_NumberOfVertices	 = cubeVerticesSize;
	for (int i = 0; i < cubeVerticesSize; i++) { m_Vertices[i] = cubeVertices[i]; }
}

void BasicCube::CreateColours(std::vector<Vector4f> cubeColours)
{
}

void BasicCube::CreateTextures(std::vector<Vector2f> cubeTextutres)
{
	if (cubeTextutres.empty()) { InitializeBasicCubeTextureData(cubeTextutres); }
	int cubeTextureSize = (int)cubeTextutres.size();
	m_Textures			= new Vector2f[cubeTextureSize];
	for (int i = 0; i < cubeTextureSize; i++) { m_Textures[i] = cubeTextutres[i]; }
}

void BasicCube::CreateNormals(std::vector<Vector3f> cubeNormals)
{
}

void BasicCube::CreateTangents(std::vector<Vector4f> cubeTangents)
{
}

void BasicCube::CreateIndices(std::vector<GLuint> cubeIndices)
{
	if (cubeIndices.empty()) { InitializeBasicCubeIndicesData(cubeIndices); }
	int cubeIndicesSize = (int)cubeIndices.size();
	m_NumberOfIndices	= cubeIndicesSize;
	m_Indices			= new GLuint[cubeIndicesSize];
	for (int i = 0; i < cubeIndicesSize; i++)
	{
		m_Indices[i] = cubeIndices[i];
	}
}
