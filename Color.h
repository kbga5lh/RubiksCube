#pragma once

#include <cstdint>

namespace gl3d
{
	struct Color
	{
		GLubyte red;
		GLubyte green;
		GLubyte blue;
		GLubyte alpha;

		Color(GLubyte n_red = 0, GLubyte n_green = 0, GLubyte n_blue = 0, GLubyte n_alpha = 0)
			: red(n_red), green(n_green), blue(n_blue) {}

		static float toGLcolor(GLubyte color)
		{ return color / 255.0f; }
	};
}