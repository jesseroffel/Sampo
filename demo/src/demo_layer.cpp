#include "demo_layer.hpp"

#include <imgui.h>

#include "../../sampo/src/platform/windows/audio/audio_device_win32.hpp"

DemoLayer::DemoLayer()
	: Sampo::Layer("DemoLayer")
{
}

void DemoLayer::OnAttach()
{
	//Sampo::Sound::Configure()
	m_TestSFX = Sampo::Sound::Create("../../../../../demo/data/assets/sounds/explosion.wav");
	//m_TestMusic = Sampo::Sound::CreateBGM("../../../../../demo/data/assets/sounds/freaky_grooves.mp3")
	Sampo::SoundEffectParams soundEffectParams;
	soundEffectParams.m_AdjustedVolume = 90;
	m_TestMusic = Sampo::Sound::Create("../../../../../demo/data/assets/sounds/freaky_grooves.ogg", soundEffectParams);
	m_TestMusic2 = Sampo::Sound::Create("../../../../../demo/data/assets/sounds/freaky_grooves.ogg", soundEffectParams);
	// Sampo::Sound::Create(filepath, bool aPlayImmediately)
	// Sampo::Sound::Play(asset)
	// Sampo::Sound::Stop(asset, bool aDestroyInstance)
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
		Sampo::Sound::PlayOnce("../../../../../demo/data/assets/sounds/explosion.wav");
		//Sampo::Sound::PlayOnce("../../../../../demo/data/assets/sounds/bullet_spawn.ogg");

	if (!m_PlayMusic && ImGui::Button("Play Test Music"))
	{
		m_PlayMusic = true;
		m_TestMusic->Play();
	}

	if (ImGui::Button("Play Test Music2"))
	{
		m_TestMusic2->Play();
	}

	ImGui::End();
}