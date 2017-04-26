#include "Menu/Menu.h"

int main(int /*argc*/, char */*argv*/[])
{
	// For random numbers
	std::srand(std::time(nullptr));

	//Initializes Screen
	screen(screenWidth, screenHeight, 1, GAMENAME);

	//Starts Audio Handler
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		BAD();

	//menu is all
	DisplayMenu();

	return 0;
}
