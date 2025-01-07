#include "platform/windows/core/platform_win32.hpp"

#include <imgui.h>

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

		m_Input->Init();
		m_Window->SetKeyboardEventCallback(BIND_EVENT_FN(Input::OnKeyboardEvent, m_Input));
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

	void Win32Platform::ImGuiDebug()
	{
		ImGui::Begin("Basic device debugger");

		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		m_Input->ImGuiDebug();

		ImGui::End();
	}

}