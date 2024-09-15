#pragma once

struct GLFWwindow;

namespace Sampo
{
	class Event;

	struct WindowParams
	{
		std::string m_WindowName;
		uint32 m_Width;
		uint32 m_Height;

		std::function<void(Event&)> m_EventCallback;

		WindowParams(const std::string& aWindowName = "Sampo Application", uint32 aWidth = 1280, uint32 aHeight = 720)
			: m_WindowName(aWindowName)
			, m_Width(aWidth)
			, m_Height(aHeight) {}
	};

	class Win32Window
	{
	public:
		explicit Win32Window() = default;
		~Win32Window();

		bool Init(const WindowParams& aWindowProperties);
		void Update();
		void Shutdown();

		virtual uint32 GetWidth() const { return m_Params.m_Width; }
		virtual uint32 GetHeight() const { return m_Params.m_Height; }
		virtual const std::string& GetWindowName() const { return m_Params.m_WindowName; }
		void* GetNativeWindow() const { return m_GLFWWindow; }

		void SetEventCallback(const std::function<void(Event&)> aCallback) { m_Params.m_EventCallback = aCallback; }

	private:
		void LogRendererInfo();
		void SetGLFWCallbacks();

		void SetVSync(bool anEnable);

		WindowParams m_Params{};

		bool m_GLFWInitialized{ false };
		GLFWwindow* m_GLFWWindow{ nullptr };
	};
}