#pragma once
#include "c/include/GLFW/glfw3.h"
#include "Joystick.hpp"
#include <memory>

namespace glfw
{
	class Application
	{
	public:
		static constexpr std::size_t maximum_joysticks = GLFW_JOYSTICK_LAST + 1;

		Application ( );
		~Application ( );

		Application( const Application& ) = delete;
		Application& operator=( const Application& ) = delete;

		void poll_events ( );

	private:
		virtual void on_joystick_connected ( const std::size_t id );
		virtual void on_joystick_disconnected ( const std::size_t id );
	};
}