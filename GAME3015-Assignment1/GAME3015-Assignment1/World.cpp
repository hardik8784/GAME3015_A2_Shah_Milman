#include "World.h"

World::World(Game* window)
	: mSceneGraph(new SceneNode(window))
	, mGame(window)
	, mBackground(nullptr)
	, mPlayerAircraft(nullptr)
	, mScrollSpeed(1.0f)
	, mWorldBounds(-4.5f, 4.5f, -3.0f, 3.0f)
	
{
}

void World::update(const GameTimer& gt)
{
	if (mPlayerAircraft->getWorldPosition().x < mWorldBounds.x
		|| mPlayerAircraft->getWorldPosition().x > mWorldBounds.y)
	{
		mPlayerAircraft->SetVelocity(XMFLOAT3(mPlayerAircraft->GetVelocity().x * -1.0f, 0, 0));
	}
	mSceneGraph->update(gt);
}

void World::draw()
{
	mSceneGraph->draw();
}

void World::buildScene()
{
	
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Type::Eagle, mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0.0f, 0.1f, 0.0f);
	mPlayerAircraft->setScale(0.5f, 0.5f, 0.5f);
	mPlayerAircraft->SetVelocity(mScrollSpeed, 0.0f, 0.0f);
	mSceneGraph->attachChild(std::move(player));


	std::unique_ptr<Aircraft> mleftEscort(new Aircraft(Aircraft::Type::Raptor, mGame));
	auto leftScort = mleftEscort.get();
	leftScort->setPosition(0.5f, 0.0f, -0.5f);
	leftScort->setScale(1.0f, 1.0f, 1.0f);
	leftScort->setRotation(0.0f,  0.0f, 0.0f);
	mPlayerAircraft->attachChild(std::move(mleftEscort));

	std::unique_ptr<Aircraft> mRightEscort(new Aircraft(Aircraft::Type::Raptor, mGame));
	auto RightEscort = mRightEscort.get();
	RightEscort->setPosition(-0.5, 0, -0.5f);
	RightEscort->setScale(1.0, 1.0, 1.0);
	RightEscort->setRotation(0, 0.0f, 0);
	mPlayerAircraft->attachChild(std::move(mRightEscort));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(400, 1.0, 400);
	mBackground->SetVelocity(0, 0, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
}
