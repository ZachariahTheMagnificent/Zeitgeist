#include "CPPWindow.hpp"

namespace glfw
{
	Window::Handle Window::create_handle ( const char*const name, const std::size_t width, const std::size_t height )
	{
		// Request 4x antialiasing
		glfwWindowHint ( GLFW_SAMPLES, 4 );

		// We don't need OpenGL
		glfwWindowHint ( GLFW_CLIENT_API, GLFW_NO_API );

		// We'll deal with resizing later
		glfwWindowHint ( GLFW_RESIZABLE, GLFW_FALSE );

		return Handle { glfwCreateWindow ( static_cast< int >( width ), static_cast< int >( height ), name, nullptr, nullptr ) };
	}

	Window& Window::get_window ( const Handle handle )
	{
		return *reinterpret_cast< Window* >( glfwGetWindowUserPointer ( handle ) );
	}

	Window::Window ( const char*const name, const std::size_t width, const std::size_t height ) : handle_ { create_handle ( name, 800, 600 ) }
	{
		//give glfw the pointer to this
		glfwSetWindowUserPointer ( handle_, this );

		//Setting up the different callbacks
		glfwSetWindowSizeCallback ( handle_, [ ] ( GLFWwindow* handle, int width, int height )
		{
			Window::get_window ( handle ).on_window_resized ( width, height );
		} );
		glfwSetFramebufferSizeCallback ( handle_, [ ] ( GLFWwindow* handle, int width, int height )
		{
			Window::get_window ( handle ).on_frame_buffer_resized ( width, height );
		} );
		glfwSetCharCallback ( handle_, [ ] ( GLFWwindow* handle, unsigned character )
		{
			Window::get_window ( handle ).on_character_typed ( character );
		} );
		glfwSetKeyCallback ( handle_, [ ] ( GLFWwindow* handle, int key, int scancode, int action, int mods )
		{
			auto& window = Window::get_window ( handle );

			std::bitset<4> modifiers = mods;

			window.on_key_event ( KeyEvent ( Key ( key ), KeyEvent::State ( action ), modifiers, scancode ) );
		} );
		glfwSetDropCallback ( handle_, [ ] ( GLFWwindow* handle, int count, const char** paths )
		{
			auto& window = Window::get_window ( handle );

			for ( std::size_t i = 0; i < static_cast< std::size_t >( count ); ++i )
			{
				window.on_file_dropped ( paths [ i ] );
			}
		} );
		glfwSetMouseButtonCallback ( handle_, [ ] ( GLFWwindow* handle, int button, int action, int mods )
		{
			auto& window = Window::get_window ( handle );

			std::bitset<4> modifiers = mods;

			window.on_key_event ( KeyEvent ( Key ( button ), KeyEvent::State ( action ), modifiers, 0 ) );
		} );
		glfwSetCursorPosCallback ( handle_, [ ] ( GLFWwindow* handle, double xpos, double ypos )
		{
			Window::get_window ( handle ).on_mouse_move ( xpos, ypos );
		} );
		glfwSetCursorEnterCallback ( handle_, [ ] ( GLFWwindow* handle, int entered )
		{
			if ( entered == GL_TRUE )
			{
				Window::get_window ( handle ).on_mouse_enter ( );
			}
			else if ( entered == GL_FALSE )
			{
				Window::get_window ( handle ).on_mouse_exit ( );
			}
		} );
		glfwSetScrollCallback ( handle_, [ ] ( GLFWwindow* handle, double xoffset, double yoffset )
		{
			Window::get_window ( handle ).on_scroll ( xoffset, yoffset );
		} );
	}

	Window::~Window ( )
	{
		glfwDestroyWindow ( handle_ );
	}

	Window::Size Window::size ( ) const
	{
		Size size;
		glfwGetWindowSize ( handle_, size.data ( ) + 0, size.data ( ) + 1 );
		return size;
	}

	bool Window::is_set_to_close ( ) const noexcept
	{
		return glfwWindowShouldClose ( handle_ );
	}

	void Window::set_to_close ( )
	{
		glfwSetWindowShouldClose ( handle_, GL_TRUE );
	}

	void Window::set_to_fullscreen ( )
	{
		glfwSetWindowMonitor ( handle_, glfwGetPrimaryMonitor ( ), 0, 0, 0, 0, GLFW_DONT_CARE );
	}

	void Window::set_to_windowed ( const int top_left_x, const int top_left_y, const int width, const int height )
	{
		glfwSetWindowMonitor ( handle_, nullptr, top_left_x, top_left_y, width, height, GLFW_DONT_CARE );
	}

	void Window::swap_buffers ( )
	{
		glfwSwapBuffers ( handle_ );
	}

	const char* Window::get_clipboard ( ) const
	{
		return glfwGetClipboardString ( handle_ );
	}

	void Window::set_clipboard ( const char * const string )
	{
		glfwSetClipboardString ( handle_, string );
	}

	void Window::enable_mouse_movement ( )
	{
		glfwSetInputMode ( handle_, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
	}

	void Window::disable_mouse_movement ( )
	{
		glfwSetInputMode ( handle_, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
	}

	void Window::set_mouse_position ( const MousePosition position )
	{
		glfwSetCursorPos ( handle_, position [ 0 ], position [ 2 ] );
	}

	void Window::hide_mouse ( )
	{
		glfwSetInputMode ( handle_, GLFW_CURSOR, GLFW_CURSOR_HIDDEN );
	}

	void Window::on_window_resized ( const int width, const int height )
	{

	}

	void Window::on_frame_buffer_resized ( const int width, const int height )
	{

	}

	void Window::on_character_typed ( const unsigned character )
	{

	}

	void Window::on_key_event ( const KeyEvent key )
	{

	}

	void Window::on_file_dropped ( const char * const file_path )
	{

	}

	void Window::on_mouse_enter ( )
	{

	}

	void Window::on_mouse_exit ( )
	{

	}

	void Window::on_mouse_move ( const double xpos, const double ypos )
	{

	}

	void Window::on_scroll ( const double xoffset, const double yoffset )
	{

	}
}