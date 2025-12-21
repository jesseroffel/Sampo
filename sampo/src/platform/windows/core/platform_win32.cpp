#include "sampo_pch.hpp"
#include "platform/windows/core/platform_win32.hpp"

#include "platform/windows/input/input_win32.hpp"
#include "platform/windows/audio/audio_api_win32.hpp"

#include <imgui.h>

namespace Sampo
{
	Win32Platform::Win32Platform()
	{
		m_Input = new Win32Input();
	}

	Win32Platform::~Win32Platform()
	{
		delete m_Input;
		delete m_Window;
	}

	bool Win32Platform::Init(StartParams& aStartParams)
	{
		if (!m_Input->Init())
			return false;

		if (!aStartParams.m_IsHeadless)
		{
			m_Window = new Win32Window();

			if (!m_Window->Init(aStartParams.m_ApplicationName))
				return false;

			m_Window->SetKeyboardEventCallback(BIND_EVENT_FN(Input::OnKeyboardEvent, m_Input));
			m_Window->SetMouseEventCallback(BIND_EVENT_FN(Input::OnMouseEvent, m_Input));
			m_Window->SetGamepadEventCallback(BIND_EVENT_FN(Input::OnGamepadEvent, m_Input));
		}

		if (aStartParams.m_EnableSound)
		{
			m_AudioAPI = AudioAPI::Create();
			m_AudioAPI->Init();
		}

		return true;
	}

	void Win32Platform::Update()
	{
		m_Input->Update();

		if (m_AudioAPI)
			m_AudioAPI->Update();
	}

	void Win32Platform::Shutdown()
	{
		if (m_AudioAPI)
			m_AudioAPI->Shutdown();

		if (m_Window)
			m_Window->Shutdown();
	}

	float Win32Platform::GetTime() const
	{
		return m_Window ? m_Window->GetTime() : 0.0f;
	}

#ifdef SAMPO_IMGUI_ENABLED
	void Win32Platform::ImGuiDebug()
	{
		ImGui::Begin("Basic device debugger");

		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		if (m_AudioAPI)
			m_AudioAPI->ImGuiDebug();

		m_Input->ImGuiDebug();

		ImGui::End();
	}
#endif // SAMPO_IMGUI_ENABLED
}