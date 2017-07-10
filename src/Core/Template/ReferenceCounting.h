/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef __TRI_REFERENCE_COUNTING_H__
#define __TRI_REFERENCE_COUNTING_H__

#include "Platform\Platform.h"
#include "Platform\PlatformAssertion.h"

BEGIN_TRITRANIUM

/** Simple reference counted object. */
class TRefObject
{
public:
	TRefObject() : references(0) {}
	~TRefObject() { CHK(references == 0); }

	uint32 Retain() const
	{
		return (++references);
	}

	uint32 Release() const
	{
		references--;
		if (references == 0)
		{
			delete this;
		}

		return references;
	}

	uint32 GetReferenceCount() const
	{
		return references;
	}

private:
	mutable uint32 references;
};

/** Simple pointer to reference counted objects. */
template<class T>
class TRefPtr
{
public:
	TRefPtr() : reference(NULL) {}
	TRefPtr(T *ptr, bool initRef = true)
	{
		CHK(ptr);

		reference = ptr;
		if (initRef)
			reference->Retain();
	}
	TRefPtr(TRefPtr &other)
	{
		reference = other.reference;
		reference->Retain();
	}

	~TRefPtr() 
	{
		reference->Release();
	}

	TRefPtr &operator=(T *ptr)
	{
		// Old ref so we can release
		T *old = reference;

		// Build new reference
		reference = ptr;
		reference->Retain();

		// In case we used the default no-arg constructor the old ref might be null
		if (old)
		{
			old->Release();
		}

		return *this;
	}

	// Carefull, we just set the reference, we are not releasing anything
	TRefPtr &operator=(const TRefPtr &other)
	{
		reference = other.reference;
		return *this;
	}

	T *operator->() const
	{
		return reference;
	}

	operator T*() const
	{
		return reference;
	}

	void Release()
	{
		reference->Release();
	}

	uint32 GetReferenceCount() const
	{
		return reference->GetReferenceCount();
	}

	T *GetReference()
	{
		return reference;
	}
private:
	T *reference;
};

END_TRITRANIUM

#endif