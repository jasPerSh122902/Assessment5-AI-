#include "MainScene.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Transform2D.h"
#include "Player.h"
#include "Agent.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "StateMachineComponent.h"

MainScene::MainScene()
{
	Player* player = new Player(200, 50, "Player", 100, 50);
	player->getTransform()->setScale({ 50,50 });
	player->addComponent(new SpriteComponent("Images/player.png"));

	Agent* agent = new Agent(0, 0, "Agent", 200, 500);
	agent->getTransform()->setScale({ 50,50 });
	agent->addComponent(new SpriteComponent("Images/enemy.png"));

	WanderComponent* wanderComponent = new WanderComponent(1000, 100, 100);
	wanderComponent->setSteeringForce(100);
	wanderComponent->setEnabled(1);
	agent->addComponent(wanderComponent);

	SeekComponent* seekComponent = new SeekComponent();
	seekComponent->setEnabled(0);
	seekComponent->setSteeringForce(500);
	seekComponent->setTarget(player);
	agent->addComponent(seekComponent);
	agent->addComponent<StateMachineComponent>();

	addActor(player);
	addActor(agent);
}

void MainScene::start()
{
	Scene::start();
}

void MainScene::draw()
{
	Scene::draw();
}

void MainScene::update(float deltaTime)
{
	Scene::update(deltaTime);
}
