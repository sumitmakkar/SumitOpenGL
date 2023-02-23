#pragma once

#include <string>
#include <Glew\glew.h>

class SOGLTextureBase
{
	private:
		std::string m_FileName;
		GLenum		m_TextureTarget;
		GLuint		m_TextureObject;
		int			m_imageWidth = 0;
		int			m_imageHeight = 0;
		int			m_imageBPP = 0;

	public:
		SOGLTextureBase(GLenum textureTarget, const std::string& fileName = "");
		bool Load();	// Must be called once to load the texture
		void Bind(GLenum textureUnit);	// Must be called at least once for specific texture unit
};