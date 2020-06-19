#include "Time.h"

namespace gl3d
{
	float Time::m_delta = 0.0f;	// Время, прошедшее между последним и текущим кадром
	float Time::m_lastFrame = 0.0f; // Время вывода последнего кадра
}