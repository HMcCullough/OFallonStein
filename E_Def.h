//Shoutout to WL_DEF.H
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <exception>
#include <cmath>
#include <thread>
#include <SDL/SDL_mixer.h>
#include <climits>
#include <random>

#include "HelperClasses/Vector2.h"
#include "quickcg.h"

using namespace QuickCG;

#define GAMENAME "O'FALLONSTEIN 3D"

#define screenWidth 800
#define screenHeight 600

#define texWidth 64
#define texHeight 64

#define gunTexWidth 366
#define gunTexHeight 342

#define mapWidth 30
#define mapHeight 30

#define numTextures 50
#define numGunTextures 4
#define numSounds 3
#define numSongs 1

#define U32Size 4294967295 //all possible colors

//Enemy Info
#define SMALLHEALTH 1
#define MEDHEALTH 5
#define BIGHEALTH 10
#define BOSSHEALTH 100

#define SMALLDMG 1
#define MEDDMG 3
#define BIGDMG 5
#define BOSSDMG 10

#define FASTSPEED 5
#define MEDSPEED 3
#define SLOWSPEED 1
#define BOSSSPEED 2

typedef struct mapTile
{
	int floor;
	int object;
	int ceiling;
}mapTile;

enum Textures
{
	AndyWall, AndyCeiling, AndyWall2, AndyWall3,AndyWall4,AndyWall5,AndyWall6,AndyWall7,Ground,
	computer,computerFloor,computerCeiling,Comp4,Comp3,Comp2,

	caterpillar,caterpillarHurt,worm,workHurt,cock,cockHurt,grasshopper,grasshopperHurt,mosquito,
	mosquitoHurt,spider,spiderHurt,wasp,waspHurt,

	geek,happy,loser,mad,nerd,surprised,mad2,geek2,nerd2,sad2,loser3,mad3,sad3,verysad3,why,die,gameover, 

	GameLogo, UI
};

enum GunTextures
{
	Raid, RaidAnim1, RaidAnim2, RaidAnim3
};

enum Sounds
{
	DamageSound, WillhelmScream, ShootSound
};

enum Songs
{
	AndySong
};

enum Enemies
{
	Cockroach, Caterpillar, Grasshopper, Mosquito, Spider, Wasp, Worm, Boss
};

Vector2<int> Raycast(mapTile map[][mapHeight], Vector2<double> rayPos, Vector2<double> rayDir,	Vector2<double> &stepDir,
	int &hit, int &side);
double SqrDistFromPointToRay(Vector2<double> rayPoint1, Vector2<int> rayPoint2, Vector2<double> point);

int sgn(double val);

// playSound wraps _playSound in a new thread
void playSound(Mix_Chunk *sound);

// Bound to its own thread so that the sleep function can be called without halting the program
void _playSound(Mix_Chunk *sound);

//Same as above but using Mix_Music
void playSong(Mix_Music *sound);

void _playSong(Mix_Music *sound);

void BAD();
