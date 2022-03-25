#include "FleeComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Agent.h"
#include "MoveComponent.h"
MathLibrary::Vector2 FleeComponent::calculateForce()
{
	if (!getTarget())
		return { 0,0 };

	//owners world position - targets world position
	MathLibrary::Vector2 directionToTarget = getOwner()->getTransform()->getWorldPosition()-
		getTarget()->getTransform()->getWorldPosition();

	//get the direction to the targets nomalized and scaled up by the steering force
	MathLibrary::Vector2 desriredVelocity = directionToTarget.getNormalized() * getSteeringForce();
	//gets the seek fore by desirced - agents veloicty
	MathLibrary::Vector2 seekForce = desriredVelocity - getAgent()->getMoveComponent()->getVelocity();

	return seekForce;
}
