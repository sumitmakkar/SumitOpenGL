#include "SMeshBase.h"

SMeshBase::SMeshBase() : m_VAO(0), m_VBO(0), m_IBO(0), m_Vertices(NULL), m_NumberOfVertices(0), m_Indices(NULL), m_NumberOfIndices(0)
{
	glGenVertexArrays(1, &m_VAO);
}

SMeshBase::SMeshBase(Vector3f* vertices,
					 GLuint numberOfVertices,
					 unsigned int* indices,
				     GLuint numberOfIndices) : m_VAO(0),
											   m_VBO(0),
											   m_IBO(0),
											   m_Vertices(vertices),
											   m_NumberOfVertices(numberOfVertices),
											   m_Indices(indices),
											   m_NumberOfIndices(numberOfIndices)
{
	glGenVertexArrays(1, &m_VAO);
}

SMeshBase::~SMeshBase()
{
}

void SMeshBase::SetAttributes()
{
	// Change for this commit
	glBindVertexArray(m_VAO);
	if (m_Vertices)
	{
		SendAttributeToGPU(&m_AttibuteBufferObjectsHandleID[VertexAttributesBufferEnum::Vertices], m_NumberOfVertices, sizeof(Vector3f), VertexAttributesBufferEnum::Vertices, 3, m_Vertices, "Vertices");
	}
	if (m_Colours)
	{
		SendAttributeToGPU(&m_AttibuteBufferObjectsHandleID[VertexAttributesBufferEnum::Colours], m_NumberOfVertices, sizeof(Vector4f), VertexAttributesBufferEnum::Colours, 4, m_Colours, "Colours");
	}
	if (m_Textures)
	{
		SendAttributeToGPU(&m_AttibuteBufferObjectsHandleID[VertexAttributesBufferEnum::Textures], m_NumberOfVertices, sizeof(Vector2f), VertexAttributesBufferEnum::Textures, 2, m_Textures, "Textures");
	}
	if (m_Normals)
	{
		SendAttributeToGPU(&m_AttibuteBufferObjectsHandleID[VertexAttributesBufferEnum::Normals], m_NumberOfVertices, sizeof(Vector3f), VertexAttributesBufferEnum::Normals, 3, m_Normals, "Normals");
	}
	if (m_Tangents)
	{
		SendAttributeToGPU(&m_AttibuteBufferObjectsHandleID[VertexAttributesBufferEnum::Tangents], m_NumberOfVertices, sizeof(Vector4f), VertexAttributesBufferEnum::Tangents, 4, m_Tangents, "Tangents");
	}

	if (m_Indices)
	{
		glGenBuffers(1, &m_AttibuteBufferObjectsHandleID[VertexAttributesBufferEnum::Indices]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_AttibuteBufferObjectsHandleID[VertexAttributesBufferEnum::Indices]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_NumberOfIndices * sizeof(GLuint), m_Indices, GL_STATIC_DRAW);
	}
}

void SMeshBase::SendAttributeToGPU(GLuint*			  attributeHandleID,
								   int				  numberOfVertices,
								   int				  singleVertexDataSize,
								   GLuint			  attributeIndex,	//Attribute Location in shader
								   int				  elementsInSingleVertexData,
								   const void*		  attributesData,
								   const std::string& attributeNameString)
{
	glGenBuffers(1, attributeHandleID);
	glBindBuffer(GL_ARRAY_BUFFER, *attributeHandleID);
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * singleVertexDataSize, attributesData, GL_STATIC_DRAW);

	//Attributes
	glEnableVertexAttribArray(attributeIndex);
	glVertexAttribPointer(attributeIndex, elementsInSingleVertexData, GL_FLOAT, GL_FALSE, 0, 0);
}

void SMeshBase::RenderMesh()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)(m_NumberOfIndices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

SWorldTransform& SMeshBase::GetWorldTransform()
{
	return m_WorldTransform;
}

void SMeshBase::Bind()
{
	glBindVertexArray(m_VAO);
}