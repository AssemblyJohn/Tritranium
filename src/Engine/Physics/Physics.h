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

#ifndef EN_PHYSICS_H
#define EN_PHYSICS_H

#include "Engine\Property\Property.h"

/*

class btRigidBody;
struct PVec3;

/**
 * Physics body component. 
 *
 * Steps for adding a physics component to the game:
 * I.	add the collision shape to the game's physics world
 * II.	get the btRigidBody, set it to this component 
 * III.	attatch the component to an entity 
 * IV.	add the entity to the scene.
 
class enPhysics : public enComponent
{
public:
	CLASS_VARS()

	enPhysics();
	~enPhysics();

	virtual void Step();
	void Body(btRigidBody *);

	// Physics functions
	void ApplyCentralForce(const PVec3 &force);
	void ApplyTorque(const PVec3 &torque);
	PVec3 GetAngularVelocity();
	void SetAngularVelocity(const PVec3 &velocity);
	PVec3 GetPosition();

	void GetRotation(enScalar &yaw, enScalar &pitch, enScalar &roll);
	void SetRotation(enScalar yaw, enScalar pitch, enScalar roll);
private:
	btRigidBody *body;
};

*/

#endif