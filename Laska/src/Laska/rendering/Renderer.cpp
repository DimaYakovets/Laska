#include "Renderer.h"

namespace Laska
{
	VkInstance Renderer::s_vkInstance;

	bool Renderer::Init()
	{
		const char* validationLayer = "VK_LAYER_KHRONOS_validation";
		const char** glfwExtensions;
		uint32_t glfwExtensionCount = 0;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		if (glfwVulkanSupported() != GLFW_TRUE) 
		{
			LASKA_LOG_CRITICAL("This PC does not support Vulkan.");
		}

		for (size_t i = 0; i < glfwExtensionCount; i++)
		{
			LASKA_LOG_INFO("GLFW extention for Vulkan: {0}.", glfwExtensions[i]);
		}

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Laska";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Laska Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo instanceInfo{};
		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pApplicationInfo = &appInfo;
		
		instanceInfo.enabledExtensionCount = glfwExtensionCount;
		instanceInfo.ppEnabledExtensionNames = glfwExtensions;

		instanceInfo.enabledLayerCount = 1;
		instanceInfo.ppEnabledLayerNames = &validationLayer;

		VkResult result = vkCreateInstance(&instanceInfo, nullptr, &s_vkInstance);

		if (result != VkResult::VK_SUCCESS)
		{
			LASKA_LOG_CRITICAL("Failed to create Vulkan instance.");

			return false;
		}

		return true;
	}
}