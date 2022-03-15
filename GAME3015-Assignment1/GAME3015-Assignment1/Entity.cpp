#include "Entity.h"

Entity::Entity(Game* game)
	:SceneNode(game)
	, mVelocity(0, 0, 0)
{
}

void Entity::SetVelocity(XMFLOAT3 velocity)
{
	mVelocity = velocity;
}

void Entity::SetVelocity(float vx, float vy, float vz)
{
	mVelocity = XMFLOAT3(vx, vy, vz);
}

XMFLOAT3 Entity::GetVelocity() const
{
	return mVelocity;
}

void Entity::updateCurrent(const GameTimer& gt)
{
	XMFLOAT3 mV;
	mV.x = mVelocity.x * gt.DeltaTime();
	mV.y = mVelocity.y * gt.DeltaTime();
	mV.z = mVelocity.z * gt.DeltaTime();

	move(mV.x, mV.y, mV.z);

	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;
}
//
//#include <Entity.hpp>
//
//
//void Entity::setVelocity(sf::Vector2f velocity)
//{
//	mVelocity = velocity;
//}
//
//void Entity::setVelocity(float vx, float vy)
//{
//	mVelocity.x = vx;
//	mVelocity.y = vy;
//}
//
//sf::Vector2f Entity::getVelocity() const
//{
//	return mVelocity;
//}
//
//void Entity::updateCurrent(sf::Time dt)
//{
//	move(mVelocity * dt.asSeconds());
//}
//
//void Entity::accelerate(sf::Vector2f velocity)
//{
//	mVelocity += velocity;
//}
//
//void Entity::accelerate(float vx, float vy)
//{
//	mVelocity.x += vx;
//	mVelocity.y += vy;
//}
//
