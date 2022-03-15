/**
* @brief World class
* Creats game objectes
*
*/
#pragma once
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Aircraft.h"
class World
{
public:
	/// <summary>
	/// World constructor
	/// </summary>
	/// <param name="window">pointer to game</param>
	explicit							World(Game* window);
	/// <summary>
	/// Update function.
	/// updating all the scene nodes attache to the scenegraph and their child
	/// </summary>
	/// <param name="gt">GameTimer </param>
	void								update(const GameTimer& gt);
	/// <summary>
	/// Draw function.
	/// Drawing all the scene nodes attache to the scenegraph and their child
	/// </summary>
	void								draw();
	/// <summary>
	/// Build scene.
	/// bilding all the game objects in the scene and attach them to scenegraph
	/// </summary>
	void								buildScene();

private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};

private:
	Game* mGame;
	SceneNode* mSceneGraph;
	std::array<SceneNode*, 3>                         mSceneLayers;
	XMFLOAT4                                          mWorldBounds;
	XMFLOAT2                                          mSpawnPostion;
	float                                             mScrollSpeed;
	Aircraft*                                         mPlayerAircraft;
	Aircraft*										  mLeftEscort;
	Aircraft*										  mRightEscort;
	SpriteNode*										  mBackground;



};

