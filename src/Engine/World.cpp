#include "World.h"

// Utils
#include "Core\CoreLite.h"

// Game entities
#include "Engine\Object\GameObject.h"
#include "Scene.h"

BEGIN_TRITRANIUM

PWorld::PWorld() 
{
	// Allocate scene
	mScene = new PScene();

	// Set the scene's world to 'this'
	// mScene.setWorld(this);

	// Create the camera
	// mCamera = new PCamera();

	// Set the scene's camera
	// mScene.setCamera(mCamera);
}

PWorld::~PWorld()
{

}

void PWorld::Init(PEngine *engine) 
{
	mEngine = engine;

	// Initialize the camera
	// mCamera->init(engine);

	// Add cam to the scene
	// mEntities.add(mCamera.getObject());
	// mEntities->Add()
}

void PWorld::TickWorld() 
{
	YGameObject *entity;

	// TODO: test cast stand alone

	for (int i = 0, size = mEntities.Size(); i < size; i++) {
		entity = mEntities[i];

		if (entity->IsActive()) {
			entity->DispatchTick();
		}
	}

	for (int i = 0, size = mEntities.Size(); i < size; i++) {
		entity = mEntities[i];

		if (entity->IsActive()) {
			// entity->DispatchLateTick();
		}
	}
}

/** Post the render tick, dispatched to the scene */
void PWorld::RenderTick() 
{
	// mScene->RenderTick();
}

void PWorld::BeginTick() 
{

}

void PWorld::FinishTick() 
{	
	// Delay all object destroys and creates after the tick.
	if (mPendingRemove.Size() > 0) {
		for (int i = 0, size = mPendingRemove.Size(); i < size; i++) {
			InnerRemoveFromWorld(mPendingRemove[i]);
		}

		mPendingRemove.Clear();
	}	
}

void PWorld::OnPause() 
{
	YGameObject *entity;

	// TODO:

	// On the asset loaded someone can remove an asset from the world. Pass in reverse order.
	for (int i = mEntities.Size() - 1; i >= 0; i--) 
	{
		entity = mEntities[i];

		if (entity->IsActive()) 
		{
			entity->DispatchOnPause();
		}
	}
}

void PWorld::OnResume() 
{
	YGameObject *entity;

	// TODO:

	// On the asset loaded someone can remove an asset from the world. Pass in reverse order.
	for (int i = mEntities.Size() - 1; i >= 0; i--) 
	{
		entity = mEntities[i];

		if (entity->IsActive()) 
		{
			entity->DispatchOnResume();
		}
	}
}

/**
* Returns a list of entities with the specified tag or an empty list if no such entities exist.
* The entities can contain more owned entities.
*/
uint32 PWorld::GetEntitiesWithTag(uint32 &tag, TList<YGameObject *> &out) 
{
	// mEngine.checkGame();	
	uint32 added = 0;

	for (int i = 0, size = mEntities.Size(); i < size; i++) 
	{
		YGameObject *gameObject = mEntities[i];

		if (tag == gameObject->GetTag()) 
		{
			out.Add(gameObject);

			added++;
		}
	}

	return added;
}

/**
* Returns the first entity in the list that has the provided tag or null if no such entity exists.
* The entity can contain more owned entities.
*/
YGameObject *PWorld::GetEntityWithTag(uint32 &tag)
{
	// mEngine.checkGame();	

	YGameObject *gameObject;

	for (int i = 0, size = mEntities.Size(); i < size; i++) 
	{
		gameObject = mEntities[i];

		if (tag == gameObject->GetTag()) 
		{
			return gameObject;
		}
	}

	return NULL;
}

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
void PWorld::AddEntityToWorld(YGameObject *entity)
{
	// mEngine.checkGame();

	InnerAddToWorld(entity);
}

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
void PWorld::RemoveEntityFromWorld(YGameObject *entity) {
	// mEngine.checkGame();

	mPendingRemove.AddUnique(entity);
}

/**
 * Do not use from the exterior! When a property is added to an object
 * it is automatically synced with the scene!
 *
 * Updates the scene for an added renderable property.
 *
void PWorld::UpdatePropertyAdd(RenderableProperty property) {
	if (property instanceof MeshRenderer) {
		mScene.addMeshRenderer((MeshRenderer)property);
	}
	else if (property instanceof SpriteRenderer) {
		mScene.addSpriteRenderer((SpriteRenderer)property);
	}
	else if (property instanceof ParticleGenerator) {
		mScene.addParticleGenerator((ParticleGenerator)property);
	}
	else {
		Log.e(TAG, "Forgot to add property type: " + property.getClass().getSimpleName());
	}
}

/**
* Do not use from the exterior! When a property is added to an object
* it is automatically synced with the scene!
*
* Updates the scene for an removed renderable property.
*
void PWorld::UpdatePropertyRemove(RenderableProperty property) {
	if (property instanceof MeshRenderer) {
		mScene.removeMeshRenderer((MeshRenderer)property);
	}
	else if (property instanceof SpriteRenderer) {
		mScene.removeSpriteRenderer((SpriteRenderer)property);
	}
	else if (property instanceof ParticleGenerator) {
		mScene.removeParticleGenerator((ParticleGenerator)property);
	}
	else {
		Log.e(TAG, "Forgot to add property type: " + property.getClass().getSimpleName());
	}
}
*/

/**
 * Clears the world of all the current data
 */
void PWorld::ClearWorld() 
{
	// Remove the entities
	mEntities.Clear();

	// Add the camera again
	// mEntities.add(mCamera.getObject());
}

void PWorld::ClearWorldExit() 
{
	// Null all
	mEngine = NULL;
	mScene = NULL;
	mCamera = NULL;

	// Empty everything
	mEntities.Clear();
}

void PWorld::InnerAddToWorld(YGameObject *entity) 
{
	// Add entity
	mEntities.AddUnique(entity);

	// Update scene with the entities's properties
	UpdateSceneAdd(entity);
}

void PWorld::InnerRemoveFromWorld(YGameObject *entity) 
{
	// Erase entity	
	mEntities.Erase(entity);

	// Remove scene's data
	UpdateSceneRemove(entity);
}

/**
* Adds to the scene all the object's renderable properties.
*/
void PWorld::UpdateSceneAdd(YGameObject *entity) 
{
	/*
	if (entity.isRenderable()) {
		for (RenderableProperty prop : entity.getRenderableData()) {
			updatePropertyAdd(prop);
		}
	}
	*/
}

/**
* Removes from the scene all the object's renderable properties.
*/
void PWorld::UpdateSceneRemove(YGameObject *entity) 
{
	/*
	if (entity.isRenderable()) {
		for (RenderableProperty prop : entity.getRenderableData()) {
			updatePropertyRemove(prop);
		}
	}
	*/
}

END_TRITRANIUM