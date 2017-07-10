/**
* Copyright (c) 2015 Lazu Ioan-Bogdan
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, without any restrictions.
*/

#include "Object.h"

#include "Platform\PlatformMemory.h"
#include "Platform\PlatformAssertion.h"
#include "Platform\PlatformLog.h"

#include "Core\CoreLite.h"

BEGIN_TRITRANIUM

#define TAG TXT("YCLASS")

// Global data
static YClass *g_head = NULL;
static TList<YClass *> *g_types = NULL;
static TMap<::std::string, YClass*> *g_typesMap = NULL;

// We are not initialized
bool YClass::mInitialized = false;

YClass::YClass(const CHAR *classname, const CHAR *superclassname, YObject* (*NewCallback)())
{
	// Data
	this->NewCallback = NewCallback;
	this->mClassName = classname;
	this->mSuperclassName = superclassname;
		
	// Add to the global types
	if (g_types == NULL)
		g_types = new TList<YClass *>();

	if (g_typesMap == NULL)
		g_typesMap = new TMap<::std::string, YClass*>();

	g_types->Add(this);
	g_typesMap->Put(::std::string(classname), this);
}

YClass::~YClass()
{ }

void YClass::StaticInit()
{
	CHK(mInitialized == false);

	TList<YClass *> types = (*g_types);

	// Scan for the base class
	for (uint32 i = 0; i < types.Size(); i++)
	{
		if ((StrCmp(types[i]->mClassName, "YObject") == 0))
		{
			// We got our list's head
			g_head = types[i];
			types.Erase(i);

			break;
		}
	}

	CHK(g_head != NULL);

	// If we are stuck in here it means that the hierarchy is broken somwhere
	while (types.Size() > 0)
	{
		TreeInsert(g_head, &types);

		// If it's stuck to something != 0 it's bad
		LogVerbose(TXT("Global types count: %d"), types.Size());
	}

	// We are initialized now
	mInitialized = true;
}

void YClass::TreeInsert(YClass *base, TList<YClass *> *derived)
{
	// Do operation
	ScanDerived(base, derived);				

	for (uint32 i = 0; i < base->GetDerivedClasses().Size(); i++)
	{
		TreeInsert(base->GetDerivedClasses().Get(i), derived);
	}
	
}

/**
 * Scans for the classes derrived from the provided base class.
 * The received derived list it only a list of possibilites.
 */
void YClass::ScanDerived(YClass *base, TList<YClass *> *derived)
{
	for (int i = (derived->Size() - 1); i >= 0; i--)
	{
		if (StrCmp(base->GetClassName(), derived->Get(i)->GetSuperclassName()) == 0)
		{
			derived->Get(i)->mSuperclass = base;
			base->mDerivedClasses.Add(derived->Get(i));

			derived->Erase(i);
		}
	}
}

bool YClass::SubclassOf(const YClass &type) const
{
	const YClass *clz = this;

	while (clz)
	{
		if (StrCmp(clz->GetClassName(), type.GetClassName()) == 0)
			return true;

		// Move up in the hierarchy
		clz = clz->GetSuperclass();
	}

	return false;
}

YClass *YClass::GetClass(const CHAR *clazz)
{
	CHK(YClass::mInitialized);

	if (g_typesMap->Contains(::std::string(clazz)))
	{
		// TODO: see here with the [] operator, gotta get it working
		return g_typesMap->Get(::std::string(clazz));
	}

	return NULL;
}

YObject *YClass::NewObject(const CHAR *clazz)
{
	CHK(YClass::mInitialized);

	// Look for the class type and invoke it's new callback
	YClass *type = GetClass(clazz);

	if (type != NULL)
		return type->NewCallback();

	return NULL;
}

YObject *YClass::NewInstance() const
{
	CHK(YClass::mInitialized);

	return NewCallback();
}

/*
 * End YClass
 */


/*
 * Begin YObject
 */

// TODO: move this in a profiler
// Statics
int YObject::mInstances = 0;
int YObject::mMemoryUsed = 0;

YOBJECT_FUNCTIONS(YObject, NULL)

YObject::~YObject() 
{ }

bool YObject::InstanceOf(const YClass &type)
{	
	const YClass *clz = &GetType();

	while (clz)
	{
		if (StrCmp(clz->GetClassName(), type.GetClassName()) == 0)
			return true;

		// Move up in the hierarchy
		clz = clz->GetSuperclass();
	}

	return false;
}

void *YObject::operator new(size_t size)
{
	void *ptr = PMemory::Malloc(size);

	mMemoryUsed += size;
	mInstances++;

	return ptr;
}

void YObject::operator delete(void *ptr, size_t size) 
{
	if (ptr)
	{
		PMemory::Free(ptr);

		mMemoryUsed -= size;
		mInstances--;
	}
}

END_TRITRANIUM

/*
 * End YObject
 */