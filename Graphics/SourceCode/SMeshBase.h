#pragma once

#include <Vertex.h>
#include "SWorldTransform.h"

class SMeshBase
{
	enum VertexAttributesEnum		//Ordering in Shaders
	{
		Vertices,
		Colours,
		Textures,
		Normals,
		Tangents
	};

	protected:
		GLuint			m_VAO;
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

		//Vertice Attributes Data
		/*Vector3f* m_Vertices = NULL;
		Vector4f* m_Colours  = NULL;
		Vector2f* m_Textures = NULL;
		Vector3f* m_Normals  = NULL;
		Vector4f* m_Tangents = NULL;*/

		VertexAttributesEnum vertexAttributesEnumForIteration;

	public:
		SMeshBase();
		SMeshBase(Vertex* vertices, GLsizeiptr verticesSize, unsigned int* indices, GLsizeiptr indicesSize);	// Not required
		~SMeshBase();
		virtual void RenderMesh();
		SWorldTransform& GetWorldTransform();
		void Bind();

	protected:
		void CreateVertexBuffer();
		void CreateIndexBuffer();
		void SetAttributes();

	private:
		void SendAttributesToGPU();
};