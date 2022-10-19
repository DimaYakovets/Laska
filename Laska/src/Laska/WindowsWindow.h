#pragma once
#include "Window.h"

namespace Laska
{
	class WindowsWindow : public Window
	{
	private:
		bool m_vsync;

		GLFWwindow* m_handle;

	private:
		void Init(const WindowSpecification& specs);
		void Destroy();

	public:
		WindowsWindow(const WindowSpecification& specs);
		~WindowsWindow();

		virtual bool VSync() const override;
		virtual void SetVSync(bool vsync) override;
		virtual GLFWwindow* GetHandle() const override;
	};
}
