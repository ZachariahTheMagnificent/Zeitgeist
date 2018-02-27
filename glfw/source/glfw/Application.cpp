#include "Application.hpp"
#include <stdexcept>

namespace glfw
{
	static Application* current_application = nullptr;

	Application::Application ( )
	{
		if ( current_application )
		{
			throw std::runtime_error { "There can only be one GLFW application at a time!" };
		}

		if ( glfwInit ( ) == GLFW_FALSE )
		{
			throw std::runtime_error { "GLFW has failed to initialise!" };
		}

		current_application = this;

		glfwSetJoystickCallback ( [ ] ( int joy, int event )
		{
			if ( event == GLFW_CONNECTED )
			{
				current_application->on_joystick_connected ( joy );
			}
			else if ( event == GLFW_DISCONNECTED )
			{
				current_application->on_joystick_disconnected ( joy );
			}
		} );
	}

	Application::~Application ( )
	{
		glfwTerminate ( );
	}

	void Application::poll_events ( )
	{
		glfwPollEvents ( );
	}

	void Application::on_joystick_connected ( const std::size_t id )
	{
	}

	void Application::on_joystick_disconnected ( const std::size_t id )
	{
	}
}