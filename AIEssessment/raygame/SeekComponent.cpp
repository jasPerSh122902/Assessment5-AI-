#include "SeekComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Agent.h"
#include "MoveComponent.h"

/// <summary>
/// Caluclates the force from the target and the agent
/// </summary>
/// <returns></returns>
MathLibrary::Vector2 SeekComponent::calculateForce()
{
	if (!getTarget())
		return { 0,0 };
	//get the direction form the target and the owner
	MathLibrary::Vector2 directionToTarget = getTarget()->getTransform()->getWorldPosition()
		- getOwner()->getTransform()->getWorldPosition();
	//a normalized direction to the target scaled by the steering force3
	MathLibrary::Vector2 desriredVelocity = directionToTarget.getNormalized() * getSteeringForce();
	//makes the seekforce the desirced velocity -  the agents velocity
	MathLibrary::Vector2 seekForce = desriredVelocity - getAgent()->getMoveComponent()->getVelocity();

	return seekForce;
}
