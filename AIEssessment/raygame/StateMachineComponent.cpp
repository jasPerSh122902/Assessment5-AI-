#include "StateMachineComponent.h"
#include "Actor.h"
#include "SeekComponent.h"
#include "FleeComponent.h"
#include "PathfindComponent.h"
#include "WanderComponent.h"
#include "Transform2D.h"
#include <iostream>

void StateMachineComponent::start()
{
	Component::start();

	m_seekComponent = getOwner()->getComponent<SeekComponent>();
	m_seekForce = m_seekComponent->getSteeringForce();

	m_wanderComponent = getOwner()->getComponent<WanderComponent>();
	m_wanderForce = m_wanderComponent->getSteeringForce();

	m_pathFind = getOwner()->getComponent<PathfindComponent>();
	m_pathFind->setEnabled(0);

	m_currentState = Wander;
}

void StateMachineComponent::update(float deltaTime)
{
	Component::update(deltaTime);
	//get the world position of the target
	MathLibrary::Vector2 targetPos = m_seekComponent->getTarget()->getTransform()->getWorldPosition();
	//gets the world position of the owner
	MathLibrary::Vector2 ownerPos = getOwner()->getTransform()->getWorldPosition();
	//is the magnitude of the world position of the enemy and player
	float distanceFromTarget = (targetPos - ownerPos).getMagnitude();
	//is the cone
	MathLibrary::Vector2 coneFlee = (targetPos - ownerPos).getNormalized();
	//range that is the distnace from the target and the seek range
	bool targetInRange = distanceFromTarget <= m_seekRange;
	//this is going to make a cone in front of the enemy 

	switch (m_currentState)
	{
	case SEEK:
		//1 is true to enable the pathfinding
		m_pathFind->setEnabled(1);
		m_seekComponent->setSteeringForce(m_seekForce);
		m_wanderComponent->setSteeringForce(0);
		std::cout << "I am here" << std::endl;
		//std::cout << getOwner()->getTransform()->getForward().x <<"\\" << getOwner()->getTransform()->getForward().y << std::endl;
	if (distanceFromTarget >= 300)
			setCurrentState(Wander);
		break;
	case Wander:
		//0 is false to disable the path finding
		m_pathFind->setEnabled(0);
		m_seekComponent->setSteeringForce(0);
		m_wanderComponent->setSteeringForce(m_wanderForce);
		std::cout << "I am here to wander" << std::endl;
		//this is a cone and you can change the number at the end to get a different amount of vishion
		if (distanceFromTarget <= 250 && acos(MathLibrary::Vector2::dotProduct(coneFlee, getOwner()->getTransform()->getForward())) < 1)
			setCurrentState(SEEK);
		break;
	}
}
