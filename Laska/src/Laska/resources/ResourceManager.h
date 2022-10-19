#pragma once
#include "Resources.h"
#include <unordered_map>

namespace Laska
{
	class ResourceManager
	{
	private:
		std::unordered_map<uint64_t, Audio> m_audios;
		std::unordered_map<uint64_t, Texture> m_textures;

	public:
		Texture LoadTexture(const char* path);
	};
}
