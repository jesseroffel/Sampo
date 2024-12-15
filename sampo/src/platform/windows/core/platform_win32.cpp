#include "platform/windows/core/platform_win32.hpp"

namespace Sampo
{
	Win32Platform::Win32Platform()
	{
		m_Window = new Win32Window();
		m_Input = new Input();
	}

	Win32Platform::~Win32Platform()
	{
		delete m_Input;
		delete m_Window;
	}

	bool Win32Platform::Init(const std::string& aWindowName)
	{
		if (!m_Window->Init(aWindowName))
			return false;

		m_Window->SetMouseEventCallback(BIND_EVENT_FN(Input::OnMouseEvent, m_Input));
		return true;
	}

	void Win32Platform::Update()
	{
		m_Window->Update();
	}

	void Win32Platform::Shutdown()
	{
		m_Window->Shutdown();

		delete m_Window;
		m_Window = nullptr;
	}

	Window* Win32Platform::GetWindow() const
	{
		return m_Window;
	}
}