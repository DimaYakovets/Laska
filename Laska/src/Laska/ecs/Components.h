#pragma once

#include <string>
#include <glm/glm.hpp>

#include <Laska/memory/MemoryUtils.h>
#include <Laska/utils/EnumUtils.h>
#include <Laska/dotnet/Dotnet.h>

#include <Laska/gui/UIControl.h>

#define TypeIndexStruct(type, i) template<> struct type_index<##type> { static const uint64_t index = i; }
#define TypeIndex(type) type_index<##type>::index 
#define DefineComponent bool Enabled

namespace Laska
{
	using ptr = void*;

	enum class RigidBodyType : uint32_t
	{
		Static = 0,
		Dynamic = 1,
		Kinematic = 2
	};

	enum class CameraType : uint32_t
	{
		Orthogonal = 0,
		Perspective = 1
	};

	enum class ClipType : uint32_t
	{
		ListFrames,
		KeyFrames
	};


	enum class StyleProperty : uint16_t
	{
		Width,
		Height
	};

	enum class ScriptCallback : uint32_t
	{
		Init = FlagI32(1),
	};

	struct AABB
	{
		glm::vec2 Min;
		glm::vec2 Max;
	};

	struct Basis2D
	{
		glm::vec2 X;
		glm::vec2 Y;
	};

	struct Transform
	{
		glm::vec3 Position;
		glm::vec2 Scale;
		float Angle;
	};

	struct Hierarchy
	{
		Hierarchy* pParent;
		Transform* pTransform;
		Span<Hierarchy> Children;
	};

	struct Label
	{
		std::wstring Text;
	};

	struct Camera
	{
		CameraType Type;
		float Far;
		float Near;
		float Width;
		float Height;
		float Scale;
	};

	struct SpriteRenderer
	{
		glm::vec2 Size;
		glm::vec2 Offset;
		glm::vec4 Color;
		bool FlipX;
		bool FlipY;
	};

	struct BoxCollider
	{
		glm::vec2 Min;
		glm::vec2 Max;
	};

	struct CircleCollider
	{
		float Radius;
	};

	struct RigidBody
	{
		RigidBodyType Type;
		glm::vec2 Velocity;
		float Density;
		float Friction;
		float Restitution;
		float GravityScale;
		float LinearDrag;
		float AngularDrag;
		bool FreezRotation;
	};

	struct Frame
	{

	};

	struct Clip
	{
		ClipType Type;
		Span<Frame> Frames;
	};

	struct Animator
	{
		uint64_t Id;
		float Time;
		bool Looped;
	};

	struct Grid
	{
		uint32_t Width;
		uint32_t Height;
		uint32_t CellSize;

		void* Cells;

		void (__cdecl *Init)(void*);
		void (__cdecl *Update)(void*);
	};

	struct CSharpScript
	{
		bool Enabled;
		dotnet_object instance;
		dotnet_type_info type;
	};


	struct UIRenderer
	{
		Style* BaseStyle;
		UIControl* Root;
	};

	static const uint32_t ComponentsCount = 8;

	template<typename TComponent>
	struct type_index;

	TypeIndexStruct(Transform, 0);
	TypeIndexStruct(Hierarchy, 1);
	TypeIndexStruct(Camera, 2);
	TypeIndexStruct(CSharpScript, 3);
	TypeIndexStruct(SpriteRenderer, 4);
	TypeIndexStruct(BoxCollider, 5);
	TypeIndexStruct(CircleCollider, 6);
	TypeIndexStruct(RigidBody, 7);
	TypeIndexStruct(Grid, 8);
}
