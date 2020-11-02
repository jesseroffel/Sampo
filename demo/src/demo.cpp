#include <sampo/sampo.hpp>
#include "demolayer.hpp"

class Demo : public Sampo::Application
{
public:
	Demo() = default;	// Change to adding an object that will be looped through with Sampo
	~Demo() = default;
	virtual void Init() override
	{
		PushLayer(new DemoLayer());
	}
};

// Client application creation //

Sampo::Application* Sampo::CreateApplication()
{
	return new Demo();
}