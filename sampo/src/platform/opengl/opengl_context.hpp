#pragma once
#include "sampo/graphics/graphics_context.hpp"

#include "sampo/graphics/window.hpp"

struct GLFWwindow;

namespace Sampo
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(Window* aWindow, GLFWwindow* aWindowHandle);

		void Init() override;
		void OnStartFrame() override;
		void SwapBuffers() override;
		void Draw() override {};

		void LogRendererInfo() override;
	private:
		Window* m_Window{ nullptr };
		GLFWwindow* m_WindowHandle{ nullptr };
	};
}