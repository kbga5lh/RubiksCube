#include "Camera.h"

namespace gl3d
{
	float Camera::m_yaw = -90.0f;
	float Camera::m_pitch = 0.0f;

	glm::vec3 Camera::m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 Camera::m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Camera::m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 Camera::m_projection(1.0f);

	void Camera::move(float speed, Direction dir)
	{
		if (dir == Direction::Forward)
			m_cameraPos += speed * m_cameraFront;
		else if (dir == Direction::Backward)
			m_cameraPos -= speed * m_cameraFront;
		else if (dir == Direction::Left)
			m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * speed;
		else if (dir == Direction::Right)
			m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * speed;
	}

	void Camera::rotate(float angle, Axis axis)
	{
		if (axis == Axis::Y)
		{
			m_pitch += angle;
			if (m_pitch > 89.0f)
				m_pitch = 89.0f;
			else if (m_pitch < -89.0f)
				m_pitch = -89.0f;
		}
		else if (axis == Axis::X)
		{
			m_yaw += angle;
		}

		glm::vec3 front;
		front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
		front.y = sin(glm::radians(m_pitch));
		front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
		m_cameraFront = glm::normalize(front);
	}
}