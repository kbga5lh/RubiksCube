#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Time.h"

namespace gl3d
{
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right,
		Forward,
		Backward,
	};

	enum class Axis
	{
		X,
		Y,
		Z,
	};

	class Camera
	{
	private:
		static float m_yaw;
		static float m_pitch;

		static glm::vec3 m_cameraPos;
		static glm::vec3 m_cameraFront;
		static glm::vec3 m_cameraUp;

		static glm::mat4 m_projection;

	public:
		static void projection(float fov, float aspect, float zNear, float zFar)
		{
			m_projection = glm::perspective(fov, aspect, zNear, zFar);
		}

		static void rotate(float angle, Axis axis);

		static void move(float speed, Direction dir);

		static glm::mat4 getView()
		{
			return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
		}

		static glm::mat4& getProjection()
		{
			return m_projection;
		}
	};
}