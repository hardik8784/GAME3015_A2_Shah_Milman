
#pragma once
#include "SceneNode.h"
class Entity : public SceneNode
{
public:
	
	Entity(Game* game);
	
	void			SetVelocity(XMFLOAT3 velocity);
	
	void			SetVelocity(float vx, float vy, float vz);
	
	XMFLOAT3		GetVelocity() const;
	
	virtual void	updateCurrent(const GameTimer& gt);

public:
	XMFLOAT3		mVelocity;
};


//#pragma once
//
//#include <SceneNode.hpp>
//
//
//class Entity : public SceneNode
//{
//public:
//	void				setVelocity(sf::Vector2f velocity);
//	void				setVelocity(float vx, float vy);
//	sf::Vector2f		getVelocity() const;
//	void				accelerate(sf::Vector2f velocity);
//	void				accelerate(float vx, float vy);
//
//private:
//	virtual void		updateCurrent(sf::Time dt);
//
//private:
//	sf::Vector2f		mVelocity;
//};
//
