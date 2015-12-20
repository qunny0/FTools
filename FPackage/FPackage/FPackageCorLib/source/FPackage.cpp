#include "FPackage.h"

NS_FPACKAGE_BEGIN

const std::string& FPackage::getPackageName() const
{
	return _strPackageName;
}

bool FPackage::hasFile(const std::string& filename) const
{
	return false;
}

IReadFile* FPackage::openFile(const std::string& filename)
{
	return nullptr;
}

uint32_t FPackage::getFileCount() const
{
	return 0;
}

void FPackage::addFile(const std::string& relativeFilePath)
{

}

void FPackage::readFileDataToPackage(const std::string& absoluteFilePath)
{

}

NS_FPACKAGE_END