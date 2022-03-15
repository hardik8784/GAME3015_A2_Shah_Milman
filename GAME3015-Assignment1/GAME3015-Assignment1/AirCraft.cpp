#include "Aircraft.h"
#include "Game.h"

Aircraft::Aircraft(Type type, Game* game)
	: Entity(game)
	, mType(type)
{
	switch (type)
	{
	case (Type::Eagle):
		mSprite = "Eagle";
		break;
	case (Type::Raptor):
		mSprite = "Raptor";
		break;
	default:
		mSprite = "Eagle";
		break;
	}
}

void Aircraft::drawCurrent() const
{
	renderer->World = getWorldTransform();
	renderer->NumFramesDirty++;
}

void Aircraft::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = (UINT)game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;
	game->getRenderItems().push_back(std::move(render));
}


//
//#include <Aircraft.hpp>
//#include <ResourceHolder.hpp>
//
//#include <SFML/Graphics/RenderTarget.hpp>
//#include <SFML/Graphics/RenderStates.hpp>
//
//
//Textures::ID toTextureID(Aircraft::Type type)
//{
//	switch (type)
//	{
//	case Aircraft::Eagle:
//		return Textures::Eagle;
//
//	case Aircraft::Raptor:
//		return Textures::Raptor;
//	}
//	return Textures::Eagle;
//}
//
//Aircraft::Aircraft(Type type, const TextureHolder& textures)
//	: mType(type)
//	, mSprite(textures.get(toTextureID(type)))
//{
//	sf::FloatRect bounds = mSprite.getLocalBounds();
//	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
//}
//
//void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	target.draw(mSprite, states);
//}
//
//unsigned int Aircraft::getCategory() const
//{
//	switch (mType)
//	{
//	case Eagle:
//		return Category::PlayerAircraft;
//
//	default:
//		return Category::EnemyAircraft;
//	}
//}
//
