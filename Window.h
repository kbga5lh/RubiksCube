#pragma once

#include "Vectors.h"
#include "Color.h"
#include "Log.h"

#include "glfw3.h"
#include "glew.h"

#include <string>

namespace gl3d
{
	class Window
	{
	private:
		static GLFWwindow *m_window;
		static Vec2i m_size;

	public:

		static GLFWwindow* getInstance()
		{ return m_window; }

		static bool shouldClose()
		{ return glfwWindowShouldClose(m_window); }

		static Vec2i size()
		{ return m_size; }

		static bool exist()
		{ return (bool)m_window; }

		static void create(const Vec2i& size, const std::string& title);

		static void destroy();

		static void clear(const Color& clearColor);

		static void show();
	};
}