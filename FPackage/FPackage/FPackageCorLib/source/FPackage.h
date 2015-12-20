#pragma once

#include "FPackageCore.h"

NS_FPACKAGE_BEGIN

class FPackage : public IFPackage
{
public:
	FPackage();
	virtual ~FPackage();

// interface
	
	virtual const std::string& getPackageName() const;

	// readFile
	virtual bool hasFile(const std::string& filename) const;
	virtual IReadFile* openFile(const std::string& filename);

	// writeFile
	virtual uint32_t getFileCount() const;

	virtual void addFile(const std::string& relativeFilePath);

	virtual void readFileDataToPackage(const std::string& absoluteFilePath);

};

NS_FPACKAGE_END