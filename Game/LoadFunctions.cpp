#include "Game.h"

void Game::InitPlayer()
{
	// Player Class Members
	mPlayer.setArmor(0);
	mPlayer.setBattery(100);
	mPlayer.setCameraPlane(0, 0.66);

	// Character Class Members
	mPlayer.setHealth(100);
	mPlayer.setSpeed(1);

	// Object Class Members
	mPlayer.setPosition(26, 26);
	mPlayer.setDirection(-1, 0);

	// Inwit default gun
	mPlayer.AddGun((screenHeight * 3) / 4 - 300, (screenWidth/2) - 250/2, 2, 1000, GunTextures::Raid);
	mPlayer.getCurrentGun().addAnimationFrame(GunTextures::RaidAnim1);
	mPlayer.getCurrentGun().addAnimationFrame(GunTextures::RaidAnim2);
	mPlayer.getCurrentGun().addAnimationFrame(GunTextures::RaidAnim3);
	mPlayer.setShootSound(mSounds[Sounds::ShootSound]);

	std::cout << "Player Initialized" << std::endl;
}

void Game::LoadTextures()
{
	int success = 0;

	// Initialize Each Image Buffer
	for(int i = 0; i < numTextures; i++) mTextures[i].resize(texWidth * texHeight);
	for(int i = 0; i < numGunTextures; i++) mGuns[i].resize(gunTexWidth * gunTexHeight);
	mUI.resize(256*800);

	unsigned long tw, th;
	// Ship Textures


	// Ceiling Textures
    success |= loadImage(mTextures[Textures::AndyCeiling], tw, th, "Textures/Ceilings/andyWall1.png");
    success |= loadImage(mTextures[Textures::computerCeiling], tw, th, "Textures/Ceilings/computer_ceiling.png");
	// Wall Textures
    success |= loadImage(mTextures[Textures::AndyWall], tw, th, "Textures/Walls/andyWall.png");
    success |= loadImage(mTextures[Textures::AndyWall2], tw, th, "Textures/Walls/andyWall2.png");
	success |= loadImage(mTextures[Textures::AndyWall3], tw, th, "Textures/Walls/andyWall3.png");
	success |= loadImage(mTextures[Textures::AndyWall4], tw, th, "Textures/Walls/andyWall4.png");
	success |= loadImage(mTextures[Textures::AndyWall5], tw, th, "Textures/Walls/andyWall5.png");
	success |= loadImage(mTextures[Textures::AndyWall6], tw, th, "Textures/Walls/andyWall6.png");
	success |= loadImage(mTextures[Textures::AndyWall7], tw, th, "Textures/Walls/andyWall7.png");
	success |= loadImage(mTextures[Textures::computer], tw, th, "Textures/Walls/computer.png");
	success |= loadImage(mTextures[Textures::Comp4], tw, th, "Textures/Walls/Computer_4.png");
	success |= loadImage(mTextures[Textures::Comp3], tw, th, "Textures/Walls/Computer_3.png");
	success |= loadImage(mTextures[Textures::Comp2], tw, th, "Textures/Walls/Computer_2.png");
	
	// Floor Textures
    success |= loadImage(mTextures[Textures::Ground], tw, th, "Textures/Floors/ground.png");
    success |= loadImage(mTextures[Textures::computerFloor], tw, th, "Textures/Floors/computer_floor.png");

	// Enemy Textures
	success |= loadImage(mTextures[Textures::caterpillar], tw, th, "Textures/Enemies/caterpillar.png");
    success |= loadImage(mTextures[Textures::caterpillarHurt], tw, th, "Textures/Enemies/caterpillar_hurt.png");
	success |= loadImage(mTextures[Textures::worm], tw, th, "Textures/Enemies/worm.png");
	success |= loadImage(mTextures[Textures::workHurt], tw, th, "Textures/Enemies/worm_hurt.png");
	success |= loadImage(mTextures[Textures::cock], tw, th, "Textures/Enemies/Cock.png");
	success |= loadImage(mTextures[Textures::cockHurt], tw, th, "Textures/Enemies/Cock_hurt.png");
	success |= loadImage(mTextures[Textures::grasshopper], tw, th, "Textures/Enemies/grasshopper.png");
	success |= loadImage(mTextures[Textures::grasshopperHurt], tw, th, "Textures/Enemies/grasshopper_hurt.png");
	success |= loadImage(mTextures[Textures::mosquito], tw, th, "Textures/Enemies/Mosquito.png");
	success |= loadImage(mTextures[Textures::mosquitoHurt], tw, th, "Textures/Enemies/Mosquito_hurt.png");
	success |= loadImage(mTextures[Textures::spider], tw, th, "Textures/Enemies/spider.png");
	success |= loadImage(mTextures[Textures::spiderHurt], tw, th, "Textures/Enemies/spider_hurt.png");
	success |= loadImage(mTextures[Textures::wasp], tw, th, "Textures/Enemies/Wasp.png");
	success |= loadImage(mTextures[Textures::waspHurt], tw, th, "Textures/Enemies/Wasp_hurt.png");

	success |= loadImage(mTextures[Textures::geek], tw, th, "Textures/Enemies/_Geek.png");
	success |= loadImage(mTextures[Textures::happy], tw, th, "Textures/Enemies/_happy.png");
	success |= loadImage(mTextures[Textures::loser], tw, th, "Textures/Enemies/_Loser.png");
	success |= loadImage(mTextures[Textures::mad], tw, th, "Textures/Enemies/_Mad.png");
	success |= loadImage(mTextures[Textures::nerd], tw, th, "Textures/Enemies/_Nerd.png");
	success |= loadImage(mTextures[Textures::surprised], tw, th, "Textures/Enemies/_Suprised.png");
	success |= loadImage(mTextures[Textures::mad2], tw, th, "Textures/Enemies/2attack.png");
	success |= loadImage(mTextures[Textures::geek2], tw, th, "Textures/Enemies/2Geek.png");
	success |= loadImage(mTextures[Textures::nerd2], tw, th, "Textures/Enemies/2Nerd.png");
	success |= loadImage(mTextures[Textures::sad2], tw, th, "Textures/Enemies/2Sad.png");
	success |= loadImage(mTextures[Textures::loser3], tw, th, "Textures/Enemies/3Loser.png");
	success |= loadImage(mTextures[Textures::mad3], tw, th, "Textures/Enemies/3Mad.png");
	success |= loadImage(mTextures[Textures::verysad3], tw, th, "Textures/Enemies/3verySad.png");
	success |= loadImage(mTextures[Textures::sad3], tw, th, "Textures/Enemies/3Sad.png");
	success |= loadImage(mTextures[Textures::why], tw, th, "Textures/Enemies/4why.png");
	success |= loadImage(mTextures[Textures::die], tw, th, "Textures/Enemies/5dying2.png");
	success |= loadImage(mTextures[Textures::gameover], tw, th, "Textures/Enemies/5evenMoredead.png");

	// Sprites
	//success |= loadImage(mTextures[Textures::TestSprite], tw, th, "Textures/Sprites/27846.png");

	// Menu
	success |= loadImage(mTextures[Textures::GameLogo], tw, th, "Textures/gamelogo.png");

	//UIStuff
	success |= loadImage(mUI, tw, th, "Textures/UI/ofallonui.png");

	//Gun
	success |= loadImage(mGuns[GunTextures::Raid], tw, th, "Textures/UI/raid.png");
	success |= loadImage(mGuns[GunTextures::RaidAnim1], tw, th, "Textures/UI/raidboom1.png");
	success |= loadImage(mGuns[GunTextures::RaidAnim2], tw, th, "Textures/UI/raidboom2.png");
	success |= loadImage(mGuns[GunTextures::RaidAnim3], tw, th, "Textures/UI/raidboom3.png");

	if (success == 0)
		std::cout << "Textures Loaded" << std::endl;
	else
		std::cout << "Textures Not Loaded" << std::endl;
}

void Game::LoadSounds()
{
	bool success = true;

	mSounds.resize(numSounds);

	mSounds[Sounds::DamageSound] = Mix_LoadWAV("sound/urgh.wav");
	mSounds[Sounds::WillhelmScream] = Mix_LoadWAV("sound/willhelm.wav");
	mSounds[Sounds::ShootSound] = Mix_LoadWAV("sound/rap.wav");

	for (int i = 0; i < numSounds; i++)
		success &= (mSounds[i] != nullptr);

	if (success)
		std::cout << "Sound Chunks Loaded" << std::endl;
	else
		BAD();

 	//MUSIC
 	mSongs.resize(numSongs);
 
 	mSongs[Songs::AndySong] = Mix_LoadMUS("Music/Andy.wav");
 	std::cout << SDL_GetError();
 
 	for (int i = 0; i < numSongs; i++)
 		success &= (mSongs[i] != nullptr);
 
 	if (success)
 		std::cout << "Music Loaded" << std::endl;
 	else
 		BAD();
}

void Game::LoadEnemies(std::string mapName)
{
	Enemy e(5, 20, 0, 4.0, 4.0, Textures::caterpillar);
	e.setDamageSound(mSounds[Sounds::DamageSound]);
	e.setDeathSound(mSounds[Sounds::WillhelmScream]);
	mEnemies.insertAtFront(e);

	e.setPosition(22.5, 3);
	mEnemies.insertAtFront(e);
	std::cout << "Enemies Loaded" << std::endl;
}

void Game::LoadMap(std::string mapName)
{
	std::string filepath = "./Maps/" + mapName + ".txt";
	std::ifstream infile(filepath);

	for(int k = 0; k < 3; k++)
	{
		for(int i = 0; i < 30; i++)
		{
			for(int j = 0; j < 30; j++)
			{
				std::string line;
				std::getline(infile, line, ',');

				if (line == "")
				{
					std::cout << "Finished" << std::endl;
					continue;
				}

				switch(k)
				{
					case 0:
						mMap[i][j].floor = std::stoi(line);
						break;
					case 1:
						mMap[i][j].object = std::stoi(line);
						break;
					case 2:
						mMap[i][j].ceiling = std::stoi(line);
						break;
				}
			}
		}
	}

	std::cout << "Map Loaded" << std::endl;
}