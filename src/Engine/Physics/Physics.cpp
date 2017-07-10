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

#include "Physics.h"

// #include "std.h"

/*

CLASS_FUNCTIONS(enPhysics, enComponent)

enPhysics::enPhysics()
{
	body = NULL;
}

enPhysics::~enPhysics()
{
	if (body) 
		delete body;
}

void enPhysics::Body(btRigidBody *body)
{
	this->body = body;
}

void enPhysics::ApplyTorque(const PVec3 &torque)
{
	body->applyTorque(btVector3(torque.x, torque.y, torque.z));	
}

void enPhysics::ApplyCentralForce(const PVec3 &force)
{
	body->applyCentralForce(btVector3(force.x, force.y, force.z));	
}

PVec3 enPhysics::GetAngularVelocity()
{
	return PVec3(body->getAngularVelocity().m_floats);
}
void enPhysics::SetAngularVelocity(const PVec3 &velocity)
{
	body->setAngularVelocity(btVector3(velocity.x, velocity.y, velocity.z));	
}

PVec3 enPhysics::GetPosition()
{
	return PVec3(body->getCenterOfMassPosition().m_floats);
}

void enPhysics::GetRotation(enScalar &yaw, enScalar &pitch, enScalar &roll)
{
	body->getCenterOfMassTransform().getBasis().getEulerYPR(yaw, pitch, roll);
}

void enPhysics::SetRotation(enScalar yaw, enScalar pitch, enScalar roll)
{
	//body->getWorldTransform().getRotation().setEuler(DEG2RAD(yaw), DEG2RAD(pitch), DEG2RAD(roll));

	body->getWorldTransform().setRotation(btQuaternion(PScalar::DegToRad(yaw), PScalar::DegToRad(pitch), PScalar::DegToRad(roll)));

	/*
	// get thransform
	btTransform trans = body->getWorldTransform();
	// create a quaternion
	btQuaternion quat;
	// set the quaternion's angle
	quat.setEuler(DEG2RAD(yaw), DEG2RAD(pitch), DEG2RAD(roll));
	// set the translation to the quaternion
	trans.setRotation(quat);
	// update the world transform
	body->setWorldTransform(trans);
	
}

void enPhysics::Step()
{
	enTransform &transform = owner->Transform();
	
	// Set position
	btVector3 v = body->getCenterOfMassPosition();
	transform.position.Set(v.x(), v.y(), v.z());
	
	// Set rotation
	btQuaternion rot = body->getCenterOfMassTransform().getRotation();
	transform.rotation.angle = PScalar::RadToDeg(rot.getAngle());
	transform.rotation.axis.Set(rot.getAxis().x(), rot.getAxis().y(), rot.getAxis().z());
}

*/