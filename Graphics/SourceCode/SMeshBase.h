#pragma once

#include <Vertex.h>
#include "SWorldTransform.h"

class SMeshBase
{
	protected:
		GLuint			m_VBO;
		GLuint			m_IBO;
		Vertex*			m_Vertices; //TODO: - To be changed later. Rather than having an object of vertex, have all attributes there in this mesh base class. So that ever attribute can be checked and uploaded to the GPU, without occupying additional space.
		GLsizeiptr		m_VerticesSize;
		unsigned int*	m_Indices;
		GLsizeiptr	    m_IndicesSize;
		SWorldTransform m_WorldTransform;

		bool			m_HasPosition = false;
		bool			m_HasColour	  = false;
		bool			m_HasTexture  = false;

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