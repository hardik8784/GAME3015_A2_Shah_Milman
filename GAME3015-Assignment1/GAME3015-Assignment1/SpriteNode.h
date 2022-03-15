/**
* @brief SpriteNode class.
* Extends enetity class
*
*/
#pragma once
#include "Entity.h"
class SpriteNode : public Entity
{
public:
	/// <summary>
	/// SpriteNode constructor
	/// </summary>
	/// <param name="game">pointer to game</param>
	SpriteNode(Game* game);
private:
	/// <summary>
	/// drawCurrent function
	/// </summary>
	virtual void		drawCurrent() const;
	/// <summary>
	/// buildCurrent function.
	/// setting up render item
	/// </summary>
	virtual void		buildCurrent();
};