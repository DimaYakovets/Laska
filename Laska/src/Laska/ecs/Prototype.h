#pragma once

#include <stdint.h>
#include <Laska/ecs/EntityMatrix.h>
#include <Laska/memory/MemoryUtils.h>
#include <Laska/memory/PageAllocator.h>

#define BuiltInComponent(component) { TypeIndex(component), sizeof(component) }

namespace Laska
{
	using Prototype = uint32_t;

	struct Component
	{
		uint32_t Index;
		size_t Size;
	};

	struct PrototypeInfo
	{
		Span<Component> Components;
	};

	struct PrototypeData
	{
		Span<PageAllocator> Allocators;
		Span<uint16_t> Mappers;
		EntityMatrix Matrix;
	};
}
