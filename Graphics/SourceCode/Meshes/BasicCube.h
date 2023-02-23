#pragma once

#include <vector>
#include "../SMeshBase.h"
#include "Vertex.h"
#include "SOGLUtility.h"

class BasicCube : public SMeshBase
{
	public:
		BasicCube(std::vector<Vector3f> cubeVertices = NULL_3D_VECTOR,
				  std::vector<Vector4f> cubeColours  = NULL_4D_VECTOR,
				  std::vector<Vector2f> cubeTextures = NULL_2D_VECTOR,
				  std::vector<Vector3f> cubeNormals  = NULL_3D_VECTOR,
				  std::vector<Vector4f> cubeTangents = NULL_4D_VECTOR,
				  std::vector<GLuint>   cubeIndices  = std::vector<GLuint>());
		~BasicCube();

	private:
		void InitializeBasicCubeVerticesData(std::vector<Vector3f>& cubeVertices);
		void InitializeBasicCubeTextureData(std::vector<Vector2f>& cubeTexture);
		void InitializeBasicCubeIndicesData(std::vector<GLuint>& indicesData);
		void CreateVertices(std::vector<Vector3f> cubeVertices);
		void CreateColours(std::vector<Vector4f>  cubeColours);
		void CreateTextures(std::vector<Vector2f> cubeTextutres);
		void CreateNormals(std::vector<Vector3f>  cubeNormals);
		void CreateTangents(std::vector<Vector4f> cubeTangents);
		void CreateIndices(std::vector<GLuint>	  cubeIndices);
};