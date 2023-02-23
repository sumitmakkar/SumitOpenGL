#include <iostream>
#include "SFileMeshLoader.h"
#include "../../STextureUnitsCommon.h"

bool SFileMeshLoader::LoadMesh(const std::string& fileName)
{
	bool hasFileLoadedSuccessfully = false;
	m_Scene = m_Importer.ReadFile(fileName.c_str(), ASSIMP_LOAD_FLAGS);
	if (m_Scene)
	{
		m_GlobalInverseTransform  = m_Scene->mRootNode->mTransformation;
		m_GlobalInverseTransform  = m_GlobalInverseTransform.Inverse();
		hasFileLoadedSuccessfully = InitializeFromScene(fileName);
	}
	else
	{
		std::cout << "Scene Not Loaded!!!" << std::endl;
	}
	return hasFileLoadedSuccessfully;
}

bool SFileMeshLoader::InitializeFromScene(const std::string& fileName)
{
	m_MeshesData.resize(m_Scene->mNumMeshes);
	m_Materials.resize(m_Scene->mNumMaterials);

	unsigned int NumVertices = 0;
	unsigned int NumIndices = 0;

	CountVerticesAndIndices(NumVertices, NumIndices);

	ReserveSpace(NumVertices, NumIndices);

	InitAllMeshes();

	if (!InitMaterials(fileName)) {
		return false;
	}

	//PopulateBuffers();
	SetAttributes();
	return true;
}

void SFileMeshLoader::CountVerticesAndIndices(unsigned int& numVertices, unsigned int& numIndices)
{
	for (unsigned int i = 0; i < m_MeshesData.size(); i++) {
		m_MeshesData[i].materialIndex	= m_Scene->mMeshes[i]->mMaterialIndex;
		m_MeshesData[i].numberOfIndices = m_Scene->mMeshes[i]->mNumFaces * 3;
		m_MeshesData[i].baseVertex		= numVertices;
		m_MeshesData[i].baseIndex		= numIndices;

		numVertices += m_Scene->mMeshes[i]->mNumVertices;
		numIndices  += m_MeshesData[i].numberOfIndices;
	}
	m_NumberOfVertices = numVertices;
	m_NumberOfIndices  = numIndices;
}

void SFileMeshLoader::ReserveSpace(unsigned int numVertices, unsigned int numIndices)
{
	m_Vertices.reserve(numVertices);
	m_Normals.reserve(numVertices);
	m_Textures.reserve(numVertices);
	m_Indices.reserve(numIndices);
}

void SFileMeshLoader::InitAllMeshes()
{
	unsigned int currentStartIndex   = 0;
	unsigned int currentIndicesIndex = 0;
	for (unsigned int i = 0; i < m_MeshesData.size(); i++)
	{
		const aiMesh* aiMesh = m_Scene->mMeshes[i];
		InitSingleMesh(currentStartIndex, aiMesh);
		currentStartIndex   += aiMesh->mNumVertices;
		currentIndicesIndex += aiMesh->mNumFaces;
	}
}

void SFileMeshLoader::InitSingleMesh(uint meshIndex, const aiMesh* aiMesh)
{
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	// Populate the vertex attribute vectors
	for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
	{
		const aiVector3D& pPos = aiMesh->mVertices[i];
		m_Vertices.push_back(Vector3f(pPos.x, pPos.y, pPos.z));

		if (aiMesh->mNormals)
		{
			const aiVector3D& pNormal = aiMesh->mNormals[i];
			m_Normals.push_back(Vector3f(pNormal.x, pNormal.y, pNormal.z));
		}
		else
		{
			aiVector3D Normal(0.0f, 1.0f, 0.0f);
			m_Normals.push_back(Vector3f(Normal.x, Normal.y, Normal.z));
		}

		const aiVector3D& pTexCoord = aiMesh->HasTextureCoords(0) ? aiMesh->mTextureCoords[0][i] : Zero3D;
		m_Textures.push_back(Vector2f(pTexCoord.x, pTexCoord.y));
	}

	// Populate the index buffer
	for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
	{
		const aiFace& Face = aiMesh->mFaces[i];
		m_Indices.push_back(Face.mIndices[0]);
		m_Indices.push_back(Face.mIndices[1]);
		m_Indices.push_back(Face.mIndices[2]);
	}
}

bool SFileMeshLoader::InitMaterials(const string& filename)
{
	string directory = GetDirFromFilename(filename);

	bool Ret = true;

	printf("Num materials: %d\n", m_Scene->mNumMaterials);

	// Initialize the materials
	for (unsigned int i = 0; i < m_Scene->mNumMaterials; i++)
	{
		const aiMaterial* material = m_Scene->mMaterials[i];

		LoadTextures(directory, material, i);

		LoadColors(material, i);
	}

	return Ret;
}

void SFileMeshLoader::LoadTextures(const string& directory, const aiMaterial* material, int index)
{
	LoadDiffuseTexture(directory, material, index);
	LoadSpecularTexture(directory, material, index);
}

void SFileMeshLoader::LoadDiffuseTexture(const string& directory, const aiMaterial* material, int materialIndex)
{
	m_Materials[materialIndex].pDiffuse = NULL;

	if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
		aiString path;

		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
			const aiTexture* aiTexture = m_Scene->GetEmbeddedTexture(path.C_Str());

			if (aiTexture)	// If Diffuse texture is embedded. To be handled later
			{
				//LoadDiffuseTextureEmbedded(aiTexture, material);
			}
			else {
				LoadDiffuseTextureFromFile(directory, path, materialIndex);
			}
		}
	}
}

# pragma region To be looked into later
//void SFileMeshLoader::LoadDiffuseTextureEmbedded(const aiTexture* aiTexture, int materialIndex)
//{
//	printf("Embeddeded diffuse texture type '%s'\n", aiTexture->achFormatHint);
//	m_Materials[materialIndex].pDiffuse = new SOGLTextureBase(GL_TEXTURE_2D);
//	int buffer_size = aiTexture->mWidth;
//	m_Materials[materialIndex].pDiffuse->Load(buffer_size, aiTexture->pcData);
//}
#pragma endregion


void SFileMeshLoader::LoadDiffuseTextureFromFile(const string& directory, const aiString& path, int materialIndex)
{
	string p(path.data);

	for (int i = 0; i < p.length(); i++) {
		if (p[i] == '\\') {
			p[i] = '/';
		}
	}

	if (p.substr(0, 2) == ".\\") {
		p = p.substr(2, p.size() - 2);
	}

	string FullPath = directory + "/" + p;

	m_Materials[materialIndex].pDiffuse = new SOGLTextureBase(GL_TEXTURE_2D, FullPath.c_str());

	if (!m_Materials[materialIndex].pDiffuse->Load())
	{
		printf("Error loading diffuse texture '%s'\n", FullPath.c_str());
		exit(0);
	}
	else { printf("Loaded diffuse texture '%s' at index %d\n", FullPath.c_str(), materialIndex); }
}

void SFileMeshLoader::LoadSpecularTexture(const string& directory, const aiMaterial* material, int materialIndex)
{
	m_Materials[materialIndex].pSpecularExponent = NULL;

	if (material->GetTextureCount(aiTextureType_SHININESS) > 0) {
		aiString path;

		if (material->GetTexture(aiTextureType_SHININESS, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
			const aiTexture* aiTexture = m_Scene->GetEmbeddedTexture(path.C_Str());

			if (aiTexture)	// If Specular texture is embedded. To be handled later
			{
				//LoadSpecularTextureEmbedded(aiTexture, materialIndex);
			}
			else {
				LoadSpecularTextureFromFile(directory, path, materialIndex);
			}
		}
	}
}

# pragma region To be looked into later
//void SFileMeshLoader::LoadSpecularTextureEmbedded(const aiTexture* aiTexture, int materialIndex)
//{
//	printf("Embeddeded specular texture type '%s'\n", aiTexture->achFormatHint);
//	m_Materials[materialIndex].pSpecularExponent = new SOGLTextureBase(GL_TEXTURE_2D);
//	int buffer_size = aiTexture->mWidth;
//	m_Materials[materialIndex].pSpecularExponent->Load(buffer_size, aiTexture->pcData);
//}
#pragma endregion


void SFileMeshLoader::LoadSpecularTextureFromFile(const string& directory, const aiString& path, int materialIndex)
{
	string p(path.data);

	if (p == "C:\\\\") {
		p = "";
	}
	else if (p.substr(0, 2) == ".\\") {
		p = p.substr(2, p.size() - 2);
	}

	string FullPath = directory + "/" + p;

	m_Materials[materialIndex].pSpecularExponent = new SOGLTextureBase(GL_TEXTURE_2D, FullPath.c_str());

	if (!m_Materials[materialIndex].pSpecularExponent->Load())
	{
		printf("Error loading specular texture '%s'\n", FullPath.c_str());
		exit(0);
	}
	else { printf("Loaded specular texture '%s'\n", FullPath.c_str()); }
}

void SFileMeshLoader::LoadColors(const aiMaterial* material, int index)
{
	aiColor3D ambientColor(0.0f, 0.0f, 0.0f);
	Vector3f allOnes(1.0f, 1.0f, 1.0f);

	int shadingModel = 0;
	if (material->Get(AI_MATKEY_SHADING_MODEL, shadingModel) == AI_SUCCESS) {
		printf("Shading model %d\n", shadingModel);
	}

	if (material->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor) == AI_SUCCESS) {
		printf("Loaded ambient color [%f %f %f]\n", ambientColor.r, ambientColor.g, ambientColor.b);
		m_Materials[index].AmbientColor.r = ambientColor.r;
		m_Materials[index].AmbientColor.g = ambientColor.g;
		m_Materials[index].AmbientColor.b = ambientColor.b;
	}
	else {
		m_Materials[index].AmbientColor = allOnes;
	}

	aiColor3D diffuseColor(0.0f, 0.0f, 0.0f);

	if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS) {
		printf("Loaded diffuse color [%f %f %f]\n", diffuseColor.r, diffuseColor.g, diffuseColor.b);
		m_Materials[index].DiffuseColor.r = diffuseColor.r;
		m_Materials[index].DiffuseColor.g = diffuseColor.g;
		m_Materials[index].DiffuseColor.b = diffuseColor.b;
	}

	aiColor3D specularColor(0.0f, 0.0f, 0.0f);

	if (material->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == AI_SUCCESS) {
		printf("Loaded specular color [%f %f %f]\n", specularColor.r, specularColor.g, specularColor.b);
		m_Materials[index].SpecularColor.r = specularColor.r;
		m_Materials[index].SpecularColor.g = specularColor.g;
		m_Materials[index].SpecularColor.b = specularColor.b;
	}
}

void SFileMeshLoader::RenderMesh()
{
	glBindVertexArray(m_VAO);

	for (unsigned int i = 0; i < m_MeshesData.size(); i++)
	{
		unsigned int MaterialIndex = m_MeshesData[i].materialIndex;
		assert(MaterialIndex < m_Materials.size());

		if (m_Materials[MaterialIndex].pDiffuse)
		{
			m_Materials[MaterialIndex].pDiffuse->Bind(COLOR_TEXTURE_UNIT);
		}

		glDrawElementsBaseVertex(GL_TRIANGLES,
								 m_MeshesData[i].numberOfIndices,
								 GL_UNSIGNED_INT,
								 (void*)(sizeof(unsigned int) * m_MeshesData[i].baseIndex), 
								 m_MeshesData[i].baseVertex);
	}

	// Make sure the VAO is not changed from the outside
	glBindVertexArray(0);


	//void* pRenderCallbacks = NULL;
	//glBindVertexArray(m_VAO);

	//for (unsigned int i = 0; i < m_MeshesData.size(); i++) {
	//	unsigned int MaterialIndex = m_MeshesData[i].materialIndex;
	//	assert(MaterialIndex < m_Materials.size());

	//	if (m_Materials[MaterialIndex].pDiffuse) {
	//		m_Materials[MaterialIndex].pDiffuse->Bind(COLOR_TEXTURE_UNIT);
	//	}

	//	if (m_Materials[MaterialIndex].pSpecularExponent) {
	//		m_Materials[MaterialIndex].pSpecularExponent->Bind(SPECULAR_EXPONENT_UNIT);

	//		if (pRenderCallbacks) {
	//			//pRenderCallbacks->ControlSpecularExponent(true);
	//		}
	//	}
	//	else {
	//		if (pRenderCallbacks) {
	//			//pRenderCallbacks->ControlSpecularExponent(false);
	//		}
	//	}

	//	if (pRenderCallbacks) {
	//		if (m_Materials[MaterialIndex].pDiffuse) {
	//			/*pRenderCallbacks->DrawStartCB(i);
	//			pRenderCallbacks->SetMaterial(m_Materials[MaterialIndex]);*/
	//		}
	//		else {
	//			//pRenderCallbacks->DisableDiffuseTexture();
	//		}
	//	}

	//	glDrawElementsBaseVertex(GL_TRIANGLES,
	//		m_MeshesData[i].numberOfIndices,
	//		GL_UNSIGNED_INT,
	//		(void*)(sizeof(unsigned int) * m_MeshesData[i].baseIndex),
	//		m_MeshesData[i].baseVertex);
	//}

	//// Make sure the VAO is not changed from the outside
	//glBindVertexArray(0);
}