#include "Menu/Menu.h"

int main(int /*argc*/, char */*argv*/[])
{
	//Initializes Screen
	screen(screenWidth, screenHeight, 0, GAMENAME);

	//Starts Audio Handler
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		BAD();

	//menu is all
	DisplayMenu();

	//CutsceneManager cm;

	//plays the intro
	//cm.PlayRange(SCENE1, SCENE5);

	//plays the outro
	//cm.PlayRange(SCENE6, SCENE8);

	//plays the game over sequence
	//cm.PlayRange(GAMEOVER1, GAMEOVER5, true, "");

	//Game game;
	//game.RunGame("e1m1");

	return 0;
}
