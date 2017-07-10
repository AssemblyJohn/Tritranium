/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef __Y_GAME_OBJECT__
#define __Y_GAME_OBJECT__

#include "Platform\Platform.h"
#include "Core\CoreLite.h"

#include "Engine\Property\Transform.h"
#include "Object.h"

#include <EASTL\shared_ptr.h>

BEGIN_TRITRANIUM

class PEngine;
class PWorld;

class YRenderable;
class YProperty;

enum GAME_OBJECT_TAGS
{
	NO_TAG = 0,

	GAME_CONTROLLER = 1,
	PLAYER = 2,
	ENEMY = 3
};

class YGameObject : public YObject 
{
public:
	// The transform will never be null, it's standard.
	PTransform transform;

	YOBJECT_VARS(YGameObject);

public:	
	// YGameObject(PEngine *engine, uint32 tag = GAME_OBJECT_TAGS::NO_TAG, const PString &name = "");
	YGameObject() { }

	virtual void Init(PEngine *engine)
	{
		CHK(engine != NULL);
		mEngine = engine;
	}

public: /* Simple getters and setters */

	const PTransform &GetTransform() const
	{
		return transform;
	}

	PTransform &GetTransform()
	{
		return transform;
	}

	/** @return Entity's tag */
	const uint32 GetTag() const
	{
		return mTag;
	}

	/** Set the entity's tag. */
	void SetTag(uint32 tag) 
	{
		this->mTag = tag;
	}

	const PString &GetName() const
	{
		return mName;
	}

	void SetName(const PString &name)
	{
		mName = name;
	}

	void SetName(PString &&name)
	{
		mName = name;
	}

	/** Owner of this object. Can be NULL. */
	YGameObject *GetOwner()
	{
		return mOwner;
	}

	/** @return	Owned entities. Can be empty. Do not modify! */
	TList<YGameObject *> &GetOwnedEntities()
	{
		return mOwnedObjects;
	}

	/**
	 * @return	The list of the properties owned by this entity. Do not modify!
	 */
	TList<YProperty *> &GetProperties()
	{
		return mProperties;
	}

	PWorld *GetWorld();

	PEngine *GetEngine() { return mEngine; }

public: /* State */
	/**
	 * Mark the entity as active for tick. Note that the active state
	 * will be sent down the hierarchy to the owned objects.
	 */
	void SetActive(bool active);

	/** If the entity is active */
	bool IsActive() 
	{
		return mActive;
	}   

public: /* Property retrieval and set */
	/** Returns the first property of the specified type or null if no property of that type could be found. */
	YProperty *GetPropertyOfType(const YClass &type);

	template<class T> 
	FORCEINLINE T *GetPropertyOfType(const YClass &type)
	{
		return (T)GetPropertyOfType(type);
	}

	/** Returns all the properties of a certain type in this object. */
	void GetPropertiesOfType(const YClass &type, TList<YProperty *> &outProperties);

	template<class T>
	FORCEINLINE void GetPropertiesOfType(const YClass &type, TList<T> &outProperties)
	{


		// GetPropertiesOfType(type, (TList<YProperty *>)outProperties);
	}

	/** IF the object has a property of a certain type. */
	bool HasPropertyOfType(const YClass &type);

	template<class T>
	bool HasPropertyOfType();

	/** If this entity has a property that will be drawn */
	bool IsRenderable();

	/** Get the renderable data if we have such */
	void GetRenderableData(TList<YRenderable *> &outRenderables);

	/**
	* Adds a property of a type to the game object.
	*
	* It has it's owner set and it is initialized. Will also sync with the scene if this property is renderable.
	*/
	YProperty *AddProperty(YProperty *property);

	/** Same as above but with a type instead of a instance */
	YProperty *AddProperty(const YClass &type);

	/**
	 * Removes a property from the game object.
	 */
	void RemoveProperty(YProperty *property);

	/**
	 * Removes all the properties of the specified type from this object.
	 *
	 * It is deinitialized and it's owned removed. Will also sync with the
	 * scene if this property is renderable.
	 */
	void RemoveProperties(const YClass &type);

public: /* Hierarchy managing */

	/**
	* Sets the owner of this object. By doing so the following operations take place:
	*
	* - check if the object is equal to 'this' case in which we throw
	*
	* - check that the owner is not a owned entity in any of our owned entities
	*
	* - if the object already has an owner
	*      - remove this from the owner's list of owned entities. Integrity check, to make sure we were the object's entity.
	* - if the object does not already have an owner
	*      - no action is required if we don't have an owner
	*
	* - add the object to the new owner's list of objects. Check that we are not already there somehow
	*
	* @param owner	Game object that will own this entity
	*/
	void SetOwner(YGameObject *owner);

public: /* Begin script and tickables callbacks */

	/**
	* Ticks all the tickables of this game entity.
	* It's final. If the behaviour should change attach a script.
	* It will also tick the owned objects if they are active.
	*
	* This tick will not be called if this entity is not active!
	* Neither the ticks for the owned objects will not be called!
	*/
	void DispatchTick();

	void DispatchOnResume();

	void DispatchOnPause();

	/*
	void dispatchOnAssetsLoaded(AssetMap<String, Asset> assets, int identifier) {
		if (hasPropertiesOfType(Script.class)) {
			List<Script> scripts = getPropertiesOfType(Script.class);

			for (int i = 0, size = scripts.size(); i < size; i++) {
				Script script = scripts.get(i);

				if (script.isActive()) {
					script.onAssetsLoaded(assets, identifier);
				}
			}
		}
	}
	*/

private: /** Inner utils */
	void CheckProperty(YProperty *property) { }

	void InnerInit(PEngine *engine, uint32 tag, const PString &name) { }
	void InnerClean() { }

private: /* Retrieval data */
	PString mName;
	uint32 mTag;

private: /* Hierarchy data */
	// Owner. It it is null it is part of the root objects.
	YGameObject *mOwner = NULL;
	// Owned objects.
	TList<YGameObject *> mOwnedObjects;

private: /* Property data */	
	TList<YProperty *> mProperties;

private: /* Misc */
	// Owner engine
	PEngine *mEngine;

private: /* State */
	bool mActive;
};

typedef YGameObject* CYGameObject;
typedef eastl::shared_ptr<CYGameObject> SCYGameObject;

END_TRITRANIUM

#endif