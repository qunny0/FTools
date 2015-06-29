#pragma once
#include "FPackageDefine.h"

#include <string>
#include <stdint.h>

NS_FPACKAGE_BEGIN

class IReadFile;
class IWriteFile;

class IFPackage
{
public:
	virtual std::string& getPackageName() const = 0;

	// readFile
	virtual bool hasFile(const std::string& filename) const = 0;
	virtual IReadFile* openFile(const std::string& filename) const = 0;

	// writeFile
	virtual uint32_t getFileCount() = 0;
};



//////////////////////////////////////////////////////////////////////////

IFPackage*	createFPackage(const std::string& filename, uint32_t chunkSize = 0x40000, uint32_t fileUserDataSize = 0);

NS_FPACKAGE_END