#include "demo_layer.hpp"

#include <imgui.h>

DemoLayer::DemoLayer()
	: Sampo::Layer("DemoLayer")
{
}

void DemoLayer::OnAttach()
{
	m_TestSFX = Sampo::Sound::Create("../../../../../demo/data/assets/sounds/explosion.ogg");

	Sampo::SoundEffectParams soundEffectParams;
	soundEffectParams.m_AdjustedVolume = 90;
	m_TestMusic = Sampo::Sound::Create("../../../../../demo/data/assets/sounds/freaky_grooves.ogg", soundEffectParams);
}

void DemoLayer::OnUpdate(Sampo::Timestep aDeltaTime)
{
	SAMPO_UNUSED(aDeltaTime);
}

void DemoLayer::OnImGuiRender()
{
	ImGui::Begin("DemoSettings");

	if (ImGui::Button("Play Test SFX"))
		m_TestSFX->Play();

	if (ImGui::Button("Play OneOff SFX"))
		Sampo::Sound::PlayOnce("../../../../../demo/data/assets/sounds/bullet_spawn.ogg");

	if (!m_PlayMusic)
	{
		if (ImGui::Button("Play Test Music"))
		{
			m_PlayMusic = true;
			m_TestMusic->Play();
		}
	}
	else
	{
		if (ImGui::Button("Stop Test Music"))
		{
			m_TestMusic->Stop();
			m_PlayMusic = false;
		}
	}

	ImGui::End();
}