#include <iostream>

#define LASKA_API extern "C" __declspec(dllimport)

namespace Laska
{
	class Application;

	struct DotnetSpecification
	{
		bool UseExternalDotnet;
		void* Init;
	};

	struct EngineSetupSpecification
	{
		DotnetSpecification Dotnet;
	};

	struct ApplicationSpecification
	{
		uint32_t WindowHeight;
		uint32_t WindowWidth;
		bool FullScreen;
		bool VSync;
	};

	LASKA_API bool lskEngineStartup(const EngineSetupSpecification& specs);
	LASKA_API void lskEngineShutdown();
	LASKA_API Application* lskApplicationCreate(const ApplicationSpecification& specs);
	LASKA_API void lskApplicationDestroy(Application* app);
	LASKA_API void lskApplicationStart(Application* app);
}

int main()
{
	using namespace Laska;

	EngineSetupSpecification specs{};
	specs.Dotnet.UseExternalDotnet = false;

	if (lskEngineStartup(specs))
	{
		ApplicationSpecification specs{};
		specs.WindowHeight = 720;
		specs.WindowWidth = 1280;
		specs.FullScreen = true;
		specs.VSync = true;

		Application* app = Laska::lskApplicationCreate(specs);
		lskApplicationStart(app);
		lskApplicationDestroy(app);

		lskEngineShutdown();
	}

	std::cin.get();

	return 0;
}
