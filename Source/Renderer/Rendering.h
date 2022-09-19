#ifndef RENDERER_H
#define RENDERER_H

#include"../ECS/Scene.h"

#include"VertexArray.h"
#include"IndexBuffer.h"
#include"FrameBuffer.h"

namespace Blaze
{
	class Rendering
	{
	public:
		Rendering() = default;
		~Rendering();

		void Draw(Scene& scene, Shader& shader, FrameBuffer& frameBuffer);
		void Draw(VertexArray& vao, IndexBuffer& ibo, FrameBuffer& frameBuffer);
		void Clear();
	};

#endif // !RENDERER_H
}