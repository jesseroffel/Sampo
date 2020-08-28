#include <sampo.hpp>
#include <iostream>
#include "mathtests.hpp"

class Demo : public Sampo::Application
{
public:
	Demo() = default;	// Change to adding an object that will be looped through with Sampo
	~Demo() = default;
	virtual void Init() override
	{
		PushLayer(new mathtests());
	}
};

// Client application creation //

Sampo::Application* Sampo::CreateApplication()
{
	return new Demo();
}