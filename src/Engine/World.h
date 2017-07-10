#pragma once

#include "Platform\Platform.h"
#include "Core\CoreLite.h"

BEGIN_TRITRANIUM

// static const TCHAR *TAG = TXT("PWORLD");

// template <class T> class TList;
// template <typename> class TList;

class PEngine;
class PScene;
class PCamera;
class YGameObject;

// class SCYGameObject;

// typedef TVector<SCYGameObject> ObjectList;

/**
 * World that contains all the entitites and ticks them. Has exclusive owning rights
 * so no cached pointers to objects!
 *
 * 
 */
class PWorld
{
public: /* Ctor, dtor and initialize */
	PWorld();
	~PWorld();

	void Init(PEngine *engine);

public: /* Accesors */
	PScene *GetScene() 
	{
		return mScene;
	}

	PCamera *GetCamera() 
	{
		return mCamera;
	}

	PEngine *GetEngine() 
	{
		return mEngine;
	}

public: /* Ticking */

	/** Begin tick, called before the world tick */
	void BeginTick();

	/** World tick. */
	void TickWorld();
	
	/** Finish tick, called after the world tick */
	void FinishTick();

	/** Post the render tick, dispatched to the scene */
	void RenderTick();

public: /* Lifetime */
	/** Called before the engine is paused so objects can take action */
	void OnPause();
	/** Called after the engine is resumed so objects can take action */
	void OnResume();

public: /* Entity add and remove */

	// TODO: modify add/remove so that we know of the hierarchy
	/**
	 * Do not use from the exterior! Use the GameObject instantiate, destroy methods!
	 *
	 * Adds an entity to the world. It will NOT add the owned entities of this object! the world knows nothing of that,
	 * that is the object's business.
	 *
	 * This method will also update the scene with the renderable properties of the object.
	 *
	 * Will delay the scene add after the tick. In that way we can cleanly iterate without problems.
	 *
	 * @param entity
	 *              Entity to add to the world.
	 */
	void AddEntityToWorld(YGameObject *entity);

	/**
	 * Do not use from the exterior! Use the GameObject instantiate, destroy methods!
	 *
	 * Removes the entity from the world. It will NOT remove the owned entities of this object! The world knows nothing
	 * of that, it's the object's job to take care of the hierarchy.
	 *
	 * This method will also remove the renderable properties of this entitie's and it's owned objects.
	 *
	 * Will delay the scene remove after we tick. In that way we can cleanly iterate over them.
	 *
	 * @param entity
	 *              Entity to remove from the world.
	 */
	void RemoveEntityFromWorld(YGameObject *entity);

	/**
	* Do not use from the exterior! When a property is added to an object
	* it is automatically synced with the scene!
	*
	* Updates the scene for an added renderable property.
	*/
	// void UpdatePropertyAdd(YRenderable *property);

	/**
	* Do not use from the exterior! When a property is added to an object
	* it is automatically synced with the scene!
	*
	* Updates the scene for an removed renderable property.
	*/
	// void UpdatePropertyRemove(YRenderable *property);


public: /* Entity query */
	/**
	 * Returns a list of entities with the specified tag or an empty list if no such entities exist.
	 * The entities can contain more owned entities.
	 */
	uint32 GetEntitiesWithTag(uint32 &tag, TList<YGameObject *> &out);

	/**
	 * Returns the first entity in the list that has the provided tag or null if no such entity exists.
	 * The entity can contain many owned entities.
	 */
	YGameObject *GetEntityWithTag(uint32 &tag);

public: /* Clear */

	/**
	 * Clears the world of all the current data. Used when level switching.
	 */
	void ClearWorld();

	/**
	 * Clears the world from all the data for exit.
	 */
	void ClearWorldExit();

private: /* Private updates */

	void InnerAddToWorld(YGameObject *entity);
	void InnerRemoveFromWorld(YGameObject *entity);
	
	/**
	 * Adds to the scene all the object's renderable properties.
	 */
	void UpdateSceneAdd(YGameObject *entity);

	/**
	 * Removes from the scene all the object's renderable properties.
	 */
	void UpdateSceneRemove(YGameObject *entity);

private: /** Core data */
	// Engine owner
	PEngine *mEngine;
	PScene *mScene;

	// Default camera
	PCamera *mCamera;

	// TVector<SCYGameObject> mGameObjects;

	// Game entities
	TList<YGameObject*> mEntities;
	// Pending remove
	TList<YGameObject*> mPendingRemove;
};

/*
	public StringBuilder completeData() {
		StringBuilder builder = new StringBuilder();

		for (GameObject entity : mEntities) {
		builder.append("[Entity: (" + entity + ")]\n");

		for (Property prop : entity.getProperties()) {
		builder.append("\t\t Property: (" + prop + ")\n");
		}

		builder.append("\n\n");
		}

		return builder;
	}
*/

END_TRITRANIUM