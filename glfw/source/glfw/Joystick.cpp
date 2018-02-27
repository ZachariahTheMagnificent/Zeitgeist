#include "Joystick.hpp"

namespace glfw
{
	Joystick::Joystick ( std::size_t id ) : index ( index )
	{
		update ( );
	}

	std::size_t Joystick::GetIndex ( )
	{
		return index;
	}

	const char* Joystick::GetName ( )
	{
		return name;
	}

	const float* Joystick::GetAxesBegin ( )
	{
		return axes_begin;
	}

	const float* Joystick::GetAxesEnd ( )
	{
		return axes_end;
	}

	const unsigned char* Joystick::GetButtonsBegin ( )
	{
		return buttons_begin;
	}

	const unsigned char* Joystick::GetButtonsEnd ( )
	{
		return buttons_end;
	}
	
	void Joystick::update ( )
	{
		// Get the name
		name = glfwGetJoystickName ( index );

		// Get the axes
		int axes_count;

		axes_begin = glfwGetJoystickAxes ( index, &axes_count );
		axes_end = axes_begin + axes_count;

		// Get the buttons
		int button_count;

		buttons_begin = glfwGetJoystickButtons ( index, &button_count );
		buttons_end = buttons_begin + button_count;
	}
}
