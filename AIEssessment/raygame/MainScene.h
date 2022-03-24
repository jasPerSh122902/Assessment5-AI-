#pragma once
#include "Scene.h"
class MainScene :
	public Scene
{
public:
	void start() override;
	void draw() override;
	void update(float deltaTime) override;
};

