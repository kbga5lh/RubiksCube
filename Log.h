#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <ctime>
#include <iostream>

namespace gl3d
{
	class Log
	{
	private:

		static bool isFileOpened;
		static std::ofstream file;

	public:

		static void create(const char* fileName = "log.txt");
		static void close();
		static void error(const char* text);
		static void debug(const char* text);
	};
}