#define NOMINMAX

#include "World.h"

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	//Window Boundaries
	, mWorldBoundariess(-7.0f, 7.0f, -5.0f, 5.5f) 
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(1.0f)
{
}

/// <summary>
/// Updates the scene graph, calls the update function of eahc scene node
/// </summary>
/// <param name="gt"></param>
void World::update(const GameTimer& gt)
{

	mPlayerAircraft->setVelocity(0.0f, 0.0f, 0.0f);
	while (!mCommandQueue.isEmpty())
		mSceneGraph->onCommand(mCommandQueue.pop(), gt);

	playerVelocityChange();
	mSceneGraph->update(gt);
	playerPositionChange();


}

void World::draw()
{
	mSceneGraph->draw();
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

/// <summary>
/// Builds the game scene, creates scene nodes and adds the m to the scene graph
/// </summary>
void World::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Type::Eagle, mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0.0f, 0.1f, 0.0f);
	mPlayerAircraft->setScale(0.5f, 0.5f, 0.5f);
	mPlayerAircraft->setVelocity(mScrollSpeed, 0.0f, 0.0f);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<Aircraft> enemy1(new Aircraft(Aircraft::Type::Raptor, mGame));
	auto raptor = enemy1.get();
	raptor->setPosition(0.5f, 0.0f, -1.0f);
	raptor->setScale(1.0f, 1.0f, 1.0f);
	raptor->setWorldRotation(0.0f, 0, 0.0f);
	mPlayerAircraft->attachChild(std::move(enemy1));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Type::Raptor, mGame));
	auto raptor2 = enemy2.get();
	raptor2->setPosition(-0.5, 0, -1);
	raptor2->setScale(1.0, 1.0, 1.0);
	raptor2->setWorldRotation(0, 0, 0);
	mPlayerAircraft->attachChild(std::move(enemy2));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(200.0, 1.0, 200.0);
	mBackground->setVelocity(0, 0, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
}

void World::playerPositionChange()
{
	const float borderDistance = 100.f;

	XMFLOAT3 position = mPlayerAircraft->getWorldPosition();
	position.x = std::max(position.x, mWorldBoundariess.x);
	position.x = std::min(position.x, mWorldBoundariess.y);
	position.z = std::max(position.z, mWorldBoundariess.z);
	position.z = std::min(position.z, mWorldBoundariess.w);
	mPlayerAircraft->setPosition(position.x, position.y, position.z);
}

void World::playerVelocityChange()
{
	XMFLOAT3 velocity = mPlayerAircraft->getVelocity();

	if (velocity.x != 0.f && velocity.z != 0.f)
		mPlayerAircraft->setVelocity(velocity.x / std::sqrt(2.f), velocity.y / std::sqrt(2.f), velocity.z / std::sqrt(2.f));
}
