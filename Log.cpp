#include "Log.h"

namespace gl3d
{
	std::ofstream Log::file;
	bool Log::isFileOpened = false;

	void Log::create(const char* fileName)
	{
		if (isFileOpened)
		{
			file.close();
			isFileOpened = false;
		}
		file.open(fileName, std::ios::trunc);
		if (file.is_open())
		{
			std::time_t t = std::time(0);
			std::tm* now = std::localtime(&t);

			file << "Log started: " << now->tm_year + 1900 << ':'
				<< now->tm_mon + 1 << ':' << now->tm_mday << '\n'
				<< "==================================" << '\n';
			isFileOpened = true;
		}
	}

	void Log::close()
	{
		if (!isFileOpened)
			return;
		isFileOpened = false;
	}

	void Log::error(const char* text)
	{
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);

		std::cout << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec
			<< " ERROR - " << text << '\n';

		if (isFileOpened)
		{
			file << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec
				<< " ERROR - " << text << '\n';
		}

		close();
		exit(EXIT_FAILURE);
	}

	void Log::debug(const char* text)
	{
#ifdef _DEBUG

		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);

		std::cout << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec
			<< " - " << text << '\n';

		if (isFileOpened)
		{
			file << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec
				<< " - " << text << '\n';
		}

#endif // _DEBUG
	}
}