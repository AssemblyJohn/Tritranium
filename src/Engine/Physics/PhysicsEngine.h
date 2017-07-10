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

#ifndef EN_PHYSICS_ENGINE_H
#define EN_PHYSICS_ENGINE_H

#include "Engine\Object\Object.h"
#include "Core\Core.h"

#include <btBulletCollisionCommon.h>
#include <LinearMath\btAlignedObjectArray.h>

class btDiscreteDynamicsWorld;
class btRigidBody;
class btCollisionShape;

/*
// PS:  Actually make this class NOT to inherit from en CLASS:
// TODO: change from inheritance to local methods so we don't have multiple inheritance here
class enPhysicsEngine : public YObject, public TRefObject
{
public:
	// CLASS_VARS()

	enPhysicsEngine() {}
	virtual ~enPhysicsEngine() {}

	void Initialize();
	void Deinitialize();

	void Step();
		
	btDiscreteDynamicsWorld *World() const;
	
	/**
	 * No body should be added during the physics step or from another thread. Call on the main thread only.
	 * NOTE: For our spacecraft to look cool we must apply forces, NOT impulses.
	 *
	 * @param shape
	 *				Shape of the body
	 * @param position
	 *				Position in the physics world
	 * @param mass
	 *				Mass of the body
	 *
	btRigidBody* AddRigidBody(btCollisionShape *shape, PVec3 &position, btScalar mass);
private:
	// Keep the collision shapes, for deletion/cleanup
	btAlignedObjectArray<btCollisionShape*>	collisionShapes;
	btBroadphaseInterface *broadphase;
	btCollisionDispatcher *dispatcher;
	btConstraintSolver *solver;
	btDefaultCollisionConfiguration *collisionConfiguration;
	// Our actual world. Most important of all
	btDiscreteDynamicsWorld *physicsWorld;
};
*/

#endif