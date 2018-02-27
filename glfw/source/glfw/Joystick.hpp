#pragma once
#include <utility>
#include "c/include/GLFW/glfw3.h"

namespace glfw
{
	class Joystick
	{
	public:
		Joystick ( std::size_t id );

		std::size_t GetIndex ( );
		const char* GetName ( );

		const float* GetAxesBegin ( );
		const float* GetAxesEnd ( );

		const unsigned char* GetButtonsBegin ( );
		const unsigned char* GetButtonsEnd ( );

		void update ( );

	private:
		std::size_t index;
		const char* name { };
		const float* axes_begin { };
		const float* axes_end { };
		const unsigned char* buttons_begin { };
		const unsigned char* buttons_end { };
	};
}