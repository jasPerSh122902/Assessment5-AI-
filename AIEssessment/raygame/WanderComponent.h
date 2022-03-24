#pragma once
#include "SteeringComponent.h"
#include "NodeGraph.h"

class Maze;
class Agent;
class SteeringComponent;

class WanderComponent :
	public Component
{

public:
	WanderComponent(float circleDistance, float circleRadius, float wanderForce);
	WanderComponent(float circleDistance, float circleRadius, float wanderForce, Maze* maze);
	MathLibrary::Vector2 calculateForce();
	float getTheRand();

	void start() override;

	/// <summary>
	/// Update the Behavior, affecting its owning Agent where necessary.
	/// </summary>
	/// <param name="owner">The Agent to which this Behavior belongs</param>
	/// <param name="deltaTime"></param>
	virtual void update(float deltaTime) override;

	/// <summary>
	/// Draw the Behavior, primarily for debugging purposes. Agent calls
	/// this by default.
	/// </summary>
	/// <param name="owner">The Agent to which this Behavior belongs</param>
	virtual void draw() override;

	/// <summary>
	/// Update the current path to the target.
	/// This is called by update(Agent*,float).
	/// </summary>
	/// <param name="owner">The Agent to which this Behavior belongs</param>
	void updatePath();
	/// <summary>
	/// Update the current path to the given destination.
	/// This is called by update(Agent*,float).
	/// </summary>
	/// <param name="owner">The Agent to which this Behavior belongs</param>
	/// <param name="destination">The new destination</param>
	void updatePath(MathLibrary::Vector2 destination);

	/// <returns>The current target to use in pathfinding</returns>
	Actor* getTarget() { return m_target; }
	/// <summary>
	/// Set the target to a new actor.
	/// </summary>
	/// <param name="target">The actor to use in pathfinding</param>
	void setTarget(Actor* target) { m_target = target; }

	int getColor() { return m_color; }
	void setColor(int color) { m_color = color; }

	void onEnabled() override { m_needPath = true; }

protected:
	virtual MathLibrary::Vector2 findDestination();

private:
	float m_radius = 0;
	float m_distance = 0;
	float m_wanderAngle = 0;//we will come back to this
	MathLibrary::Vector2 m_targetVelocity;
	MathLibrary::Vector2 m_circlePos;
	Maze* m_maze;
	SteeringComponent* m_steeringComponent;
	DynamicArray<NodeGraph::Node*> m_path;
	Agent* m_owner;
	Actor* m_target = nullptr;
	bool m_needPath = true;
	int m_color = 0xFFFFFFFF;
};

