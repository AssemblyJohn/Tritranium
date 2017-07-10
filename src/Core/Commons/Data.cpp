#include "Data.h"

BEGIN_TRITRANIUM

PData::PData() :
	mBytes(nullptr),
	mByteSize(0)
{ }

PData::PData(const PData &other) :
	mBytes(nullptr),
	mByteSize(0)
{
	Copy(other.mBytes, other.mByteSize);
}

PData::PData(PData &&other) :
	mBytes(nullptr),
	mByteSize(0)
{
	Move(other);
}

PData::PData(uint8 *bytes, int32 size) :
	mBytes(bytes),
	mByteSize(size)
{ }

PData::~PData()
{
	Free();
}

PData& PData::operator=(const PData &other)
{	
	Copy(other.mBytes, other.mByteSize);
	return *this;
}

PData& PData::operator=(PData &&other)
{	
	Move(other);
	return *this;
}

void PData::Move(PData &other)
{
	CHK(mBytes == nullptr);

	mBytes = other.mBytes;
	mByteSize = other.mByteSize;

	other.mBytes = nullptr;
	other.mByteSize = 0;
}

void PData::Copy(const uint8* bytes, const uint32 size)
{
	Free();

	if (size > 0)
	{
		// Set data
		mByteSize = size;
		mBytes = (uint8 *)PMemory::Malloc(size);

		// Copy data from the bytes
		PMemory::Memcpy(mBytes, bytes, size);
	}
}

void PData::Assign(uint8* bytes, const uint32 size)
{
	Free();

	mBytes = bytes;
	mByteSize = size;
}

void PData::Free()
{
	if (mBytes != nullptr)
	{
		PMemory::Free(mBytes);
		mBytes = nullptr;		
	}
	
	mByteSize = 0;
}

END_TRITRANIUM