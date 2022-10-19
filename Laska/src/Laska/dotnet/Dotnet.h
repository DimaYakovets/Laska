#pragma once

#include <stdint.h>

#include <Laska/dotnet/hostfxr/hostfxr.h>
#include <Laska/dotnet/hostfxr/coreclr_delegates.h>
#include <Laska/memory/MemoryUtils.h>

#ifdef _WIN32
#define STR(str) L##str
#else
#define STR(str) str
#endif 

#define FLAG(f) 1 << (f - 1)

#define DOTNET_API_CALLCONV __cdecl

#define DOTNET_VERSION STR("6.0.5")
#define DOTNET_ROOT_NAME STR("dotnet")
#define DOTNET_HOSTFXR_DLL_PATH DOTNET_ROOT_NAME STR("\\host\\fxr\\") DOTNET_VERSION STR("\\hostfxr.dll")

#define DOTNET_MAIN_DLL_PATH STR("Laska.Dotnet.dll")
#define DOTNET_MAIN_DLL_RUNTIME_CONFIG_PATH STR("Laska.Dotnet.runtimeconfig.json")
#define DOTNET_MAIN_ASSEMBLY_NAME STR("Laska.Dotnet")
#define DOTNET_MAIN_CLASS_NAME STR("Laska.Dotnet.Bridge, ") DOTNET_MAIN_ASSEMBLY_NAME
#define DOTNET_INIT_FUNC_NAME STR("Init")

#define DefineFuncPtr(ret, name, ...) typedef ret (DOTNET_API_CALLCONV* name)(__VA_ARGS__)

namespace Laska
{
	using dotnet_char = wchar_t;
	using dotnet_string = dotnet_char*;
	using dotnet_object = void*;
	using dotnet_field = uint32_t;
	using dotnet_type = uint32_t;

	using dotnet_static_method = void*;

	enum class dotnet_gc_collection_mode
	{
		gc_default = 0,
		gc_forced = 1,
		gc_optimized = 2
	};

	struct dotnet_method
	{
		dotnet_type type;
		uint32_t handle;
	};

	enum class dotnet_base_types
	{
		dotnet_byte, // C++ : unsigned char
		dotnet_sbyte, // C++ : char
		
		dotnet_short, // C++ : int16_t
		dotnet_ushort, // C++ : uint16_t
		dotnet_char, // C++ : wchar_t
		
		dotnet_int, // C++ : int32_t
		dotnet_uint, // C++ : uint32_t
		
		dotnet_long, // C++ : int64_t
		dotnet_ulong, // C++ : uint64_t

		dotnet_float, // C++ : float
		dotnet_double, // C++ : double

		dotnet_intptr, // C++ : void*

		dotnet_handle, // C++ : uint64_t

		dotnet_vector2, // C++ : glm::vec2
		dotnet_vector3, // C++ : glm::vec3
		dotnet_vector4, // C++ : glm::vec4

		dotnet_matrix2, // C++ : glm::mat2
		dotnet_matrix3, // C++ : glm::mat3
		dotnet_matrix4, // C++ : glm::mat4
	};

	enum class dotnet_lsk_behaviour_flags
	{
		lsk_init = FLAG(1),
		lsk_early_update = FLAG(2),
		lsk_fixed_update = FLAG(3),
		lsk_update = FLAG(4),
		lsk_late_update = FLAG(5),
		lsk_delete = FLAG(6),
		lsk_on_collision_enter = FLAG(7),
		lsk_on_collision_exit = FLAG(8)
	};

	DefineFuncPtr(dotnet_object, dotnet_create_instance_fn, dotnet_type type);
	DefineFuncPtr(void, dotnet_finalize_fn, dotnet_object object);
	DefineFuncPtr(void, dotnet_call_init_fn, dotnet_object object, dotnet_type type);
	DefineFuncPtr(void, dotnet_call_early_update_fn, dotnet_object object, dotnet_type type, float arg0);
	DefineFuncPtr(void, dotnet_call_fixed_update_fn, dotnet_object object, dotnet_type type, float arg0);
	DefineFuncPtr(void, dotnet_call_update_fn, dotnet_object object, dotnet_type type, float arg0);
	DefineFuncPtr(void, dotnet_call_late_update_fn, dotnet_object object, dotnet_type type, float arg0);
	DefineFuncPtr(void, dotnet_call_delete_fn, dotnet_object object, dotnet_type type);

	//!!! This API is not implemented yet. !!!
	DefineFuncPtr(void, dotnet_set_byte_fn, dotnet_object object, dotnet_field field, uint8_t value);
	DefineFuncPtr(void, dotnet_set_ushort_fn, dotnet_object object, dotnet_field field, uint16_t value);
	DefineFuncPtr(void, dotnet_set_uint_fn, dotnet_object object, dotnet_field field, uint32_t value);
	DefineFuncPtr(void, dotnet_set_ulong_fn, dotnet_object object, dotnet_field field, uint64_t value);

	DefineFuncPtr(void, dotnet_set_sbyte_fn, dotnet_object object, dotnet_field field, int8_t value);
	DefineFuncPtr(void, dotnet_set_short_fn, dotnet_object object, dotnet_field field, int16_t value);
	DefineFuncPtr(void, dotnet_set_int_fn, dotnet_object object, dotnet_field field, int32_t value);
	DefineFuncPtr(void, dotnet_set_long_fn, dotnet_object object, dotnet_field field, int64_t value);

	DefineFuncPtr(void, dotnet_set_float_fn, dotnet_object object, dotnet_field field, float value);
	DefineFuncPtr(void, dotnet_set_double_fn, dotnet_object object, dotnet_field field, double value);

	DefineFuncPtr(void, dotnet_call_on_collision_enter_fn, dotnet_object object, dotnet_type type, void* manifold);
	DefineFuncPtr(void, dotnet_call_on_collision_exit_fn, dotnet_object object, dotnet_type type, void* manifold);
	DefineFuncPtr(void, dotnet_invoke_fn, dotnet_object object, dotnet_method method, void* args);
	DefineFuncPtr(void, dotnet_gc_collect_fn);
	DefineFuncPtr(void, dotnet_gc_collect_gen_fn, int32_t generation);
	DefineFuncPtr(void, dotnet_gc_collect_gen_mode_fn, int32_t generation, dotnet_gc_collection_mode mode);
	DefineFuncPtr(void, dotnet_gc_try_start_no_gc_fn, int64_t totalSize);
	DefineFuncPtr(void, dotnet_gc_end_no_gc_fn);

	struct dotnet_api_funcs
	{
		dotnet_create_instance_fn dotnet_create_instance;
		dotnet_finalize_fn dotnet_finalize;
		dotnet_call_init_fn dotnet_call_init;
		dotnet_call_early_update_fn dotnet_call_early_update;
		dotnet_call_fixed_update_fn dotnet_call_fixed_update;
		dotnet_call_update_fn dotnet_call_update;
		dotnet_call_late_update_fn dotnet_call_late_update;
		dotnet_call_delete_fn dotnet_call_delete;
		dotnet_call_on_collision_enter_fn dotnet_call_on_collision_enter;
		dotnet_call_on_collision_exit_fn dotnet_call_on_collision_exit;
	};

	struct dotnet_method_arg_info
	{
		wchar_t* name;
		wchar_t* type;
		uint32_t index;
	};

	struct dotnet_method_info
	{
		wchar_t* name;
		dotnet_method method;
	};

	struct dotnet_type_info
	{
		wchar_t* name;
		dotnet_type type;
		Span<dotnet_method_info> defined_methods;
	};

	struct dotnet_init_info
	{
		Span<void*> native_api_functions_ptrs;
		Span<dotnet_string> dll_paths;

		dotnet_api_funcs* api_functions;
		Span<dotnet_type_info>* defined_types;
	};

	DefineFuncPtr(void, dotnet_init_fn, dotnet_init_info* info);

	struct DotnetSpecification
	{
		bool UseExternalDotnet;
		dotnet_init_fn DotnetInit;
	};

	class Dotnet
	{
	public:
		static bool Init(const DotnetSpecification& specs);

		static void Dispose();

		inline static dotnet_object CreateInstance(dotnet_type type)
		{

			return s_api.dotnet_create_instance(type);
		}

		inline static void CallInit(dotnet_object object, dotnet_type type)
		{
			s_api.dotnet_call_init(object, type);
		}

		inline static void CallUpdate(dotnet_object object, dotnet_type type)
		{
			s_api.dotnet_call_update(object, type, 0);
		}

		inline static void CallDelete(dotnet_object object, dotnet_type type)
		{
			s_api.dotnet_call_delete(object, type);
		}

	private:
		static void InitWithHostfxr(const DotnetSpecification& specs);
		static void InitWithExternalHooks(const DotnetSpecification& specs);

		static void DisposeHostfxr();
		static void DisposeExternal();
	
	private:
		static bool s_isExternalDotnetUsage;
		static dotnet_api_funcs s_api;
		static Span<dotnet_type_info> s_defined_types;
	};
}
