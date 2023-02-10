#include "SMeshBase.h"

SMeshBase::SMeshBase() : m_VBO(0), m_IBO(0), m_Vertices(NULL), m_VerticesSize(0), m_Indices(NULL), m_IndicesSize(0)
{
	//m_WorldTransform = WorldTransform();
}

SMeshBase::SMeshBase(Vertex* vertices, GLsizeiptr verticesSize, unsigned int* indices, GLsizeiptr indicesSize) : m_VBO(0), m_IBO(0), m_Vertices(vertices), m_VerticesSize(verticesSize), m_Indices(indices), m_IndicesSize(indicesSize)
{
	//m_WorldTransform = WorldTransform();
	CreateVertexBuffer();
	CreateIndexBuffer();
	SetAttributes();
}

SMeshBase::~SMeshBase()
{
}

void SMeshBase::CreateVertexBuffer()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_VerticesSize, m_Vertices, GL_STATIC_DRAW);
}

void SMeshBase::SetAttributes()
{
	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	//Colour
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

void SMeshBase::CreateIndexBuffer()
{
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndicesSize, m_Indices, GL_STATIC_DRAW);
}

void SMeshBase::RenderMesh()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	SetAttributes();	//Setting attributes because it has been deleted in the end. Remove this if the disabled statements are removed in the end.

	glDrawElements(GL_TRIANGLES, (GLsizei)(m_IndicesSize / sizeof(m_Indices[0])), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);	//Position
	glDisableVertexAttribArray(1);	//Colour
}

SWorldTransform& SMeshBase::GetWorldTransform()
{
	return m_WorldTransform;
}
