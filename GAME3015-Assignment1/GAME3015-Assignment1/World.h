#pragma once
#include "SceneNode.h"
#include "Aircraft.h"
#include "SpriteNode.h"
#include "CommandQueue.h"
#include "Command.h"

class World
{
public:
	explicit World(Game* game);
	void update(const GameTimer& gt);
	void draw();
	CommandQueue& getCommandQueue();

	void buildScene();
private:
	CommandQueue mCommandQueue;


	void playerPositionChange();
	void playerVelocityChange();

private:
	enum class Layer
	{
		BG,
		Air
	};

private:
	Game* mGame;
	SceneNode* mSceneGraph;
	std::array<SceneNode*, 2> mSceneLayers;

	XMFLOAT4 mWorldBoundariess;
	XMFLOAT2 mSpawnPosition;

	float mScrollSpeed;

	Aircraft* mPlayerAircraft;
	SpriteNode* mBackground;
	Aircraft* mEnemy;
};
