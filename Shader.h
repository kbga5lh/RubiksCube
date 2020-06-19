#pragma once
#define GLEW_STATIC
#include <glew.h>
#include "Log.h"
#include <sstream>

namespace gl3d
{
	class Shader
	{
	public:
		Shader() {}
		Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
		{
			Compile(vertexShaderPath, fragmentShaderPath);
		}
		void Compile(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
		void Use()
		{
			glUseProgram(program);
		}
		GLuint GetProgram() { return program; }

	private:
		GLuint program;

		GLuint compileShader(const GLchar* shaderPath, GLenum shaderType);
	};
}