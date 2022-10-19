#include <stdint.h>
#include <Laska/memory/MemoryUtils.h>

namespace Laska
{
	enum class UIControlType : uint32_t
	{
		Block,
		Grid,
		Dock,
		Stack,

		Canvas,
		Image,

		Button,
		Checkbox,
		Textbox,
		Slider,
		Dropdown
	};

	struct DropdownValue
	{
		wchar_t* Label;
	};

	struct DropdownData
	{
		uint32_t ItemsCount;
		DropdownValue* Items;
		DropdownValue* SelectedItem;
	};

	struct Style
	{
		float Width;
		float Height;
	};

	struct UIControl
	{
		Style* Style;
		UIControl* Parent;
		void* Context;
		UIControlType Type;
	};

	struct Page
	{
		UIControl Root;
	};

	struct Interface
	{
		Span<Page> Pages;
 	};
}
