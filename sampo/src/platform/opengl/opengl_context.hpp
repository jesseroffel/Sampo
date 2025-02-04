#pragma once
#include "sampo/graphics/graphics_context.hpp"
#include "sampo/graphics/window.hpp"

struct GLFWwindow;

namespace Sampo
{
	class Shader;
	class IndexBuffer;
	class VertexBuffer;

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(Window* aWindow, GLFWwindow* aWindowHandle);

		void Init() override;
		void PostInit() override;
		void OnStartFrame() override;
		void SwapBuffers() override;
		void Draw() override;

		void LogRendererInfo() override;
	private:
		Window* m_Window{ nullptr };
		GLFWwindow* m_WindowHandle{ nullptr };

		uint32 m_VertexArray = 0;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};
}