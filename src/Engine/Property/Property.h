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

#ifndef __TRITRANIUM_PROPERTY_H__
#define __TRITRANIUM_PROPERTY_H__

#include "Platform\Platform.h"
#include "Platform\PlatformDebug.h"

#include "Engine\Object\Object.h"

#include "Core\CoreLite.h"

BEGIN_TRITRANIUM

class YGameObject;

class YProperty : public YObject 
{	
public:
	YOBJECT_VARS(YProperty);

protected:
	/** Owner of this property. If we want the owner of the property's object use mOwner.getOwner() */
	YGameObject *mOwner;

	// So we don't accidentally do bad things
	YProperty() { }

public:
	/**
	* Sets the owner of this property. Will be called before adding the property to the entity.
	*/
	void SetOwner(YGameObject *owner) {
		CHK(mOwner != NULL);
		
		mOwner = owner;
	}

private:
	// Defaults to true
	bool mActive = true;


	
public:
	YGameObject *GetOwner() {
		return mOwner;
	}

	/**
	* Any needed initialization. When it is called the owner has been set.
	* It is called when the property is constructed and before it has been added to the owner property list.
	*/
	void Initialize() { }

	/**
	* Any needed deinitialization.
	* It is called before removing from the world and before destroying the object.
	*/
	void Deinitialize() { }

	/** If the property is active */
	bool IsActive() {
		return mActive;
	}

	/** If the property is visible */
	void SetActive(bool active) {
		mActive = active;
	}

	/** Called if the property implements the {@link ITickable} interface */
	void Tick() { }

	/** Called if the prop implements {@link ITickable} */
	void LateTick() { }

	/*	
	public String toString() {
		return "Property{" +
			"owner=" + owner.getTag() +
			", type=" + this.getClass().getSimpleName() +
			", active=" + active +
			'}';
	} */
};



/*
class enGame;
class enEntity;

// TODO: add some default variables, like 'camera', 'owner', 'transform', 'physics'
class enComponent : public YObject
{
public:
	CLASS_VARS()

	enComponent();
	enComponent(const PString &);

	virtual void Initialize() {};
	virtual void Step() {};

	void SetEntity(enEntity *);
	const enEntity *GetEntity() const;

	void SetGame(enGame *);
	const enGame *GetGame() const;

	const bool IsActive() const;
	void SetActive(bool);

	void SetName(PString &);
	const PString &GetName() const;
protected:
	enGame *game;
	enEntity *owner;
private:
	PString name;
	bool active;	
};

*/

END_TRITRANIUM

#endif