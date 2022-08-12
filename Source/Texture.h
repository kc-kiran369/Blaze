#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include"glew/glew.h"
#include"stb_image/stb_image.h"

class Texture
{
	unsigned int m_RendererID;
public:
	Texture(const char* path, unsigned int slot);
	~Texture();

	void Bind();
	void UnBind();
	unsigned int GetRendererID();
};

#endif
