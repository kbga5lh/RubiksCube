#include "Window.h"

#include "Time.h"

namespace gl3d
{
	GLFWwindow* Window::m_window = nullptr;
	Vec2i Window::m_size;

	void Window::create(const Vec2i& size, const std::string& title)
	{
		if (m_window)
		{
			Log::debug("Can't create window! There is another windows that is active!");
			return;
		}
		Log::create();
		Log::debug("Window::create");
		if (!glfwInit())
			Log::error("Failed to initialize glfw");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		m_window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
		if (!m_window)
			Log::error("Failed to create window");

		glfwMakeContextCurrent(m_window);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			Log::error("Failed to initialize glew");

		glViewport(0, 0, size.x, size.y);
		glEnable(GL_DEPTH_TEST);
		m_size = size;
	}

	void Window::destroy()
	{
		Log::debug("Window::destroy");
		glfwDestroyWindow(m_window);
		m_window = nullptr;
		m_size = 0;
		glfwTerminate();
	}

	void Window::clear(const Color & clearColor)
	{
		glClearColor(Color::toGLcolor(clearColor.red),
			Color::toGLcolor(clearColor.green),
			Color::toGLcolor(clearColor.blue),
			Color::toGLcolor(clearColor.alpha));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::show()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
		gl3d::Time::update();
	}
}