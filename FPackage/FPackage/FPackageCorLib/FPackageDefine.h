#pragma once

#include <stdint.h>

// namespace
#define NS_FPACKAGE_BEGIN namespace F_PACKAGE {
#define NS_FPACKAGE_END	}

#define USING_NS_FPACKAGE using namespace F_PACKAGE
#define NS_FPACKAGE	F_PACKAGE::



NS_FPACKAGE_BEGIN

const uint32_t	PACKAGE_FILE_SIGN	= 'FPAK';
const uint64_t	PACKAGE_VERSION		= '20150626';

const char PACKAGE_EXT_NAME[4] = "pak";

#pragma pack(4)

struct PackageHeader
{
	uint32_t	sign;
	uint32_t	version;
	uint32_t	headerSize;
	uint32_t	fileCount;
	uint32_t	fileEntryOffset;
	uint32_t	filenameOffset;
	uint32_t	allFileEntrySize;
	uint32_t	allFilenameSize;
	uint32_t	originFilenamesSize;	//filename size before compression
	uint32_t	chunkSize;				//file compress unit
	uint32_t	flag;
	uint32_t	fileEntrySize;
	uint32_t	reserved[18];
};

struct FileEntity
{

};

#pragma pack()

NS_FPACKAGE_END

