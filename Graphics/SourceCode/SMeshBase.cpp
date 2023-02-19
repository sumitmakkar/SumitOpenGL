#include "SMeshBase.h"

SMeshBase::SMeshBase() : m_VAO(0), m_VBO(0), m_IBO(0), m_Vertices(NULL), m_VerticesSize(0), m_Indices(NULL), m_IndicesSize(0)
{
	
}

SMeshBase::SMeshBase(Vertex* vertices, GLsizeiptr verticesSize, unsigned int* indices, GLsizeiptr indicesSize) : m_VAO(0), m_VBO(0), m_IBO(0), m_Vertices(vertices), m_VerticesSize(verticesSize), m_Indices(indices), m_IndicesSize(indicesSize)
{

}

SMeshBase::~SMeshBase()
{
}

void SMeshBase::CreateVertexBuffer()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_VerticesSize, m_Vertices, GL_STATIC_DRAW);
}

void SMeshBase::SetAttributes()
{
	int attribPointerIndex = 0;
	int stride			   = 0;
	//Position
	if (m_HasPosition)
	{
		glEnableVertexAttribArray(attribPointerIndex++);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		stride += 3;
	}
	//Colour
	if (m_HasColour)
	{
		glEnableVertexAttribArray(attribPointerIndex++);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(stride * sizeof(float)));
		stride += 3;
	}
	//Texture
	if (m_HasPosition)
	{
		glEnableVertexAttribArray(attribPointerIndex++);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(stride * sizeof(float)));
		stride += 2;
	}

	// Changes
	/*for (int i = Vertices; i < Tangents; i++)
	{
		switch (vertexAttributesEnumForIteration)
		{
			case VertexAttributesEnum::Vertices:
				glEnableVertexAttribArray(attribPointerIndex++);
				glVertexAttribPointer(,)
				break;
		}
	}*/
}

void SMeshBase::SendAttributesToGPU()
{

}

void SMeshBase::CreateIndexBuffer()
{
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndicesSize, m_Indices, GL_STATIC_DRAW);
}

void SMeshBase::RenderMesh()
{
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glDrawElements(GL_TRIANGLES, (GLsizei)(m_IndicesSize / sizeof(m_Indices[0])), GL_UNSIGNED_INT, 0);

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