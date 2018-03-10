#pragma once
#include <cassert>

namespace common
{
	namespace debugging
	{
#if defined NDEBUG
		constexpr auto is_enabled = false;
#else
		constexpr auto is_enabled = true;
#endif
	}
}