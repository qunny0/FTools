#pragma once
#include <stdint.h>

// namespace
#define NS_FPACKAGE_BEGIN namespace F_PACKAGE {
#define NS_FPACKAGE_END	}

#define USING_NS_FPACKAGE using namespace F_PACKAGE
#define NS_FPACKAGE	F_PACKAGE::

NS_FPACKAGE_BEGIN

const uint32_t	PACKAGE_FILE_SIGN = 'FPAK';
const uint32_t	PACKAGE_VERSION = '0629';

const char PACKAGE_EXT_NAME[4] = "zpk";

#pragma pack(4)

struct PackageHeader
{
	uint32_t	sign;
	uint32_t	version;
	uint32_t	headerSize;
	uint32_t	fileCount;
};

struct FileEntity
{
	uint32_t	byteOffset;
	uint32_t	packSize;		// size in package (may be compressed)
	uint32_t	originSize;		// before compressed file size
	uint64_t	nameHash;		// file directory
};

#pragma pack()

NS_FPACKAGE_END