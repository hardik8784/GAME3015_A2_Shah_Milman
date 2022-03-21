#pragma once

#include "Entity.h""



class Aircraft : public Entity {
public:
	enum Type {
		Eagle,
		Raptor
	};

public: 
	Aircraft(Type type);


	void Update();

private:
	// Attributes
	Type type;
	

	// Methods
	virtual void drawCurrent(GameTimer dt);
};

//
//#include <SFML/Graphics/Sprite.hpp>
//
//
//class Aircraft : public Entity
//{
//public:
//	enum Type
//	{
//		Eagle,
//		Raptor,
//	};
//
//
//public:
//	Aircraft(Type type, const TextureHolder& textures);
//
//
//private:
//	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
//
//
//private:
//	Type				mType;
//	sf::Sprite			mSprite;
//};