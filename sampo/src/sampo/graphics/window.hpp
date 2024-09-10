#pragma once

#ifdef SAMPO_PLATFORM_WINDOWS
namespace Sampo
{
	class Win32Window;
	using Window = Win32Window;
}
#endif // SAMPO_PLATFORM_WINDOWS

namespace Sampo
{
	struct WindowParams
	{
		std::string m_WindowName;
		uint32 m_Width;
		uint32 m_Height;

		WindowParams(const std::string& aWindowName = "Sampo Application", uint32 aWidth = 1280, uint32 aHeight = 720)
			: m_WindowName(aWindowName)
			, m_Width(aWidth)
			, m_Height(aHeight) {}
	};

	class WindowBase
	{
	public:
		virtual void Update() = 0;

		// TODO - Convert to vec2 -> GetSize()
		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;
		virtual const std::string& GetWindowName() const = 0;
	};
}
