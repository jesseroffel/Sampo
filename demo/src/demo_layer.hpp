#pragma once
#include "sampo.hpp"

namespace Sampo
{
	class Keyboard;
	class Event;
}

class DemoLayer : public Sampo::Layer
{
public:
	DemoLayer();
	~DemoLayer() = default;

	void OnAttach() override;
	void OnUpdate(Sampo::Timestep aDeltaTime) override;
	void OnImGuiRender() override;

private:
	std::shared_ptr<Sampo::SoundEffect> m_TestSFX;
	std::shared_ptr<Sampo::SoundEffect> m_TestMusic;
	std::shared_ptr<Sampo::SoundEffect> m_TestMusic2;

	bool m_PlayMusic{ false };
};