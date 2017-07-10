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

#include "GameObject.h"

#include "Platform\PlatformAssertion.h"
#include "Platform\PlatformLog.h"

#include "Engine\Property\Property.h"
#include "Engine\Property\Renderable.h"

#include "Engine\Engine.h"
#include "Engine\World.h"

// Got it from somwhere, useless don't need, TODO: see at final compile if we can get rid of it somehow without undefining it here....
#undef GetClassName

BEGIN_TRITRANIUM

// static const TCHAR *TAG = TXT("YGAME_OBJECT");

/*
YGameObject::YGameObject(PEngine *engine, uint32 tag, const PString &name)  : 
	mEngine(engine),
	mTag(tag),
	mName(name)
{
	
	/*
	engine->checkGame();

	if (DEBUG) {
	Log.d(TAG, "New instance of game object. Instances: " + engine.mDebugInstances.incrementAndGet());
	}
	
}*/

YOBJECT_FUNCTIONS(YGameObject, YObject);

PWorld *YGameObject::GetWorld()
{
	return mEngine->GetWorld();
}

/**
* Mark the entity as active for tick. Note that the active state
* will be sent down the hierarchy to the owned objects.
*/
void YGameObject::SetActive(bool active) 
{
	mActive = active;
	
	for (int i = 0, size = mProperties.Size(); i < size; i++) 
		mProperties[i]->SetActive(active);

	for (int i = 0, size = mOwnedObjects.Size(); i < size; i++) 
		mOwnedObjects[i]->SetActive(active);
}


YProperty *YGameObject::GetPropertyOfType(const YClass &type)
{
	for (int i = 0, size = mProperties.Size(); i < size; i++)
	{
		if (mProperties[i]->InstanceOf(type))
			return mProperties[i];
	}

	return NULL;
}

void YGameObject::GetPropertiesOfType(const YClass &type, TList<YProperty *> &outProperties) 
{	
	for (int i = 0, size = mProperties.Size(); i < size; i++) 
	{		
		if (mProperties[i]->InstanceOf(type))
			outProperties.Add(mProperties[i]);
	}
}

bool YGameObject::HasPropertyOfType(const YClass &type)
{
	for (int i = 0, size = mProperties.Size(); i < size; i++) 
	{
		if (mProperties[i]->InstanceOf(type)) 
			return true;
	}

	return false;
}

template<class T>
bool YGameObject::HasPropertyOfType()
{
	return HasPropertyOfType(T::Type);
}

bool YGameObject::IsRenderable()
{	
	return HasPropertyOfType(YRenderable::Type);
}

void YGameObject::GetRenderableData(TList<YRenderable *> &outRenderables)
{
	GetPropertiesOfType<YRenderable *>(YRenderable::Type, outRenderables);
}

YProperty *YGameObject::AddProperty(YProperty *property)
{
	CheckProperty(property);

	CHK(property->GetOwner() == NULL);

	property->SetOwner(this);
	property->Initialize();

	// Add the property to the list of properties
	mProperties.AddUnique(property);		

	// TODO:

	// Scene sync
	if (property->InstanceOf(YRenderable::Type))
	{
		// mEngine->GetWorld()->UpdatePropertyAdd((YRenderable *)property);		

		LogDebug(TXT("Synced scene for prop: %s"), property->GetClassName());
	}
	
	LogDebug(TXT("Added new property of type: %s"), property->GetClassName());

	return property;
}

YProperty *YGameObject::AddProperty(const YClass &type)
{
	CHK(type.SubclassOf(YProperty::Type));

	AddProperty((YProperty *)type.NewInstance());

	// TODO:
	return nullptr;
}

void YGameObject::RemoveProperty(YProperty *property)
{
	if (mProperties.Erase(property))
	{
		property->Deinitialize();
		property->SetOwner(NULL);
		
		// Scene sync
		if (property->InstanceOf(YRenderable::Type)) 
		{
			// TODO:
			// mEngine->GetWorld()->UpdatePropertyRemove((YRenderable *)property);
		}

		LogDebug(TXT("Removed property of type: %s and synced scene!"), property->GetClassName());

		// TODO: see here how we can smartly do this... mental blockage with this delete, mental blockage
		LogDebug("Don't forget to move from 'delete' to some sort of 'release'.");
		delete property;
	}
	else
	{
		LogDebug(TXT("Tried to remove inexistent property: %s from object %s"), property->GetClassName(), mName.c_str());
	}
}

void YGameObject::RemoveProperties(const YClass &type)
{
	if (HasPropertyOfType(type)) 
	{
		TList<YProperty *> props;

		GetPropertiesOfType(type, props);

		for (int i = 0, size = props.Size(); i < size; i++) 
			RemoveProperty(props[i]);

		// Don't access properties again, they're dangling!
	}
	else 
	{
		LogDebug(TXT("Object: %s has no properties of type: %s"), mName.c_str(), type.GetClassName());
	}
}


void YGameObject::SetOwner(YGameObject *owner) 
{
	CHK(owner != NULL);
	CHK(this != owner);

	// Check if the object to which we want to be a owned entity of is NOT a entity owned by us
	// a.k.a check that the object is not of lower hierarchy than us	
	#ifdef TRITRANIUM_DEBUG
		YGameObject *ownersOwner = owner->GetOwner();

		while (ownersOwner != NULL) 
		{
			LogDebug(TXT("Setting owner to: %d is wrong since we own that object"), owner->GetName());
			CHK(ownersOwner != this);

			// Move up the hierarchy
			ownersOwner = ownersOwner->GetOwner();
		}
	#endif

	LogDebug(TXT("Setting new owner for object: %s owner: %s"), this->GetClassName(), owner->GetClassName());

	if (mOwner != NULL) 
	{
		// If we already have an owner

		// First remove this from the list of the object's owned entities. If this happends it's bad, we done something very wrong.
		#ifdef TRITRANIUM_DEBUG
		LogDebug("Integrity broken, this: %s not contained in the owner's list: %s", GetName().c_str(), mOwner->GetName().c_str());
		CHK(mOwner->mOwnedObjects.Contains(this) == true);
		#endif

		// Remove this
		mOwner->mOwnedObjects.Erase(this);
	}

	// Set the new owner
	mOwner = owner;

	#ifdef TRITRANIUM_DEBUG
		// Check that we are not already contained there
		// Log.e(TAG, "Integrity broken, this: " + this + " already contained in the onwer's list: " + owner);
		CHK(mOwner->mOwnedObjects.Contains(this) == false);

		// Check that the owner is not added to out list of owned entities
		LogDebug("Integrity broken, owner is contained in our list of owned entities. owner: " + mOwner->GetName());
		CHK(mOwnedObjects.Contains(mOwner) == false);
	#endif

	// Add this to the owner's list of owned entities
	mOwner->mOwnedObjects.AddUnique(this);
}


void YGameObject::DispatchTick()
{
	if (mProperties.IsEmpty() == false)
	{
		for (int i = 0, size = mProperties.Size(); i < size; i++)
		{
			YProperty *tickable = mProperties[i];

			if (tickable->IsActive())
				tickable->Tick();
		}
	}
}

void YGameObject::DispatchOnResume() 
{
	CHK(0);

	/*
	if (hasPropertiesOfType(Script.class)) {
		List<Script> scripts = getPropertiesOfType(Script.class);

		for (int i = 0, size = scripts.size(); i < size; i++) {
			Script script = scripts.get(i);

			if (script.isActive()) {
				script.onResume();
			}
		}
	}
	*/
}

void YGameObject::DispatchOnPause() 
{
	CHK(0);

	/*
	if (hasPropertiesOfType(Script.class)) {
		List<Script> scripts = getPropertiesOfType(Script.class);

		for (int i = 0, size = scripts.size(); i < size; i++) {
			Script script = scripts.get(i);

			if (script.isActive()) {
				script.onPause();
			}
		}
	}
	*/
}

END_TRITRANIUM