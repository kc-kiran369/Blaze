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
	uint32_t m_RendererID = 0;
	uint32_t m_Width = 0, m_Height = 0, m_Channel = 0;
public:
	Texture() = default;
	Texture(const char* path, uint32_t slot);
	~Texture();

	void Load(const char* path, uint32_t slot);
	void Bind();
	void UnBind();
	uint32_t GetRendererID();
	uint32_t GetWidth();
	uint32_t GetHeight();
	uint32_t GetChannel();
};
#endif