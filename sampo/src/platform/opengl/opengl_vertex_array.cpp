#include "sampo_pch.hpp"
#include "opengl_vertex_array.hpp"

#include "sampo/graphics/buffer.hpp"

#include <glad/glad.h>

namespace Sampo
{
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType aDataType)
	{
		switch (aDataType)
		{
			case Sampo::ShaderDataType::None:
			case Sampo::ShaderDataType::Bool: return GL_BOOL;
			case Sampo::ShaderDataType::Int: return GL_INT;
			case Sampo::ShaderDataType::Int2: return GL_INT;
			case Sampo::ShaderDataType::Int3: return GL_INT;
			case Sampo::ShaderDataType::Int4: return GL_INT;
			case Sampo::ShaderDataType::Float: return GL_FLOAT;
			case Sampo::ShaderDataType::Float2: return GL_FLOAT;
			case Sampo::ShaderDataType::Float3: return GL_FLOAT;
			case Sampo::ShaderDataType::Float4: return GL_FLOAT;
			case Sampo::ShaderDataType::Matrix3: return GL_FLOAT;
			case Sampo::ShaderDataType::Matrix4: return GL_FLOAT;
		}

		SAMPO_ASSERT_MSG(false, "Cannot convert Shader Data Type to OpenGL Type as the data type is invalid!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& aVertexBuffer)
	{
		SAMPO_ASSERT_MSG(!aVertexBuffer->GetLayout().GetElements().empty(), "Vertex Buffer has no layout elements!");

		glBindVertexArray(m_RendererID);
		aVertexBuffer->Bind();

		uint32 index = 0;
		const BufferLayout& vertexLayout = aVertexBuffer->GetLayout();
		for (const BufferElement& bufferElement : vertexLayout)
		{
			glEnableVertexAttribArray(index);
			const uint32 componentCount = bufferElement.GetComponentCount();
			const GLenum dataType = ShaderDataTypeToOpenGLType(bufferElement.m_Type);
			const GLboolean normalized = bufferElement.m_Normalized ? GL_TRUE : GL_FALSE;
			const uint32 stride = vertexLayout.GetStride();
			glVertexAttribPointer(index, componentCount, dataType, normalized, stride, (const void*)bufferElement.m_Offset);
			index++;
		}

		m_VertexBuffers.emplace_back(aVertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& anIndexBuffer)
	{
		glBindVertexArray(m_RendererID);
		anIndexBuffer->Bind();

		m_IndexBuffer = anIndexBuffer;
	}

}