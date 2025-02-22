#include "sampo_pch.hpp"
#include "buffer.hpp"

#include "renderer.hpp"

#if SAMPO_PLATFORM_WINDOWS
	#include "platform/opengl/opengl_buffer.hpp"
#endif // SAMPO_PLATFORM_WINDOWS

namespace Sampo
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* aVertices, uint32 aSize)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SAMPO_ASSERT_MSG(false, "Headless API not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateShared<OpenGLVertexBuffer>(aVertices, aSize);
		}

		SAMPO_ASSERT_MSG(false, "API Version not supported!");
		return nullptr;
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32* anIndices, uint32 aSize)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: SAMPO_ASSERT_MSG(false, "Headless API not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateShared<OpenGLIndexBuffer>(anIndices, aSize);
		}

		SAMPO_ASSERT_MSG(false, "API Version not supported!");
		return nullptr;
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		m_Stride = 0;
		for (BufferElement& bufferElement : m_BufferElements)
		{
			bufferElement.m_Offset = m_Stride;
			m_Stride += bufferElement.m_Size;
		}
	}

}