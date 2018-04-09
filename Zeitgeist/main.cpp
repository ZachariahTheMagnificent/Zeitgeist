/*************************************************************************/
/** Contains the entrypoint of the program.

Copyright (C) 2017-2018 Zachariah The Magnificent
<zachariah@zachariahs.world>.

This file is part of Zeitgeist.

Zeitgeist is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published bythe Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

Zeitgeist is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along
with Zeitgeist.If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/
#include <iostream>
#include <stdexcept>
#include <functional>
#include <memory>

#include <glfw/Application.hpp>
#include <glfw/CPPWindow.hpp>
#include <common/Debugging.h>

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT (
	VkInstance                                  instance,
	const VkDebugReportCallbackCreateInfoEXT*   pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDebugReportCallbackEXT*                   pCallback )
{
	auto func = ( PFN_vkCreateDebugReportCallbackEXT ) vkGetInstanceProcAddr ( instance, "vkCreateDebugReportCallbackEXT" );
	if ( func != nullptr )
	{
		return func ( instance, pCreateInfo, pAllocator, pCallback );
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}
VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT (
	VkInstance                                  instance,
	VkDebugReportCallbackEXT                    callback,
	const VkAllocationCallbacks*                pAllocator )
{
	auto func = ( PFN_vkDestroyDebugReportCallbackEXT ) vkGetInstanceProcAddr ( instance, "vkDestroyDebugReportCallbackEXT" );
	if ( func != nullptr )
	{
		func ( instance, callback, pAllocator );
	}
}

class TestApp : public glfw::Application
{
public:
	TestApp ( )
	{
		init_vulkan ( );
	}

	void run ( )
	{
		while ( !window.is_set_to_close ( ) )
		{
			poll_events ( );
		}
	}

private:
	void init_vulkan ( )
	{
		auto info = vk::ApplicationInfo { "Test App", VK_MAKE_VERSION ( 1, 0, 0 ), "Zeitgeist", VK_MAKE_VERSION ( 1, 0, 0 ), VK_API_VERSION_1_0 };

		uint32_t glfw_extension_count = 0;
		const char** glfw_extension_names = glfwGetRequiredInstanceExtensions ( &glfw_extension_count );

		std::vector<const char*> requested_layer_names;
		auto requested_extension_names = std::vector<const char*> ( glfw_extension_names, glfw_extension_names + glfw_extension_count );

		if constexpr ( common::debugging::is_enabled )
		{
			requested_layer_names.push_back ( "VK_LAYER_LUNARG_standard_validation" );
			requested_extension_names.push_back ( "VK_EXT_debug_report" );
		}

		auto extensions = vk::enumerateInstanceExtensionProperties ( nullptr );
		auto layers = vk::enumerateInstanceLayerProperties ( );

		if constexpr ( common::debugging::is_enabled )
		{
			std::cout << extensions.size ( ) << " extensions supported" << std::endl;

			for ( auto& extension : extensions )
			{
				std::cout << extension.extensionName << '\n';
			}

			std::cout << '\n';

			std::cout << layers.size ( ) << " layers supported" << std::endl;

			for ( auto& layer : layers )
			{
				std::cout << layer.layerName << '\n';
			}

		}

		auto has_layer = [ ] ( const char* layer_name, const std::vector<vk::LayerProperties>& layers )
		{
			for ( auto layer : layers )
			{
				if ( std::strcmp ( layer_name, layer.layerName ) == 0 )
				{
					return true;
				}
			}

			return false;
		};

		for ( auto requested_layer_name : requested_layer_names )
		{
			if ( !has_layer ( requested_layer_name, layers ) )
			{
				throw std::runtime_error { std::string { } + "Requested layer " + requested_layer_name + " was not found!" };
			}
		}

		auto create_instance_info = vk::InstanceCreateInfo
		{
			{ }, &info,
			requested_layer_names.size ( ), &requested_layer_names.front ( ),
			requested_extension_names.size ( ), &requested_extension_names.front ( )
		};

		instance = vk::createInstanceUnique ( create_instance_info );
		auto debug_callback_info = vk::DebugReportCallbackCreateInfoEXT {vk::DebugReportFlagBitsEXT::eError | vk::DebugReportFlagBitsEXT::eWarning, debug_callback };
		debug_callback_handle = instance->createDebugReportCallbackEXTUnique ( debug_callback_info );

		auto devices = instance->enumeratePhysicalDevices ( );

		auto properties = devices.front ( ).getProperties ( );
		auto features = devices.front ( ).getFeatures ( );
		auto device_type = properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu;
		auto geometry_Shader = features.geometryShader;

		auto families = devices.front ( ).getQueueFamilyProperties ( );
		auto queue_count = families.front ( ).queueCount;
		auto graphics_queue = families.front ( ).queueFlags & vk::QueueFlagBits::eGraphics;
		bool found = static_cast< bool >( graphics_queue );

		//VkSurfaceKHR surface;
		//VkResult err = glfwCreateWindowSurface ( instance, window, NULL, &surface );
		//if ( err )
		//{
		//	throw AAAAAAAAAAAAAAHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH();
		//}
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback (
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData )
	{

		std::cout << "validation layer: " << msg << std::endl;

		return VK_FALSE;
	}

	glfw::Window window { "Test App", 800, 600 };
	vk::UniqueInstance instance;
	vk::UniqueDebugReportCallbackEXT debug_callback_handle;
};

int main ( )
{
	try
	{
		TestApp app;
		app.run ( );
	}
	catch ( const std::exception& e )
	{
		std::cerr << "An error has occured!\n";
		std::cerr << e.what ( ) << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}