#include <ResourceManager.h>
#include "TestGame.h"

TestGame game;

int main(int argc, char* args[])
{
	game.Init(1920, 1080);
	game.MainLoop();
	game.Exit();
	return 0;
}