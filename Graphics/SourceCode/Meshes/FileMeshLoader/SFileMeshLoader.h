#pragma once


#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include "../../SMeshBase.h"
#include "SumitOGLMaths.h"
#include "SMaterial.h"

#define INVALID_MATERIAL 0xFFFFFFFF

class SFileMeshLoader : public SMeshBase
{
	typedef struct BasicMeshDataStructure
	{
		uint numberOfIndices;
		uint baseVertex;
		uint baseIndex;
		uint materialIndex;

		BasicMeshDataStructure()
		{
			numberOfIndices = 0;
			baseVertex		= 0;
			baseIndex		= 0;
			materialIndex	= INVALID_MATERIAL;
		}
	}BasicMeshData;

	private:
		const aiScene*			   m_Scene;
		Assimp::Importer		   m_Importer;
		Matrix4f				   m_GlobalInverseTransform;
		std::vector<BasicMeshData> m_MeshesData;
		std::vector<SMaterial>	   m_Materials;

	public:
		bool LoadMesh(const std::string& fileName);

	private:
		bool InitializeFromScene(const std::string& fileName);
		void CountVerticesAndIndices(unsigned int& NumVertices, unsigned int& NumIndices);
		void ReserveSpace(unsigned int numVertices, unsigned int numIndices);
		void InitAllMeshes();
		void InitSingleMesh(uint meshIndex, const aiMesh* aiMesh);
		bool InitMaterials(const string& filename);
		void LoadTextures(const string& directory, const aiMaterial* material, int index);
		void LoadDiffuseTexture(const string& directory, const aiMaterial* material, int materialIndex);
		void LoadDiffuseTextureEmbedded(const aiTexture* aiTexture, int materialIndex);
		void LoadDiffuseTextureFromFile(const string& directory, const aiString& path, int materialIndex);
		void LoadSpecularTexture(const string& directory, const aiMaterial* material, int materialIndex);
		void LoadSpecularTextureEmbedded(const aiTexture* aiTexture, int materialIndex);
		void LoadSpecularTextureFromFile(const string& directory, const aiString& path, int materialIndex);
		void LoadColors(const aiMaterial* material, int index);
		void RenderMesh();
};