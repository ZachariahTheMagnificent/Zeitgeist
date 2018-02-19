#include <iostream>
#include <stdexcept>
#include <functional>
#include <memory>

#include <vulkan/vulkan.hpp>
#include <glfw/Application.hpp>
#include <glfw/CPPWindow.hpp>
#include <thread>
#include <queue>
#include <type_traits>

template<typename Type>
class ApplicationTraits
{
public:
	static void on_key_pressed ( Type& application, const char key )
	{
		application.on_key_pressed ( key );
	}
};

template<typename Application>
class Keyboard
{
public:
	Keyboard ( )
	{
		keys.push ( 'a' );
	}
	void Update ( Application& app )
	{
		//Receive key presses

		while ( !keys.empty ( ) )
		{
			auto key = keys.front ( );
			ApplicationTraits<Application>::on_key_pressed ( app, key );
			keys.pop ( );
		}
	}

private:
	std::queue<char> keys;
};

class Application
{
public:
	void OnKeyPressed ( const char key )
	{
		keys.push ( key );
	}

private:
	std::queue<char> keys;
};

template<>
class ApplicationTraits<Application>
{
public:
	static void on_key_pressed ( Application& application, const char key )
	{
		std::cout << key << " pressed!\n";
		application.OnKeyPressed ( key );
	}
};

class TestApp
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
			app->poll_events ( );
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

	std::unique_ptr<glfw::Application> app = glfw::Application::create_instance ( );
	glfw::Window window { "Test App", 800, 600 };
};

template<typename Member, typename ReturnType>
struct HasMember_
{
	using Type = ReturnType;
};

template<typename Member, typename ReturnType = void>
using HasMember = typename HasMember_<Member, ReturnType>::Type;

template<typename Type>
HasMember<decltype(&Type::OnKeyPressed)> HasFoo ( )
{
	std::cout << "Yes!\n";
}

template<typename Type>
HasMember<decltype(&Type::on_key_pressed)> HasFoo ( )
{
	std::cout << "No!\n";
}

int main ( )
{
	HasFoo<Application> ( );
	constexpr bool x = &TestApp::run;
	TestApp app;

	try
	{
		app.run ( );
	}
	catch ( const std::exception& e )
	{
		std::cerr << e.what ( ) << std::endl;
		return EXIT_FAILURE;
	}
	class X
	{
	public:
		using foo = int;
	};

	return EXIT_SUCCESS;
}