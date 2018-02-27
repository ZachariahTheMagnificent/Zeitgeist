#include "Key.hpp"
#include <cassert>

namespace glfw
{
	int get_scan_code ( const Key key )
	{
		assert ( "This function is incomplete!", false );
		return 0;
	}

	const char* get_key_name ( const Key key )
	{
		return glfwGetKeyName ( static_cast< int >( key ), int { } );
	}

	const char* get_key_name ( const int scan_code )
	{
		return glfwGetKeyName ( GLFW_KEY_UNKNOWN, scan_code );
	}
}
