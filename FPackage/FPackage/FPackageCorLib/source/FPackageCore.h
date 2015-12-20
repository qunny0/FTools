#pragma once
#include "FPackageDefine.h"

#include <string>
#include <vector>
#include <stdint.h>

NS_FPACKAGE_BEGIN

class IReadFile;
class IWriteFile;

class IFPackage
{
public:
	virtual const std::string& getPackageName() const = 0;

	// readFile
	virtual bool hasFile(const std::string& filename) const = 0;
	virtual IReadFile* openFile(const std::string& filename) = 0;

	// writeFile
	virtual uint32_t getFileCount() const = 0;

	virtual void addFile(const std::string& relativeFilePath) = 0;

	virtual void readFileDataToPackage(const std::string& absoluteFilePath) = 0;

protected:
	std::string		_strPackageName;
};



//////////////////////////////////////////////////////////////////////////

IFPackage*	createFPackage(const std::string& filename, uint32_t chunkSize = 0x40000, uint32_t fileUserDataSize = 0);

IFPackage*	openFPackage(const std::string& packagePath);

NS_FPACKAGE_END