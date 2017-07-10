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

// #include "std.h"

#include "PhysicsEngine.h"

#define TIME_STEP 0.01666666754f
#define MAX_SUBSTEPS 5

/*
// Our gravity. It is 0 since we are simulating space objects
static btVector3 gravity(0, 0, 0);

// CLASS_FUNCTIONS(enPhysicsEngine, YObject)

void enPhysicsEngine::Step()
{	
	// physicsWorld->stepSimulation(TIME_STEP);
}

void enPhysicsEngine::Initialize()
{
	// Collision configuration contains default setup for memory, collision setup
	collisionConfiguration = new btDefaultCollisionConfiguration();
	// Use the default collision dispatcher.
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	// Broadphase colision
	// Ray test, aabb test etc...
	broadphase = new btDbvtBroadphase();
	// The default constraint solver.
	solver = new btSequentialImpulseConstraintSolver();
	
	// Our world...
	physicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);	
	physicsWorld->setGravity(gravity);
}

void enPhysicsEngine::Deinitialize()
{
	// Remove the rigidbodies from the dynamics world and delete them
	int i;

	for (i = physicsWorld->getNumCollisionObjects() - 1; i >= 0 ;i--)
	{
		btCollisionObject* obj = physicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);

		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}

		physicsWorld->removeCollisionObject(obj);

		delete obj;
	}

	// Delete collision shapes
	for (i = 0; i < collisionShapes.size(); i++)
	{
		btCollisionShape* shape = collisionShapes[i];
		delete shape;
	}

	collisionShapes.clear();

	delete physicsWorld;
	delete solver;
	delete broadphase;
	delete dispatcher;
	delete collisionConfiguration;
}

btRigidBody* enPhysicsEngine::AddRigidBody(btCollisionShape *shape, PVec3 &position, btScalar mass)
{
	// First push the shape in the collision shapes so we can delete it later
	collisionShapes.push_back(shape);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	bool isDynamic = (mass != 0.0f);

	btVector3 localInertia(0, 0, 0);

	if (isDynamic)
	{
		// Calculates local inertia based on mass
		shape->calculateLocalInertia(mass, localInertia);
	}

	// Set origin
	startTransform.setOrigin(btVector3(position.x, position.y, position.z));

	btDefaultMotionState *motionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);
	
	// Create the rigid body
	btRigidBody* body = new btRigidBody(rbInfo);
	
	physicsWorld->addRigidBody(body);

	// Return a pointer to the object in case we don't want to lose the conection with that object.
	return body;
}

btDiscreteDynamicsWorld* enPhysicsEngine::World() const
{
	return physicsWorld;
}
*/