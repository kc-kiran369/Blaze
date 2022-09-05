#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include"glew/glew.h"

#ifndef STBI_INCLUDE_STB_IMAGE_H
#include"stb_image/stb_image.h"
#endif

#include <iostream>

#include"Benchmark/Logger.h"

class Texture
{
	unsigned int m_RendererID;
	unsigned int m_Width, m_Height, m_Channel;
public:
	Texture(const char* path, unsigned int slot);
	~Texture();

	void Bind();
	void UnBind();
	unsigned int GetRendererID();
	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetChannel();
};
#endif