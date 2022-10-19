#pragma once

#include <Laska/Core.h>

namespace Laska
{
	class Renderer
	{
	public:
		static bool Init();

	private:
		static VkInstance s_vkInstance;
	};
}
