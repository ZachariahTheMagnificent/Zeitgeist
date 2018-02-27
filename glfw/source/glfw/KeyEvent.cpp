#include "KeyEvent.h"

namespace glfw
{
	KeyEvent::KeyEvent ( const Key key, const State state, const std::bitset<4> modifiers, const int scancode ) noexcept : key_ ( key ), state_ ( state ), modifiers_ ( modifiers ), scancode_ ( scancode )
	{
	}

	Key KeyEvent::get_key ( ) const noexcept
	{
		return key_;
	}

	KeyEvent::State KeyEvent::get_state ( ) const noexcept
	{
		return state_;
	}

	int KeyEvent::get_scan_code ( ) const noexcept
	{
		return scancode_;
	}
}