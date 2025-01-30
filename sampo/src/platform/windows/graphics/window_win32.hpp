#pragma once
#include <glm/glm.hpp>

struct GLFWwindow;

namespace Sampo
{
	class Event;

	struct WindowParams
	{
		std::string m_WindowName;
		glm::vec2 m_WindowSize;

		std::function<void(Event&)> m_WindowEventCallback;
		std::function<void(Event&)> m_KeyboardEventCallback;
		std::function<void(Event&)> m_MouseEventCallback;
		std::function<void(Event&)> m_JoystickEventCallback;

		WindowParams(const std::string& aWindowName = "Sampo Application", const glm::vec2& aWindowSize = { 1280, 720 })
			: m_WindowName(aWindowName)
			, m_WindowSize(aWindowSize)
		{ }
	};

	class Win32Window
	{
	public:
		explicit Win32Window() = default;
		~Win32Window();

		bool Init(const WindowParams& aWindowProperties);
		void OnStartFrame();
		void OnEndFrame();
		void Shutdown();

		const glm::vec2& GetWindowSize() const { return m_Params.m_WindowSize; }
		virtual float GetTime() const;
		virtual const std::string& GetWindowName() const { return m_Params.m_WindowName; }
		void* GetNativeWindow() const { return m_GLFWWindow; }

		void SetWindowEventCallback(const std::function<void(Event&)> aCallback) { m_Params.m_WindowEventCallback = aCallback; }
		void SetKeyboardEventCallback(const std::function<void(Event&)> aCallback) { m_Params.m_KeyboardEventCallback = aCallback; }
		void SetMouseEventCallback(const std::function<void(Event&)> aCallback) { m_Params.m_MouseEventCallback = aCallback; }
		void SetGamepadEventCallback(const std::function<void(Event&)> aCallback) { m_Params.m_JoystickEventCallback = aCallback; }
	private:
		void LogRendererInfo();
		void SetGLFWCallbacks();

		void SetVSync(bool anEnable);

		WindowParams m_Params{};

		bool m_GLFWInitialized{ false };
		GLFWwindow* m_GLFWWindow{ nullptr };
	};
}