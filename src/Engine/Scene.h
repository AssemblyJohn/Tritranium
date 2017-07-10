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

#pragma once

#include "Platform\Platform.h"

#include "Core\CoreLite.h"

#include "Engine.h"
#include "World.h"

BEGIN_TRITRANIUM

// static const TCHAR *TAG = TXT("PScene");

class PScene
{	

public:
	PScene() { }

	/**
	* @return Scene's opaque renderables
	*
	const TList<MeshRenderer *> &GetMeshes() const 
	{
		return mMeshes;
	}

	/**
	* @return Scene's sprite renderers.
	*
	const TList<SpriteRenderer *> &GetSprites() const 
	{
		return mSprites;
	}

	/**
	* @return Scene's particle generators
	*
	const TList<ParticleGenerator *> &GetParticleGenerators() const 
	{
		return mParticleSystems;
	}

	/**
	* @return Scene's particle generators and sprites
	*
	const TList<RenderableProperty *> &GetSpritesAndParticles() const
	{
		return mSpritesAndParticles;
	}

	void SetWorld(PWorld *world) {
		mWorld = world;
	}

	void SetCamera(PCamera *camera) {
		mCamera = camera;
	}

	PCamera *GetCamera() {
		return mCamera;
	}

	bool IsSpritesDirty() {
		return spritesDirty;
	}

	void CleanSprites() {
		spritesDirty = false;
	}

	// TODO: see if we can find a better wait to do this.
	void RenderTick() {
		for (int i = 0, size = mMeshes.Size(); i < size; i++) {
			mMeshes[i]->RenderTick();
		}

		for (int i = 0, size = mSprites.Size(); i < size; i++) {
			mSprites[i]->RenderTick();
		}

		for (int i = 0, size = mParticleSystems.Size(); i < size; i++) {
			mParticleSystems[i]->RenderTick();
		}
	}

	/** Clears the scene of all the objects. Does not delete them, that's the asset manager's or object owner's job. *
	void Clear() {
		// Clear 2d/3d data
		mMeshes.Clear();
		//mTranslucent.clear();
		mSprites.Clear();
		// Clear the particle system
		mParticleSystems.Clear();
	}

	void AddSpriteRenderer(SpriteRenderer *sprite) {
		mWorld->GetEngine()->CheckGame();

		mSprites.AddUnique(sprite);
		mSpritesAndParticles.AddUnique(sprite);

		spritesDirty = true;
	}

	void RemoveSpriteRenderer(SpriteRenderer *sprite) {
		mWorld->GetEngine()->CheckGame();
		
		mSprites.Erase(sprite);
		mSpritesAndParticles.Erase(sprite);

		spritesDirty = true;
	}

	void AddMeshRenderer(MeshRenderer *object) {
		mWorld->GetEngine()->CheckGame();

		mMeshes.AddUnique(object);
	}

	void RemoveMeshRenderer(MeshRenderer *object) {
		mWorld->GetEngine()->CheckGame();

		mMeshes.Erase(object);
	}

	void AddParticleGenerator(ParticleGenerator *generator) {
		mWorld->GetEngine()->CheckGame();

		mParticleSystems.AddUnique(generator);
		mSpritesAndParticles.AddUnique(generator);
	}

	void RemoveParticleGenerator(ParticleGenerator *generator) {
		mWorld->GetEngine()->CheckGame();

		mParticleSystems.Erase(generator);
		mSpritesAndParticles.Erase(generator);
	}

private:
	// Scene's owner
	PWorld *mWorld;
	// Scene's camera
	PCamera *mCamera;
	
	TList<MeshRenderer *> mMeshes;
	TList<SpriteRenderer *> mSprites;
	TList<ParticleGenerator *> mParticleSystems;
	
	TList<RenderableProperty *> mSpritesAndParticles;
	
	bool spritesDirty;
	*/
};

END_TRITRANIUM