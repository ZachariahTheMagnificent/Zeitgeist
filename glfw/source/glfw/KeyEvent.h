#pragma once
#include "Key.hpp"
#include <bitset>

namespace glfw
{
	class KeyEvent
	{
	public:
		enum class State
		{
			pressed = GLFW_PRESS,
			released = GLFW_RELEASE
		};
		enum class Modifier
		{
			super = GLFW_MOD_SUPER,
			shift = GLFW_MOD_SHIFT,
			ctrl = GLFW_MOD_CONTROL,
			alt = GLFW_MOD_ALT
		};

		explicit KeyEvent ( const Key key, const State state, const std::bitset<4> modifiers, const int scancode ) noexcept;

		Key get_key ( ) const noexcept;
		State get_state ( ) const noexcept;
		int get_scan_code ( ) const noexcept;

		template<Modifier modifier>
		bool is_modified ( ) const noexcept
		{
			switch ( modifier )
			{
				case Modifier::super:
				{
					return ( modifiers_ & std::bitset<4> { GLFW_MOD_SUPER } ).any ( );
				}
				case Modifier::shift:
				{
					return ( modifiers_ & std::bitset<4> { GLFW_MOD_SHIFT } ).any ( );
				}
				case Modifier::ctrl:
				{
					return ( modifiers_ & std::bitset<4> { GLFW_MOD_CONTROL } ).any ( );
				}
				case Modifier::alt:
				{
					return ( modifiers_ & std::bitset<4> { GLFW_MOD_ALT } ).any ( );
				}
			}
			return false;
		}

	private:
		const Key key_;
		const State state_;
		const std::bitset<4> modifiers_;
		const int scancode_;
	};
}