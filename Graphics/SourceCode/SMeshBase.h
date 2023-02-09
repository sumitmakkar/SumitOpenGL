#pragma once

#include <Vertex.h>
#include "SWorldTransform.h"

class SMeshBase
{
	protected:
		GLuint			m_VBO;
		GLuint			m_IBO;
		Vertex*			m_Vertices;
		GLsizeiptr		m_VerticesSize;
		unsigned int*	m_Indices;
		GLsizeiptr	    m_IndicesSize;
		SWorldTransform m_WorldTransform;

	public:
		SMeshBase();
		SMeshBase(Vertex* vertices, GLsizeiptr verticesSize, unsigned int* indices, GLsizeiptr indicesSize);	// Not required
		~SMeshBase();
		virtual void RenderMesh();
		SWorldTransform& GetWorldTransform();

	protected:
		void CreateVertexBuffer();
		void CreateIndexBuffer();
		void SetAttributes();
};