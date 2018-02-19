#pragma once
#include "c/include/GLFW/glfw3.h"
#include <memory>

namespace glfw
{
	class Joystick
	{
	public:
		static constexpr std::size_t maximum_total = GLFW_JOYSTICK_LAST;

		Joystick ( ) = default;
		Joystick ( const char*const name, const float*const axes_begin, const float*const axes_end,
				   const unsigned char*const buttons_begin, const unsigned char*const buttons_end );

		const char* name { };
		const float* axes_begin { };
		const float* axes_end { };
		const unsigned char* buttons_begin { };
		const unsigned char* buttons_end { };
	};

	class Application
	{
	public:
		static std::unique_ptr<Application> create_instance ( );

		~Application ( );

		Application( const Application& ) = delete;
		Application& operator=( const Application& ) = delete;

		void poll_events ( );

		Joystick GetJoystick ( const std::size_t id );

	private:
		Application ( );
	};
}