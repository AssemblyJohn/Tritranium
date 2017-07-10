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

#ifndef __TRITRANIUM_CLASS_H__
#define __TRITRANIUM_CLASS_H__

#include "Platform\Platform.h"

#include "Core\CoreLite.h"

#undef GetClassName

BEGIN_TRITRANIUM

class YClass;
class YObject;

// template <class T> class TList;

// TODO: add the checks when instantiating an object, if it contains any data that was NOT set and emmit a warning

#define YOBJECT_VARS(Clazz)					\
public:										\
	virtual const YClass &GetType() const;	\
											\
	static YObject *NewObject();			\
public:									\
	static const YClass Type;

#define YOBJECT_FUNCTIONS(Clazz, Superclass)					\
	const YClass Clazz::Type(#Clazz, #Superclass, Clazz::NewObject);	\
																\
	const YClass &Clazz::GetType() const {						\
		return (Clazz::Type);									\
	}															\
																\
	YObject *Clazz::NewObject() {								\
		return new Clazz;										\
	}

/**
 * The type of a class. Actually contains the class hierarchy.
 */
class YClass {
public:		
	YClass(const CHAR *, const CHAR *, YObject* (*NewCallback)());
	~YClass();

public: /* Utils */
	/** If this type is the subclass of another type */
	bool SubclassOf(const YClass &type) const;

	/** New instance of a object with this type */
	YObject *NewInstance() const;

public: /* Static utils */
	/**
	 * Searches for a class type by the name
	 */
	static YClass *GetClass(const CHAR *);

	/**
	 * Returns a new instance for the class found with that name
	 */
	static YObject *NewObject(const CHAR *);

public: /* Accesors */
	FORCEINLINE const CHAR *GetClassName() const
	{
		return mClassName;
	}

	FORCEINLINE const CHAR *GetSuperclassName() const
	{
		return mSuperclassName;
	}

	FORCEINLINE const TList<YClass *> &GetDerivedClasses() const
	{
		return mDerivedClasses;
	}

	FORCEINLINE const YClass *GetSuperclass() const
	{
		return mSuperclass;
	}

	FORCEINLINE YClass *GetSuperclass()
	{
		return mSuperclass;
	}

public:
	/** 
	 * Static initialize of classes that should be called only once during the program
	 * lifetime and that builds the class hierarchy.
	 */
	static void StaticInit();
private:
	// If the hierarchy was initialized
	static bool mInitialized;

private: /* Utils */
	static void ScanDerived(YClass *, TList<YClass *> *);
	static void TreeInsert(YClass *, TList<YClass *> *);

private:
	// Class name and super class name. Will be null in case this is the first object in the hierarchy.
	const CHAR *mClassName;
	const CHAR *mSuperclassName;

	// New instance callback
	YObject* (*NewCallback)();

	// Superclass in case that we are not YObject. Can be NULL
	YClass *mSuperclass;

	// List of derived objects, might be empty if nobody derives from us.
	TList<YClass*> mDerivedClasses;
};

/**
 * Base class for all engine entities. These are not entities that are required to be performance crytical but
 * the ones that are mapped to the game.
 *
 * Contains, most important, a reflection system in which we can set references at runtime. Will also contain checks that
 * we ensure that all the data is initialized and set.
 *
 * Also contains checks for instances to detect leaks an stuff.
 */
class YObject {
	YOBJECT_VARS(YObject);

public:
	virtual ~YObject();

	/** Returns the class's visible name */
	FORCEINLINE const CHAR *GetClassName() const 
	{ 
		return GetType().GetClassName(); 
	}

	/** Returns the superclasses visible name */
	FORCEINLINE const CHAR *GetSuperclassName() const 
	{ 
		return GetType().GetSuperclassName(); 
	}

	// If the object is a instance of the provided class type
	bool InstanceOf(const YClass &);

	// Friends
	friend class YClass;
	friend class Profiler;

	// TODO: see in the future, too complicated now, let's just get this working at the moment. Prefer ref counted
public:
	// We don't want any mistake initializations
	void *operator new(size_t size);
	void operator delete(void *ptr, size_t size);

private:	
	static int mInstances;
	static int mMemoryUsed;
};

END_TRITRANIUM

#endif