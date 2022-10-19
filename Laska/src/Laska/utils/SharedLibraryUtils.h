#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

namespace Laska
{
	void* load_shared_library(const char_t* path)
	{
#ifdef _WIN32
		return (void*)::LoadLibraryW(path);
#else
		return dlopen(path, RTLD_LAZY | RTLD_LOCAL);
#endif
	}

	bool close_shared_library(void* hadnle)
	{
#ifdef _WIN32
		return ::FreeLibrary((HMODULE)hadnle);
#else
		return dlopen(path, RTLD_LAZY | RTLD_LOCAL);
#endif
	}

	void* get_shared_library_export(void* handle, const char* name)
	{
#ifdef _WIN32
		return ::GetProcAddress((HMODULE)handle, name);
#else
		return dlsym(handle, name);
#endif
	}

	template<typename T>
	T get_shared_library_export_typed(void* handle, const char_t* name)
	{
		return (T)get_shared_library_export(handle, name);
	}
}
