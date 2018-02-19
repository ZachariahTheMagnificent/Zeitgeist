#include "Application.hpp"
#include <stdexcept>

namespace glfw
{
	static Application* app_instance = nullptr;

	Joystick::Joystick ( const char*const name, const float*const axes_begin, const float*const axes_end,
			   const unsigned char*const buttons_begin, const unsigned char*const buttons_end )
		:
		name { name },
		axes_begin { axes_begin },
		axes_end { axes_end },
		buttons_begin { buttons_begin },
		buttons_end { buttons_end }
	{

	}

	std::unique_ptr<Application> Application::create_instance ( )
	{
		glfwSetJoystickCallback ( [ ] ( int joy, int event )
		{
			if ( event == GLFW_CONNECTED )
			{

			}
			else if ( event == GLFW_DISCONNECTED )
			{

			}
		} );

		if ( app_instance != nullptr )
		{
			throw std::runtime_error { "GLFW has already been initialised!" };
		}
		
		app_instance = new Application { };

		return std::unique_ptr<Application> { app_instance };
	}

	Application::Application ( )
	{
		if ( glfwInit ( ) == GLFW_FALSE )
		{
			throw std::runtime_error { "GLFW has failed to initialise!" };
		}
	}
	Application::~Application ( )
	{
		glfwTerminate ( );
	}

	void Application::poll_events ( )
	{
		glfwPollEvents ( );
	}

	Joystick Application::GetJoystick ( const std::size_t index )
	{
		// Get the name
		auto name = glfwGetJoystickName ( index );

		// Get the axes
		int axes_count;

		auto axes_begin = glfwGetJoystickAxes ( index, &axes_count );
		auto axes_end = axes_begin + axes_count;

		// Get the buttons
		int button_count;

		auto buttons_begin = glfwGetJoystickButtons ( index, &button_count );
		auto buttons_end = buttons_begin + button_count;

		return Joystick { name, axes_begin, axes_end, buttons_begin, buttons_end };
	}
}