#pragma once

#include "glfw3.h"

namespace gl3d
{
	class Time
	{
	private:
		static float m_delta;
		static float m_lastFrame;

	public:
		static float getDelta()
		{
			return m_delta;
		}

		static void update()
		{
			float currentFrame = glfwGetTime();
			m_delta = currentFrame - m_lastFrame;
			m_lastFrame = currentFrame;
		}
	};
}