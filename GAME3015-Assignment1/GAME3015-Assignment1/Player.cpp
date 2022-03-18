#include "Player.h"
//The Player class contains two methods to react to the eventsand real - time input, respectively :
//	class Player
//{
//public:
//	void handleEvent(CommandQueue& commands);
//	void handleRealtimeInput(CommandQueue& commands);
//};
//These methods could be invoked from the Game class, inside a new member function such as
//processInput(.All events are delegated to the Player class :
//	void Game::processInput()
//{
//	CommandQueue& commands = mWorld.getCommandQueue();
//	mPlayer.handleEvent(commands);
//	mPlayer.handleRealtimeInput(commands);
//}
//void Player::handleRealtimeInput(CommandQueue& commands)
//{
//	const float playerSpeed = 30.f;
//	if (GetAsyncKeyState(VK_UP) & 0x8000)
//	{
//		Command moveLeft;
//		moveLeft.category = Category::PlayerAircraft;
//		moveLeft.action = derivedAction<Aircraft>(
//			AircraftMover(-playerSpeed, 0.f));
//		commands.push(moveLeft);
//	}
//}