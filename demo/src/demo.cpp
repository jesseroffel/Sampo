#include <sampo.hpp>
#include <iostream>

class Demo : public Sampo::Application
{
public:
	Demo() = default;	// Change to adding an object that will be looped through with Sampo
	~Demo() = default;

};

// Client application creation //

Sampo::Application* Sampo::CreateApplication()
{
	return new Demo();
}