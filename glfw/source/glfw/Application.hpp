#pragma once
#include <vulkan/vulkan.hpp>
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
		/*************************************************************************/
		/**
		A function that can be overridden by the derived class to respond to an
		event where a joystick is connected.

		This function is usually called on poll_events ( ). However, it is
		possible for certain systems to call it asynchronously and in parallel to
		the program's execution.

		@param id
		The id of the joystick.

		@return
		Nothing.
		**************************************************************************/
		virtual void on_joystick_connected ( const std::size_t id );
		virtual void on_joystick_disconnected ( const std::size_t id );
	};
}