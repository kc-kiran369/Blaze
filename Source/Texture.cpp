#include"Renderer/Texture.h"

Texture::Texture(const char* path, uint32_t slot)
{
	Load(path, slot);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Load(const char* path, uint32_t slot)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(false);
	unsigned char* data = stbi_load(path, (int*)&m_Width, (int*)&m_Height, (int*)&m_Channel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, (m_Channel == 3 ? GL_RGB : GL_RGBA), m_Width, m_Height, 0, (m_Channel == 3 ? GL_RGB : GL_RGBA), GL_UNSIGNED_BYTE, data);
	if (slot != NULL)
		glActiveTexture(GL_TEXTURE0 + slot);
	else
		Logger::Warn("Slot is Null");
	glGenerateMipmap(GL_TEXTURE_2D);
	if (data)
		stbi_image_free(data);
	else
		Logger::Warn("Image didn't load");

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t Texture::GetRendererID()
{
	return m_RendererID;
}

uint32_t Texture::GetWidth()
{
	return m_Width;
}

uint32_t Texture::GetHeight()
{
	return m_Height;
}

uint32_t Texture::GetChannel()
{
	return m_Channel;
}