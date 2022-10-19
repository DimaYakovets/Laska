#include "Dotnet.h"

#include <Laska/Core.h>
#include <Laska/utils/SharedLibraryUtils.h>

namespace Laska
{
	static hostfxr_handle s_hostfxr_handle;
	static void* s_hostfxr_dll;
	static hostfxr_close_fn s_hostfxr_close;

	dotnet_init_fn s_dotnet_init;

	dotnet_api_funcs Dotnet::s_api;
	Span<dotnet_type_info> Dotnet::s_defined_types;
	bool Dotnet::s_isExternalDotnetUsage;

	bool Dotnet::Init(const DotnetSpecification& specs)
	{
		if (specs.UseExternalDotnet)
		{
			InitWithExternalHooks(specs);
		}
		else
		{
			InitWithHostfxr(specs);
		}

		if (s_dotnet_init == nullptr)
		{
			return false;
		}

		dotnet_init_info info{};
		info.api_functions = &s_api;
		info.defined_types = &s_defined_types;

		s_dotnet_init(&info);

		LASKA_LOG_INFO("C# Module has been initialized successfully.");
		LASKA_LOG_INFO("C# Module has found {0} script(s).", s_defined_types.Length);

	}

	void Dotnet::InitWithHostfxr(const DotnetSpecification& specs)
	{
		load_assembly_and_get_function_pointer_fn hostfxr_load_assembly_and_get_function_pointer;
		hostfxr_initialize_for_runtime_config_fn hostfxr_initialize_for_runtime_config;
		hostfxr_get_runtime_delegate_fn hostfxr_get_runtime_delegate;
		hostfxr_get_runtime_properties_fn hostfxr_get_runtime_properties;

		s_hostfxr_dll = load_shared_library(DOTNET_HOSTFXR_DLL_PATH);

		if (s_hostfxr_dll == 0)
		{
			LASKA_LOG_ERROR("Failed to load hostfxr.dll.");
			return;
		}

		hostfxr_initialize_for_runtime_config =
			(hostfxr_initialize_for_runtime_config_fn)get_shared_library_export(s_hostfxr_dll, ("hostfxr_initialize_for_runtime_config"));

		s_hostfxr_close =
			(hostfxr_close_fn)get_shared_library_export(s_hostfxr_dll, ("hostfxr_close"));

		hostfxr_get_runtime_delegate =
			(hostfxr_get_runtime_delegate_fn)get_shared_library_export(s_hostfxr_dll, ("hostfxr_get_runtime_delegate"));

		hostfxr_get_runtime_properties =
			(hostfxr_get_runtime_properties_fn)get_shared_library_export(s_hostfxr_dll, ("hostfxr_get_runtime_properties"));

		if (hostfxr_initialize_for_runtime_config == nullptr ||
			s_hostfxr_close == nullptr ||
			hostfxr_get_runtime_delegate == nullptr ||
			hostfxr_get_runtime_properties == nullptr)
		{
			LASKA_LOG_ERROR("Failed to load hostfxr.dll exports.");
			return;
		}

		hostfxr_initialize_for_runtime_config(DOTNET_MAIN_DLL_RUNTIME_CONFIG_PATH, nullptr, &s_hostfxr_handle);

		if (s_hostfxr_handle == 0)
		{
			LASKA_LOG_ERROR("Failed to initialize hostfxr.dll.");
			return;
		}

		hostfxr_get_runtime_delegate(s_hostfxr_handle,
			hostfxr_delegate_type::hdt_load_assembly_and_get_function_pointer,
			reinterpret_cast<void**>(&hostfxr_load_assembly_and_get_function_pointer));

		if (hostfxr_load_assembly_and_get_function_pointer == nullptr)
		{
			LASKA_LOG_ERROR("Failed to get runtime delegate: {1}",
				"load_assembly_and_get_function_pointer");
			return;
		}

		hostfxr_load_assembly_and_get_function_pointer(
			DOTNET_MAIN_DLL_PATH,
			DOTNET_MAIN_CLASS_NAME,
			DOTNET_INIT_FUNC_NAME,
			UNMANAGEDCALLERSONLY_METHOD,
			nullptr,
			(void**)&s_dotnet_init
		);
	}

	void Dotnet::InitWithExternalHooks(const DotnetSpecification& specs)
	{
		s_dotnet_init = specs.DotnetInit;
		s_isExternalDotnetUsage = true;
	}

	void Dotnet::DisposeHostfxr()
	{
		s_hostfxr_close(s_hostfxr_handle);
		close_shared_library(s_hostfxr_dll);
	}

	void Dotnet::DisposeExternal()
	{
	}

	void Dotnet::Dispose()
	{
		if (s_isExternalDotnetUsage)
		{
			DisposeExternal();
		}
		else
		{
			DisposeHostfxr();
		}
	}
}
