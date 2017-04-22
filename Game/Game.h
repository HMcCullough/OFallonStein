#pragma once

#include "../E_Def.h"
#include "../Character/Player.h"
#include "../Character/Enemy.h"
#include "../HelperClasses/List.h"

typedef struct sprite
{
	double x, y;
	int texture;
} Sprite;

//#define numSprites 1

class Game
{
public:
	Game(int width = screenWidth, int height = screenHeight);

	~Game();

	int getWidth() const { return mScreenWidth; }
	int getHeight() const { return mScreenHeight; }

	void setWidth(const int width) { mScreenWidth = width; }
	void setHeight(const int height) { mScreenHeight = height; }

	void RunGame(std::string mapName);
private:
	Player mPlayer;
	double mFrameTime;
	int mScreenWidth, mScreenHeight;
	std::vector<Uint32> mTextures[numTextures];
	std::vector<Uint32> mUI;
	std::vector<Uint32> mGUN[4];
	std::vector<Mix_Chunk *> mSounds;
	Uint32 mBuffer[screenHeight][screenWidth];
	int curGunFrame = 0;
	bool isShooting;
	int ticks;
	int oldTicks;

	// Cooldown
	double cooldown;

	//1D Zbuffer
	double mZBuffer[screenWidth];

	//arrays used to sort the sprites
	//int spriteOrder[numSprites];
	//double spriteDistance[numSprites];

	// Keeps track on whether the user has pressed escape
	bool mQuit;

	mapTile mMap[mapWidth][mapHeight];

	List<Enemy>  mEnemies;
	List<Object *> mDoors,
			  	   mPickups;

	//function used to sort the sprites
	void combSort(std::vector<int> &order, std::vector<double> &dist, int amount);

	void LoadMap(std::string mapName);
	void LoadEnemies(std::string mapName);
	void LoadSounds();
	void LoadTextures();

	void Render();
	void CheckQuit();

	void DrawSprites();

	void AnimateGun();
	void DrawUI();

	void UpdateMovement();
	void UpdateRotation(float deltaMouse);
	void CheckShoot();
};
