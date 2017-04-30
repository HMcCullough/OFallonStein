#pragma once

#include "../E_Def.h"
#include "../Character/Player.h"
#include "../Character/Boss.h"
#include "../Objects/Projectile.h"
#include "../HelperClasses/List.h"
#include "../Cutscene/Cutscene.h"

#include "../UI/UI.h"

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

	void setPlayerPos(double posX, double posY);

	void RunGame();
	void Play(std::string mapName, Songs song);

	bool mQuit;
private:
	Player mPlayer;
	double mFrameTime;
	int mScreenWidth, mScreenHeight;
	std::vector<Uint32> mTextures[numTextures],
						mGuns[numGunTextures],
						mUI;
	std::vector<Mix_Chunk *> mSounds;
	std::vector<Mix_Music *> mSongs;
	Uint32 mBuffer[screenHeight][screenWidth];

	//1D Zbuffer
	double mZBuffer[screenWidth];

	// Keeps track on whether the user has pressed escape
	bool mPause;

	bool mMini;

	mapTile mMap[mapWidth][mapHeight];

	List<Object*>  mObjects;
	int mNumProjectiles;
	int mNumEnemies;
	bool mIsBossLevel;

	//function used to sort the sprites
	void combSort(std::vector<int> &order, std::vector<double> &dist, int amount);

	void InitBoss(double posX, double posY);
	void InitPlayer();
	void LoadMap(std::string mapName);
	void LoadEnemies(std::string mapName);
	void LoadSounds();
	void LoadTextures();

	void Render();
	void DrawCrosshair();
	void PrintHUD();
	
	void CheckHit();
	void CheckQuit();
	void CheckPause();
	bool CheckWin();
	void CheckShoot();

	void DrawSprites();
	void DrawUI();
	void DrawMap();

	void UpdateMovement();
	void UpdateRotation(float deltaMouse);
};
