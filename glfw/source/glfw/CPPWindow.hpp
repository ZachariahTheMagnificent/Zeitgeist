#pragma once
#include "c/include/GLFW/glfw3.h"
#include "KeyEvent.h"

#include <array>

namespace glfw
{
	class Window
	{
	public:
		using Size = std::array<int, 2>;
		using MousePosition = std::array<double, 2>;

		Window ( ) = default;
		Window ( const char*const name, const std::size_t width, const std::size_t height );
		~Window ( );

		Window ( const Window& ) = delete;
		Window& operator= ( const Window& ) = delete;

		Size size ( ) const;

		bool is_set_to_close ( ) const noexcept;
		void set_to_close ( );

		void set_to_fullscreen ( );
		void set_to_windowed ( const int top_left_x, const int top_left_y, const int width, const int height );

		void swap_buffers ( );

		const char* get_clipboard ( ) const;
		void set_clipboard ( const char*const string );

		void enable_mouse_movement ( );
		void disable_mouse_movement ( );
		void set_mouse_position ( const MousePosition position );
		void hide_mouse ( );

	private:
		using Handle = GLFWwindow*;

		static Handle create_handle ( const char*const name, const std::size_t width, const std::size_t height );
		static Window& get_window ( const Handle handle );

		virtual void on_window_resized ( const int width, const int height );
		virtual void on_frame_buffer_resized ( const int width, const int height );

		virtual void on_character_typed ( const unsigned character );
		virtual void on_key_event ( const KeyEvent key );

		virtual void on_file_dropped ( const char*const file_path );

		virtual void on_mouse_enter ( );
		virtual void on_mouse_exit ( );
		virtual void on_mouse_move ( const double xpos, const double ypos );

		virtual void on_scroll ( const double xoffset, const double yoffset );

		Handle handle_;
	};
}