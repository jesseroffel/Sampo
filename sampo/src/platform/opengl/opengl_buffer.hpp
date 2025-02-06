#pragma once

#include "sampo/graphics/buffer.hpp"

namespace Sampo
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* aVertices, uint32 aSize);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		const BufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const BufferLayout& aLayout) override { m_Layout = aLayout; }
	private:
		BufferLayout m_Layout;
		uint32 m_RendererID{ uint32_max };
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32* anIndices, uint32 aCount);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32 GetCount() const override { return m_Count; }
	private:
		uint32 m_RendererID{ uint32_max };
		uint32 m_Count{ uint32_max };
	};
}