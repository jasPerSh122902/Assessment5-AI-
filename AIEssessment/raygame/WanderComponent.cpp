#include "WanderComponent.h"
#include "Transform2D.h"
#include "Actor.h"
#include "NodeGraph.h"
#include <time.h>
#include "MazeScene.h"
#include "Agent.h"
#include "MoveComponent.h"
#include "SteeringComponent.h"

WanderComponent::WanderComponent(float circleDistance, float circleRadius, float wanderForce)
{
	m_distance = circleDistance;
	m_radius = circleRadius;
	srand(time(NULL));
}

WanderComponent::WanderComponent(float circleDistance, float circleRadius, float wanderForce, Maze* maze) : m_maze(maze)
{
	m_distance = circleDistance;
	m_radius = circleRadius;
	srand(time(NULL));
}

MathLibrary::Vector2 WanderComponent::calculateForce()
{
	if (m_steeringComponent->getSteeringForce() == 0)
		return { 0,0 };
	//finds the agnets poitin and heading
	MathLibrary::Vector2 ownerPos = getOwner()->getTransform()->getWorldPosition();//gets the worldposition for the owner or agent
	MathLibrary::Vector2 heading = (m_owner->getComponent<MoveComponent>()->getVelocity());//gets the agnets velocity

	//Find the circles position in front of the agent
	m_circlePos = ownerPos + (heading * m_distance);
	//Find a random vector on the circle and scale it up by the radius
	MathLibrary::Vector2 randDirection = MathLibrary::Vector2{ getTheRand(), getTheRand() }.normalize() * m_radius;
	//finds the target by adding the random point and circle position
	m_targetVelocity = randDirection + m_circlePos;
	//seek to the random point
	MathLibrary::Vector2 desiredVelocity = MathLibrary::Vector2::normalize(m_targetVelocity - ownerPos) * m_steeringComponent->getSteeringForce();
	MathLibrary::Vector2 force = desiredVelocity - m_owner->getComponent<MoveComponent>()->getVelocity();
		return force;
}

float WanderComponent::getTheRand()
{
	float m_rand;
	//makes a random number
	m_rand = ((rand() % 201) - 100);
	return m_rand;
}

void WanderComponent::start()
{
	Component::start();
	m_owner = (Agent*)getOwner();
}

void WanderComponent::update(float deltaTime)
{
	
	//Don't update if disabled or no target
	if (!m_target)
		return;

	//Find the positions and tiles of the owner and target
	MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getWorldPosition();
	MathLibrary::Vector2 destinationPosition = findDestination();
	Maze::Tile ownerTile = m_maze->getTile(ownerPosition);
	Maze::Tile destinationTile = m_maze->getTile(destinationPosition);

	//Update the path if needed
	if (m_needPath)
		updatePath(destinationPosition);

	//Find the position and tile of the next node
	MathLibrary::Vector2 nextPosition = ownerPosition;
	if (!m_path.getLength() <= 0)
		nextPosition = m_path[0]->position;
	Maze::Tile nextTile = m_maze->getTile(nextPosition);

	//If owner is at the front node, go to the following node
	if (ownerTile.x == nextTile.x && ownerTile.y == nextTile.y) {
		if (!m_path.getLength() <= 0)
			m_path.remove(0);
		m_needPath = true;
	}

	//Find the direction
	MathLibrary::Vector2 direction = { 0.0f, 0.0f };
	if (!m_path.getLength() <= 0)
		direction = MathLibrary::Vector2::normalize(m_path[0]->position - ownerPosition);

	//Calculate the force
	MathLibrary::Vector2 desiredVelocity = direction * m_owner->getMaxForce();
	MathLibrary::Vector2 steeringForce = desiredVelocity - m_owner->getMoveComponent()->getVelocity();

	m_owner->getMoveComponent()->setVelocity(steeringForce);
}

void WanderComponent::draw()
{
	for (int i = 0; i < m_path.getLength(); i++)
	{
		NodeGraph::Node* node = m_path[i];
		NodeGraph::drawNode(node, m_color);
	}
}

void WanderComponent::updatePath()
{
	updatePath(m_targetVelocity);
}

void WanderComponent::updatePath(MathLibrary::Vector2 destination)
{
	NodeGraph::Node* ownerNode = m_maze->getTile(getOwner()->getTransform()->getWorldPosition()).node;
	NodeGraph::Node* targetNode = m_maze->getTile(destination).node;
	m_path = NodeGraph::findPath(ownerNode, targetNode);
	//if (!m_path.empty()) m_path.pop_front();
	m_needPath = false;
}

MathLibrary::Vector2 WanderComponent::findDestination()
{
	return m_targetVelocity;
}