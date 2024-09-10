#pragma once
#include "sampo/graphics/window.hpp"

struct GLFWwindow;

namespace Sampo
{
	class Win32Window : public WindowBase
	{
	public:
		explicit Win32Window() = default;
		~Win32Window();

		void Init(const WindowParams& aWindowProperties);
		void Update();
		void Shutdown();

		virtual uint32 GetWidth() const { return m_Params.m_Width; }
		virtual uint32 GetHeight() const { return m_Params.m_Height; }
		virtual const std::string& GetWindowName() const { return m_Params.m_WindowName; }

	private:

		void SetVSync(bool anEnable);

		WindowParams m_Params{};

		bool m_GLFWInitialized{ false };
		GLFWwindow* m_GLFWWindow{ nullptr };
	};
}