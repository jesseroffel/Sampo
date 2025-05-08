#include "sampo/core/application.hpp"

#include "demo_layer.hpp"
#include "renderer2D_layer.hpp"

int main(int argc, char* argv[])
{
	using namespace Sampo;

	StartParams startParams;
	startParams.m_ApplicationName = "Demo - Sampo Application";
	startParams.m_Argc = argc;
	startParams.m_Argv = argv;
	startParams.m_EnableImGui = true;

	if (!Application::Create(startParams))
	{
		SAMPO_CRITICAL("Unable to start application!");
		return 1;
	}

	Application& application = Application::GetInstance();

	const glm::vec2& windowSize = application.GetPlatform()->GetWindow()->GetWindowSize();
	//DemoLayer* demolayer = new DemoLayer(windowSize);
	//application.PushLayer(demolayer);
	Renderer2DLayer* render2DLayer = new Renderer2DLayer(windowSize);
	application.PushLayer(render2DLayer);

	application.Run();

	application.PopLayer(render2DLayer);
	delete render2DLayer;
	//application.PopLayer(demolayer);
	//delete demolayer;

	application.Shutdown();
	return 0;
}