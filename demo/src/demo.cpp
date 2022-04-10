#include "sampo.hpp"
#include "networktest.hpp"

class Demo : public Sampo::Application
{
public:
	Demo()
	{
		PushLayer(new NetworkTest());
	}
	~Demo() = default;
};

Sampo::Application* Sampo::CreateApplication()
{
	return new Demo();
}