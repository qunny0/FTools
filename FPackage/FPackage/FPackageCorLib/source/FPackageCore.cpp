#include "FPackageCore.h"

#include <fstream>

using std::locale;
using std::fstream;
using std::ios_base;

NS_FPACKAGE_BEGIN

IFPackage*	createFPackage(const std::string& filename, uint32_t chunkSize /*= 0x40000*/, uint32_t fileUserDataSize /*= 0*/)
{
	fstream stream;
	locale loc = locale::global(locale(""));
	stream.open(filename, ios_base::out | ios_base::trunc | ios_base::binary);
	locale::global(loc);
	if (!stream.is_open())
	{
		return nullptr;
	}

	PackageHeader header;

	header.sign = PACKAGE_FILE_SIGN;
	header.version = PACKAGE_VERSION;
	header.headerSize = sizeof(PackageHeader);
	header.fileCount = 0;

	stream.write((char*)&header, sizeof(header));
	stream.close();

	return nullptr;
}

NS_FPACKAGE_END
