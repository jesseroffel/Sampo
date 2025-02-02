#pragma once
#include "sampo/graphics/graphics_context.hpp"
#include "sampo/graphics/window.hpp"

struct GLFWwindow;

namespace Sampo
{
	class Shader;

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
		uint32 m_VertexBuffer = 0;
		uint32 m_IndexBuffer = 0;

		std::unique_ptr<Shader> m_Shader;
	};
}