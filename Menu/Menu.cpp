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

	//who the heck loves setting success so bad
	success = false;

	while(!quit)
	{
		if( Mix_PlayingMusic() == 0 )
		{
			Mix_Music* menuMusic = Mix_LoadMUS("Music/CallMe8bit.wav");
			playSong(menuMusic);
		}
		SDL_ShowCursor(1);
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
			InfoButton.OnClick(mx, my);
			success = StartButton.OnClick(mx, my);
			quit = ExitButton.OnClick(mx, my);
		}

		//Hunter wrote this I guess
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
//UPDATE: it's not so bad anymore
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

	//Level 2
	if(game.mQuit) return;

	game.setPlayerPos(28, 3);
	game.Play("OF2", Songs::BitFeel);
	Mix_HaltChannel(-1);

	//Boss Level
	if(game.mQuit) return;
	
	game.setPlayerPos(27, 14);
	game.Play("OFBOSS", Songs::MachoBit);
	Mix_HaltChannel(-1);

	if(game.mQuit) return;

	//Drop through means winning
	cm.PlayRange(SCENE6, CREDITS, false, "Music/Credits.wav", 3750);

	//if win
		//cm.PlayRange(SCENE6, CREDITS, false, "Music/Credits.wav", 3750);

	//if lose
		//cm.PlayRange(GAMEOVER1, GAMEOVER5, false, "Music/SoundOfAndy.wav", 2000);
}

void ShowInfo()
{
	bool failed;
	bool pause = 53; //i love bools
	long unsigned int mw, mh;
	SDL_Event event;
	
	Button ResumeButton(Vector2<double>(screenWidth/2 - 100, screenHeight/2 + 175), nullptr, "Textures/UI/Resume.png");

	std::vector<ColorRGB> image;
	image.resize(screenWidth * screenHeight);
	failed = loadImage (image, mw, mh, "Textures/UI/HelpMenu.png");

	if (failed)
		std::cout << "loading failed" << std::endl;

	int mx, my;

	//draw info image
	for (int y = 0; y < screenHeight; ++y)
	for (int x = 0; x < screenWidth; ++x)
		pset(x, y, image[y * screenWidth + x]);
			
	while (pause)
	{
		SDL_PollEvent(&event);
		readKeys();
		
		//this is where buttons logic should go
		ResumeButton.OnHover(mx, my);
		ResumeButton.Draw();

		SDL_GetMouseState(&mx, &my);

		redraw();

		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (ResumeButton.OnClick(mx, my))
				pause = false;
		}

		if (keyDown(SDLK_ESCAPE))
		{
			pause = false;
		}
	}
}