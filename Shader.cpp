#include "Shader.h"

namespace gl3d
{
	void Shader::Compile(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
	{
		GLint success;
		GLchar infoLog[512];

		program = glCreateProgram();

		GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
		GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 512, 0, infoLog);
			std::string error = "Failed to link shaders: ";
			error.append(infoLog);
			Log::error(error.c_str());
		}

		glUseProgram(program);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	GLuint Shader::compileShader(const GLchar* shaderPath, GLenum shaderType)
	{
		GLint success;
		GLchar infoLog[512];

		std::string shaderString;

		GLuint shader;
		shader = glCreateShader(shaderType);

		std::ifstream shaderFile(shaderPath);

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		shaderString = shaderStream.str();
		const GLchar* shaderSource = shaderString.c_str();

		glShaderSource(shader, 1, &shaderSource, 0);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 512, 0, infoLog);
			std::string error = "Failed to compile shader: ";
			error.append(infoLog);
			Log::error(error.c_str());
		}

		return shader;
	}
}