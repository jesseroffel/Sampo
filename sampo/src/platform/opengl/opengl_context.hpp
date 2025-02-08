#pragma once

#include "sampo/graphics/graphics_context.hpp"
#include "sampo/graphics/window.hpp"
#include "sampo/graphics/camera.hpp"

struct GLFWwindow;

namespace Sampo
{
	class IndexBuffer;
	class Shader;
	class VertexBuffer;
	class VertexArray;

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

		OrthographicCamera m_Camera;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_SquareShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	};
}