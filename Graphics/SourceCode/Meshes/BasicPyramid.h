#pragma once

#include <vector>
#include "../SMeshBase.h"
#include "Vertex.h"
#include "SOGLUtility.h"

//TODO: - TO be placed somewhere else
#define NULL_2D_VECTOR std::vector<Vector2f>()
#define NULL_3D_VECTOR std::vector<Vector3f>()
#define NULL_4D_VECTOR std::vector<Vector4f>()

class BasicPyramid : public SMeshBase
{
	private:
		GLuint m_VAO;

	public:
		BasicPyramid(std::vector<Vector3f> pyramidVertices = NULL_3D_VECTOR,
					 std::vector<Vector4f> pyramidColours  = NULL_4D_VECTOR,
					 std::vector<Vector2f> pyramidTextures = NULL_2D_VECTOR,
					 std::vector<Vector3f> pyramidNormals  = NULL_3D_VECTOR,
					 std::vector<Vector4f> pyramidTangents = NULL_4D_VECTOR,
					 std::vector<GLuint>   pyramidIndices  = std::vector<GLuint>());
		~BasicPyramid();

	private:
		void InitializeBasicPyramidVerticesData(std::vector<Vector3f>& pyramidVertices);
		void InitializeBasicPyramidTextureData(std::vector<Vector2f>&  pyramidTexture);
		void InitializeBasicPyramidIndicesData(std::vector<GLuint>&	   pyramidIndicesData);
		void CreateVertices(std::vector<Vector3f> pyramidVertices);
		void CreateColours(std::vector<Vector4f>  pyramidColours);
		void CreateTextures(std::vector<Vector2f> pyramidTextutres);
		void CreateNormals(std::vector<Vector3f>  pyramidNormals);
		void CreateTangents(std::vector<Vector4f> pyramidTangents);
		void CreateIndices(std::vector<GLuint>	  pyramidIndices);
};