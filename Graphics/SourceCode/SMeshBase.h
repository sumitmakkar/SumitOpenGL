#pragma once

#include <Vertex.h>
#include "SWorldTransform.h"

class SMeshBase
{
	enum VertexAttributesBufferEnum		//Ordering in Shaders
	{
		Vertices,
		Colours,
		Textures,
		Normals,
		Tangents,
		Indices,
		TotalAttibutes
	};

	protected:
		GLuint			m_VAO;
		GLuint			m_VBO;
		GLuint			m_IBO;
		SWorldTransform m_WorldTransform;

		//Vertice Attributes Data
		/*Vector3f*		m_Vertices	  = NULL;
		Vector4f*		m_Colours	  = NULL;
		Vector2f*		m_Textures	  = NULL;
		Vector3f*		m_Normals	  = NULL;
		Vector4f*		m_Tangents	  = NULL;
		GLuint*			m_Indices	  = NULL;*/
		std::vector<Vector3f> m_Vertices;
		std::vector<Vector4f> m_Colours;
		std::vector<Vector2f> m_Textures;
		std::vector<Vector3f> m_Normals;
		std::vector<Vector4f> m_Tangents;
		std::vector<GLuint>   m_Indices;

		GLuint			m_AttibuteBufferObjectsHandleID[TotalAttibutes];
		GLuint			m_NumberOfVertices;
		GLuint			m_NumberOfIndices;

	public:
		SMeshBase();
		SMeshBase(std::vector<Vector3f> vertices,
				  GLuint numberOfVertices,
				  std::vector<GLuint> indices,
				  GLuint numberOfIndices);	// Not required
		~SMeshBase();
		virtual void RenderMesh();
		SWorldTransform& GetWorldTransform();
		void Bind();

	protected:
		void SetAttributes();

	private:
		void SendAttributeToGPU(GLuint*			   attributeHandleID,
								int				   numberOfVertices,
								int				   singleVertexDataSize,
								GLuint			   attributeIndex,
								int				   elementsInSingleVertexData,
								const void*		   attributesData,
								const std::string& attributeNameString);
};