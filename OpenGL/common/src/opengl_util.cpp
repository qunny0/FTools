#include "opengl_util.h"
#include <iostream>
#include <fstream>

#ifdef WIN32
#include <Windows.h>
#endif // _DEBUG

bool ReadFile(const char* fileName, string& outFile)
{
	std::ifstream f(fileName);

	bool ret = false;

	if (f.is_open())
	{
		string line;
		while (getline(f, line)) 
		{
			outFile.append(line);
			outFile.append("\n");
		}

		f.close();

		ret = true;
	}
	else {
		OGLDEV_FILE_ERROR(fileName);
	}

	return ret;
}

void OgldevFileError(const char* pFileName, uint32_t line, const char* pFileError)
{
#ifdef WIN32
	char msg[1000] = {};
	_snprintf_s(msg, sizeof(msg), "%s:%d: unable to open file '%s'", pFileName, line, pFileError);
	MessageBoxA(NULL, msg, NULL, 0);
#endif
}