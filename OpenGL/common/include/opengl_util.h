#ifndef OPENGL_UTIL_H
#define OPENGL_UTIL_H

#include <string>
#include <stdlib.h>
#include <stdint.h>
using std::string;

extern void OgldevFileError(const char* pFileName, uint32_t line, const char* pFileError);
#define OGLDEV_FILE_ERROR(FileError) OgldevFileError(__FILE__, __LINE__, FileError);

extern bool ReadFile(const char* fileName, string& outFile);

#endif