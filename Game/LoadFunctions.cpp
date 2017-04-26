#include "Game.h"

void Game::InitGame()
{
	
}

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
	mPlayer.setPosition(28, 15);
	mPlayer.setDirection(-1, 0);

	// Inwit default gun
	mPlayer.AddGun((screenHeight * 3) / 4 - 300, (screenWidth/2) - 250/2, 10, 1000, GunTextures::Raid);
	mPlayer.getCurrentGun().addAnimationFrame(GunTextures::RaidAnim1);
	mPlayer.getCurrentGun().addAnimationFrame(GunTextures::RaidAnim2);
	mPlayer.getCurrentGun().addAnimationFrame(GunTextures::RaidAnim3);
	mPlayer.setShootSound(mSounds[Sounds::Spray]);

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
	success |= loadImage(mTextures[Textures::Comp3], tw, th, "Textures/Walls/computer_3.png");
	success |= loadImage(mTextures[Textures::Comp2], tw, th, "Textures/Walls/computer_2.png");
	
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

	mSounds[Sounds::Absent] = Mix_LoadWAV("sound/Absent.wav");
	mSounds[Sounds::BossHit1] = Mix_LoadWAV("sound/BossHit1.wav");
	mSounds[Sounds::BossHit2] = Mix_LoadWAV("sound/BossHit2.wav");
	mSounds[Sounds::BossLaugh] = Mix_LoadWAV("sound/BossLaugh.wav");
	mSounds[Sounds::Caterpillar] = Mix_LoadWAV("sound/Caterpillar.wav");
	mSounds[Sounds::Cockroach] = Mix_LoadWAV("sound/Cockroach.wav");
	mSounds[Sounds::CockroachDeath] = Mix_LoadWAV("sound/CockroachDeath.wav");
	mSounds[Sounds::EatGuard] = Mix_LoadWAV("sound/EatGuard.wav");
	mSounds[Sounds::Geek] = Mix_LoadWAV("sound/Geek.wav");
	mSounds[Sounds::Grasshopper] = Mix_LoadWAV("sound/Grasshopper.wav");
	mSounds[Sounds::Gugh] = Mix_LoadWAV("sound/Gugh.wav");
	mSounds[Sounds::InheritThis] = Mix_LoadWAV("sound/InheritThis.wav");
	mSounds[Sounds::Loser] = Mix_LoadWAV("sound/Loser.wav");
	mSounds[Sounds::MosqDeath] = Mix_LoadWAV("sound/MosqDeath.wav");
	mSounds[Sounds::Mosquito] = Mix_LoadWAV("sound/Mosquito.wav");
	mSounds[Sounds::Nerd] = Mix_LoadWAV("sound/Nerd.wav");
	mSounds[Sounds::PenCap] = Mix_LoadWAV("sound/PenCap.wav");
	mSounds[Sounds::RaidPickup] = Mix_LoadWAV("sound/RaidPickup.wav");
	mSounds[Sounds::Spray] = Mix_LoadWAV("sound/rap.wav");
	mSounds[Sounds::SinkIn] = Mix_LoadWAV("sound/SinkIn.wav");
	mSounds[Sounds::Spider] = Mix_LoadWAV("sound/Spider.wav");
	mSounds[Sounds::StackOverflow] = Mix_LoadWAV("sound/StackOverflow.wav");
	mSounds[Sounds::TestWrapper] = Mix_LoadWAV("sound/TestWrapper.wav");
	mSounds[Sounds::TryCatch] = Mix_LoadWAV("sound/TryCatch.wav");
	mSounds[Sounds::TypeDeath] = Mix_LoadWAV("sound/TypeDeath.wav");
	mSounds[Sounds::Urgh] = Mix_LoadWAV("sound/urgh.wav");
	mSounds[Sounds::Wasp] = Mix_LoadWAV("sound/Wasp.wav");
	mSounds[Sounds::WaspDead] = Mix_LoadWAV("sound/WaspDedded.wav");
	mSounds[Sounds::WHY] = Mix_LoadWAV("sound/WHY.wav");
	mSounds[Sounds::Worm] = Mix_LoadWAV("sound/Worm.wav");
	mSounds[Sounds::Worm2] = Mix_LoadWAV("sound/Worm2.wav");

	for (int i = 0; i < numSounds; i++)
		success &= (mSounds[i] != nullptr);

	if (success)
		std::cout << "Sound Chunks Loaded" << std::endl;
	else
		BAD();

 	//MUSIC
 	mSongs.resize(numSongs);
 
 	mSongs[Songs::AndySong] = Mix_LoadMUS("Music/Andy.wav");
	mSongs[Songs::AndyOkay] = Mix_LoadMUS("Music/AndyAreYouOkay.wav");
	mSongs[Songs::BitFeel] = Mix_LoadMUS("Music/8BitFeel.wav");
	mSongs[Songs::CallMe] = Mix_LoadMUS("Music/CallMe8bit.wav");
	mSongs[Songs::Credits] = Mix_LoadMUS("Music/Credits.wav");
	mSongs[Songs::DukeAndy] = Mix_LoadMUS("Music/DukeOfAndy.wav");
	mSongs[Songs::MachoBit] = Mix_LoadMUS("Music/MachoBit.wav");
	mSongs[Songs::SteinFeld] = Mix_LoadMUS("Music/OFallonsteinfeld");
	mSongs[Songs::SoundAndy] = Mix_LoadMUS("Music/SoundOfAndy.wav");
	mSongs[Songs::TakeAndy] = Mix_LoadMUS("Music/TakeOnAndy.wav");

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
	//std::cout << "OK " << mObjects.size() << std::endl;
	Object *obj = nullptr;
	for (int i = 0; i < mapWidth; i++)
		for (int j = 0; j < mapHeight; j++)
			if (mMap[i][j].enemy != 0)
			{
				obj = new Enemy(Enemies(mMap[i][j].enemy - 1), double(i) + .5, double(j) + .5);
				if (obj)
					mObjects.insertAtFront(obj);
			}
}
void Game::LoadMap(std::string mapName)
{
	std::string filepath = "./Maps/" + mapName + ".txt";
	std::ifstream infile(filepath);

	for(int k = 0; k < 4; k++)
	{
		for(int i = 0; i < 30; i++)
		{
			for(int j = 0; j < 30; j++)
			{
				std::string line;
				std::getline(infile, line, ',');

				if (line == "")
				{
					continue;
				}

				switch(k)
				{
					case 0:
						mMap[i][j].floor = std::stoi(line);
						break;
					case 1:
						mMap[i][j].wall = std::stoi(line);
						break;
					case 2:
						mMap[i][j].enemy = std::stoi(line);
						break;
					case 3:
						mMap[i][j].ceiling = std::stoi(line);
						break;
				}
			}
		}
	}

	std::cout << "Map Loaded" << std::endl;
}