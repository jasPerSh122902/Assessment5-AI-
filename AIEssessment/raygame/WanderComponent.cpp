#include "WanderComponent.h"
#include "Transform2D.h"
#include "Actor.h"
#include "Agent.h"
#include "MoveComponent.h"
#include "NodeGraph.h"
#include <time.h>

WanderComponent::WanderComponent(float circleDistance, float circleRadius, float wanderForce) : SteeringComponent(nullptr, wanderForce)
{
	m_distance = circleDistance;
	m_radius = circleRadius;
	srand(time(NULL));
}

MathLibrary::Vector2 WanderComponent::calculateForce()
{
	if (getSteeringForce() == 0)
		return { 0,0 };
	//finds the agnets poitin and heading
	MathLibrary::Vector2 ownerPos = getOwner()->getTransform()->getWorldPosition();//gets the worldposition for the owner or agent
	MathLibrary::Vector2 heading = (getAgent()->getComponent<MoveComponent>()->getVelocity());//gets the agnets velocity

	//Find the circles position in front of the agent
	m_circlePos = ownerPos + (heading * m_distance);
	//Find a random vector on the circle and scale it up by the radius
	MathLibrary::Vector2 randDirection = MathLibrary::Vector2{ getTheRand(), getTheRand() }.normalize() * m_radius;
	//finds the target by adding the random point and circle position
	m_target = randDirection + m_circlePos;
	//seek to the random point
	MathLibrary::Vector2 desiredVelocity = MathLibrary::Vector2::normalize(m_target - ownerPos) * getSteeringForce();
	MathLibrary::Vector2 force = desiredVelocity - getAgent()->getComponent<MoveComponent>()->getVelocity();
	return force;
}

float WanderComponent::getTheRand()
{
	float m_rand;
	//makes a random number
	m_rand = ((rand() % 201) - 100);
	return m_rand;
}
