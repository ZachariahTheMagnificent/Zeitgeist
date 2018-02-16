#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

int main ( )
{
	glfwInit ( );

	glfwWindowHint ( GLFW_CLIENT_API, GLFW_NO_API );
	GLFWwindow* window = glfwCreateWindow ( 800, 600, "Vulkan window", nullptr, nullptr );

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties ( nullptr, &extensionCount, nullptr );

	std::cout << extensionCount << " extensions supported" << std::endl;

	//VkSurfaceKHR surface;
	//VkResult err = glfwCreateWindowSurface ( instance, window, NULL, &surface );
	//if ( err )
	//{
	//	AAAAAAAAAAAAAAHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH();
	//}

	while ( !glfwWindowShouldClose ( window ) )
	{
		glfwPollEvents ( );
	}

	glfwDestroyWindow ( window );

	glfwTerminate ( );

	return 0;
}