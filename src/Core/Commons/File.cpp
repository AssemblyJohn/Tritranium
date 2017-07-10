#include "File.h"

#include <iostream>
#include <fstream>

#include "String.h"
#include "Data.h"

BEGIN_TRITRANIUM

PString PFileUtils::ReadEntireFile(const PString &path)
{
	::std::ifstream _ifstream;
	_ifstream.open(path.c_str(), std::ios::in | std::ios::binary);

	_ifstream.seekg(0, std::ios_base::end);
	std::streamoff file_length = _ifstream.tellg();
	_ifstream.seekg(0, std::ios_base::beg);
	_ifstream.clear();

	void *outData = PMemory::Malloc(file_length);;
	uint32 outRead = file_length;

	// Read
	_ifstream.read(((char*)(outData)), file_length);

	std::string str = std::string((char *)outData, outRead);

	PMemory::Free(outData);

	return PString(str);
}

PData PFileUtils::ReadEntireFileData(const PString &path)
{
	std::ifstream _ifstream;
	_ifstream.open(path.c_str(), std::ios::in | std::ios::binary);

	_ifstream.seekg(0, std::ios_base::end);
	std::streamoff file_length = _ifstream.tellg();
	_ifstream.seekg(0, std::ios_base::beg);
	_ifstream.clear();

	void *outData = PMemory::Malloc(file_length);
	uint32 outRead = file_length;

	// Read data
	_ifstream.read(((char*)(outData)), file_length);

	// Return new data
	return PData((uint8 *)outData, outRead);
}

END_TRITRANIUM