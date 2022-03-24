#pragma once
#include "Component.h"

enum State
{
	SEEK,
	Wander
};

class SeekComponent;
class WanderComponent;
class PathfindComponent;

class StateMachineComponent :
	public Component
{
public:
	void start() override;

	State getCurrentState() { return m_currentState; }
	void setCurrentState(State state) { m_currentState = state; }

	void update(float deltaTime) override;

private:
	State m_currentState;
	SeekComponent* m_seekComponent;
	WanderComponent* m_wanderComponent;
	PathfindComponent* m_pathFind;
	float m_seekForce;
	float m_fleeingForce;
	bool m_wanderForce;
	float m_seekRange = 150;
};

