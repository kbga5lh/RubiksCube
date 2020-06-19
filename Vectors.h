#pragma once

#include "glew.h"

namespace gl3d
{
	struct Vec2i
	{
		GLint x;
		GLint y;

		Vec2i(GLint n_x = 0, GLint n_y = 0)
			: x(n_x), y(n_y) {}
	};

	struct Vec2f
	{
		GLfloat x;
		GLfloat y;

		Vec2f(GLfloat n_x = 0, GLfloat n_y = 0)
			: x(n_x), y(n_y) {}
	};

	struct Vec2d
	{
		GLdouble x;
		GLdouble y;

		Vec2d(GLdouble n_x = 0, GLdouble n_y = 0)
			: x(n_x), y(n_y) {}
	};

	struct Vec3i
	{
		GLint x;
		GLint y;
		GLint z;

		Vec3i(GLint n_x = 0, GLint n_y = 0, GLint n_z = 0)
			: x(n_x), y(n_y), z(n_z) {}
	};

	struct Vec3f
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;

		Vec3f(GLfloat n_x = 0, GLfloat n_y = 0, GLfloat n_z = 0)
			: x(n_x), y(n_y), z(n_z) {}
	};
}