#include"Renderer/Rendering.h"

namespace Blaze
{
	Rendering::~Rendering()
	{

	}

	void Rendering::Draw(Scene& scene, Shader& shader, FrameBuffer& frameBuffer)
	{
		frameBuffer.Bind();
		Clear();
		scene.m_Registry.each([&](entt::entity entity)
		{
			scene.m_Registry.get<Renderer>(entity).model.Draw(shader);
		});
		frameBuffer.UnBind();
	}

	void Rendering::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
	}

	void Rendering::Draw(VertexArray& vao, IndexBuffer& ibo, FrameBuffer& frameBuffer)
	{
		frameBuffer.Bind();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
		vao.UnBind();
		frameBuffer.UnBind();
	}
}