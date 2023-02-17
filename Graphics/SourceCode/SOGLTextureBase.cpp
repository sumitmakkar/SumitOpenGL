#include "SOGLTextureBase.h"
#include <iostream>
#include "ThirdParty\stb_image.h"
#include "ThirdParty\stb_image_write.h"
#include "SOGLUtility.h"

SOGLTextureBase::SOGLTextureBase(GLenum textureTarget, const std::string& fileName)
{
	m_TextureTarget = textureTarget;
	m_FileName		= fileName;
}

bool SOGLTextureBase::Load()
{
	stbi_set_flip_vertically_on_load(1);

	unsigned char* imageData = stbi_load(m_FileName.c_str(), &m_imageWidth, &m_imageHeight, &m_imageBPP, 0);
	if (!imageData)
	{
		printf("Can't load texture from %s - %s\n", m_FileName.c_str(), stbi_failure_reason());
		exit(0);
	}
	printf("Texture image (%s) Loaded with Width: %d, Height: %d and BPP: %d", m_FileName.c_str(), m_imageWidth, m_imageHeight, m_imageBPP);

	// Generating Texture
	glGenTextures(1, &m_TextureObject);
	//Binding Texture
	glBindTexture(m_TextureTarget, m_TextureObject);
	if (m_TextureTarget == GL_TEXTURE_2D)
	{
		glTexImage2D(m_TextureTarget, 0, GL_RGB, m_imageWidth, m_imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else
	{
		printf("Support  for texture target '%x' is not implemented\n", m_TextureTarget);
		exit(1);
	}

	// Setting Filters
	glTexParameterf(m_TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(m_TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(m_TextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(m_TextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// Unbinding Textture. So that this texture is not edited with other Textures data.
	glBindTexture(m_TextureTarget, 0);

	// Freeing the image data, as it is no longer in use from here on. A copy of the image is already loaded in the open GL and it is unnecessary to keep an additional copy of the image in the CPU.
	stbi_image_free(imageData);

	return true;
}

void SOGLTextureBase::Bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(m_TextureTarget, m_TextureObject);
}