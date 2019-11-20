#include "core/engine.h"

int main(char* argc, char** argv)
{
	Rakas::Engine* engine = Rakas::Engine::Rakas_Init(RAKAS_INIT_BASIC);
	printf("HelloWorld!");
	engine->Rakas_Quit();
	return 0;
}