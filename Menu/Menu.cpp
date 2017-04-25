#include "Menu.h"

void DisplayMenu()
{
	std::vector<ColorRGB> BG;
	int success = 0;
	bool quit = 0;
	
	unsigned long mw, mh;
  	success = loadImage(BG, mw, mh, "Textures/o'fallonstein.png");

	Button StartButton(Vector2<double>(screenWidth/2 - 330, screenHeight/2 + 100),  &StartGame, "Textures/UI/Start.png");
	Button InfoButton(Vector2<double>(screenWidth/2 - 100, screenHeight/2 + 100), &ShowInfo, "Textures/UI/Info.png");
	Button ExitButton(Vector2<double>(screenWidth/2 + 120, screenHeight/2 + 100), nullptr, "Textures/UI/Exit.png");

	if (success == 0)
		std::cout << "Logo Loaded" << std::endl;
	else
		std::cout << "Logo Not Loaded" << std::endl;

	success = false;

	Mix_Music* menuMusic = Mix_LoadMUS("Music/CallMe8bit.wav");
	playSong(menuMusic);

	//who the heck loves setting success so bad
	success = false;

	while(!success && !quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		//could use MOUSEBUTTONDOWN to change button graphic
		//but how to do that with function pointers

		int mx, my;
		SDL_GetMouseState(&mx, &my);

		StartButton.OnHover(mx, my);
		InfoButton.OnHover(mx, my);
		ExitButton.OnHover(mx, my);

		if( event.type == SDL_MOUSEBUTTONUP )
		{
			success = StartButton.OnClick(mx, my);
			quit = ExitButton.OnClick(mx, my);
		}

		double skipX = screenWidth / mw;
		double skipY = screenHeight / mh;
		//std::cout << skipX << " " << skipX << std::endl;

		//I don' know how this works ask Logan
		//draw each pixel of the image
		for(int y = 0; y < mh; y++)
		{
			for(int x = 0; x < mw; x++)
			{
				for (int i = x * skipX; i < screenWidth && i < x * skipX + skipX; i++)
				{
					for (int j = y * skipY; j < screenHeight && j < y * skipY + skipY; j++)
					{
						pset(i, j, BG[y * mw + x]);
					}
				}
			}
		}

		//draws the button. vector would allow drawing all buttons at once
		StartButton.Draw();
		InfoButton.Draw();
		ExitButton.Draw();

		redraw();
	}
}

//this function is really weird I don't know if I like it
//-Ryan
void StartGame()
{
	Mix_HaltChannel(-1);
	
	CutsceneManager cm;

	//plays the intro
	//cm.PlayRange(SCENE1, SCENE5, true, "Music/OFallonsteinfeld.wav");
	
	Mix_HaltChannel(-1);
	Game game;
	game.RunGame();

	//Level 1
	game.Play("OF1", Songs::AndySong);
	Mix_HaltChannel(-1);

	//level 2
	game.setPlayerPos(28, 3);
	game.Play("OF2", Songs::AndySong);
	Mix_HaltChannel(-1);

	//Boss Level
	game.setPlayerPos(27, 14);
	game.Play("OFBOSS", Songs::AndySong);
	Mix_HaltChannel(-1);

	//if lose
	//if(true)
		//cm.PlayRange(GAMEOVER1, GAMEOVER5, false, "Music/SoundOfAndy.wav", 2000);

	//if win
	//if(true)
		//cm.PlayRange(SCENE6, CREDITS, false, "Music/Credits.wav", 3000);
}

void ShowInfo()
{
	//
}