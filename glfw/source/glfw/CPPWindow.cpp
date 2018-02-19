#include "CPPWindow.hpp"

namespace glfw
{
	Window::Handle Window::create_handle ( const char*const name, const std::size_t width, const std::size_t height )
	{
		glfwWindowHint ( GLFW_CLIENT_API, GLFW_NO_API );
		glfwWindowHint ( GLFW_RESIZABLE, GLFW_FALSE );
		return Handle { glfwCreateWindow ( static_cast< int >( width ), static_cast< int >( height ), name, nullptr, nullptr ) };
	}

	Window::Window ( const char*const name, const std::size_t width, const std::size_t height ) : handle_ { create_handle ( name, 800, 600 ) }
	{
	}

	Window::operator bool ( ) const noexcept
	{
		return bool { handle_ };
	}

	bool Window::is_set_to_close ( ) const noexcept
	{
		return glfwWindowShouldClose ( handle_.get ( ) );
	}

	void Window::Deleter::operator() ( const pointer pointer ) const noexcept
	{
		glfwDestroyWindow ( pointer );
	}
}