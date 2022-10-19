#include "Core.h"
#include "Application.h"
#include "game/Game.h"
#include "game/Scene.h"
#include "game/Entity.h"
#include "dotnet/Dotnet.h"
#include "rendering/Renderer.h"

namespace Laska
{
	enum class lskInitResult : int32_t
	{
		Ok = 0,
		Failed = -1,
		FailedInitLogger = -2,
		FailedInitDotnet = -3,
		FailedInitGLFW = -4,
		FailedInitRenderer = -5,
		FailedInitAudio = -6,
		FailedInitResourceManager = -7,
	};

	struct RegistrypSecification
	{

	};

	struct EngineSetupSpecification
	{
		DotnetSpecification Dotnet;
	};

	LASKA_API bool lskEngineStartup(const EngineSetupSpecification& specs)
	{
		if (!::Laska::Logger::Init())
		{
			return false;
		}

		if (glfwInit() != GLFW_TRUE)
		{
			LASKA_LOG_CRITICAL("Failed to initialize GLFW.");
			return false;
		}

		if (!::Laska::Renderer::Init())
		{
			LASKA_LOG_CRITICAL("Failed to initialize Renderer.");
			return false;
		}

		if (!::Laska::Dotnet::Init(specs.Dotnet))
		{
			LASKA_LOG_CRITICAL("Failed to initialize .NET.");
			return false;
		}

		lskInitResult::Ok;

		return true;
	}

	LASKA_API void lskEngineShutdown()
	{
		Dotnet::Dispose();
		glfwTerminate();
	}

	LASKA_API Application* lskApplicationCreate(const ApplicationSpecification& specs)
	{
		return new Application(specs);
	}

	LASKA_API void lskApplicationDestroy(Application* app)
	{
		delete app;
	}

	LASKA_API void lskApplicationStart(Application* app)
	{
		app->Start();
	}

	LASKA_API void lskGameLoadScene(Game* game, uint64_t scene)
	{
		game->LoadScene(scene);
	}
}
