#include "FPackageCore.h"

#include "FPackage.h"

using std::locale;
using std::fstream;
using std::ios_base;

NS_FPACKAGE_BEGIN

IFPackage*	createFPackage(const std::string& filename, uint32_t chunkSize /*= 0x40000*/, uint32_t fileUserDataSize /*= 0*/)
{
	PackageHeader header;
	header.sign = PACKAGE_FILE_SIGN;
	header.version = PACKAGE_VERSION;
	header.headerSize = sizeof(PackageHeader);
	header.fileCount = 0;

	FILE* file = fopen(filename.c_str(), "w+");
	if (!file)
	{
		return nullptr;
	}
	auto size = fwrite(&header, sizeof(header), 1, file);
	fclose(file);

	auto package = openFPackage(filename);
	return package;
}

IFPackage* openFPackage(const std::string& packagePath)
{
	FPackage* package = new FPackage();
	package->openFile(packagePath);

	return package;
}


NS_FPACKAGE_END
