#pragma once

#include "Platform\Platform.h"
#include "Platform\PlatformMemory.h"

BEGIN_TRITRANIUM

/**
 * Raw data class. All allocated data passed to it must be allocated with 'PMemory::Malloc'
 */
struct PData
{
public:	
	/** Default ctor */
	PData();
	/** Copy ctor */
	PData(const PData &other);
	/** Move ctor */
	PData(PData &&other);
	/** Array ctor */
	PData(uint8 *bytes, int32 size);

	/* Dtor. Will free data */
	~PData();

	/** Copy assignment */
	PData& operator=(const PData &other);
	/** Move assignment */
	PData& operator=(PData &&other);
	
public:
	uint8* GetBytes() const
	{
		return mBytes;
	}

	uint32 GetByteSize() const
	{
		return mByteSize;
	}
	
	/**
	 * Copy the array. The old array (if any) is freed.
	 */
	void Copy(const uint8 *bytes, const uint32 size);

	/**
	 * Assign a new byte array. Will take ownership of it and will free it in the dtor.
	 * The old array (if any) is freed.
	 */
	void Assign(uint8 *bytes, const uint32 size);

	/**
	 * Free any data that we might hold
	 */
	void Free();

private:
	void Move(PData &other);

private:
	uint8* mBytes;
	uint32 mByteSize;
};

END_TRITRANIUM