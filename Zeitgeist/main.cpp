#include <iostream>
#include <stdexcept>
#include <functional>
#include <memory>

#include <glfw/Application.hpp>
#include <glfw/CPPWindow.hpp>

class TestApp : public glfw::Application
{
public:
	TestApp ( )
	{
	}

	void run ( )
	{
		initVulkan ( );

		while ( !window.is_set_to_close ( ) )
		{
			poll_events ( );
		}
	}

private:
	void initVulkan ( )
	{
		std::vector<int> f;
		auto info = vk::ApplicationInfo { "Test App", VK_MAKE_VERSION ( 1, 0, 0 ), "Zeitgeist", VK_MAKE_VERSION ( 1, 0, 0 ), VK_API_VERSION_1_0 };
		uint32_t glfwextensioncount = 0;
		const char** glfwextensions;

		glfwextensions = glfwGetRequiredInstanceExtensions ( &glfwextensioncount );

		auto create_instance_info = vk::InstanceCreateInfo { { }, &info, 0, nullptr, glfwextensioncount, glfwextensions };
		auto instance = vk::createInstanceUnique ( create_instance_info );

		auto extensions = vk::enumerateInstanceExtensionProperties ( nullptr );

		std::cout << extensions.size ( ) << " extensions supported" << std::endl;

		for ( auto& extension : extensions )
		{
			std::cout << extension.extensionName << '\n';
		}

		//VkSurfaceKHR surface;
		//VkResult err = glfwCreateWindowSurface ( instance, window, NULL, &surface );
		//if ( err )
		//{
		//	throw AAAAAAAAAAAAAAHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH();
		//}
	}

	glfw::Window window { "Test App", 800, 600 };
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