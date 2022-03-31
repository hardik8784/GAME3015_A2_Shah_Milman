#include "Entity.h"

Entity::Entity(Game* game) : SceneNode(game), mVelocity(0, 0, 0)
{
}

/// <summary>
/// Sets the velocity of the entity
/// </summary>
/// <param name="velocity"></param>
void Entity::setVelocity(XMFLOAT3 velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy, float vz)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
	mVelocity.z = vz;
}

/// <summary>
/// returns the velocity of the entity
/// </summary>
/// <returns></returns>
XMFLOAT3 Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::accelerate(XMFLOAT3 velocity)
{
	mVelocity.x = mVelocity.x + velocity.x;
	mVelocity.y = mVelocity.y + velocity.y;
	mVelocity.z = mVelocity.z + velocity.z;
}

void Entity::accelerate(float vx, float vy, float vz)
{
	mVelocity.x = mVelocity.x + vx;
	mVelocity.y = mVelocity.y + vy;
	mVelocity.z = mVelocity.z + vz;
}

/// <summary>
/// Updates the current entity
/// </summary>
/// <param name="gt"></param>
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
