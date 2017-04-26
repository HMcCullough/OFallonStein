#pragma once
#include "../E_Def.h"
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(int health, int damage, double speed, Vector2<double> pos, int texture);
	Enemy(int health = 0, int damage = 0, double speed = 0, double posX = 0.0, double posY = 0.0, int texture = 0);
	Enemy(const Enemies & enemy, double posX, double posY, std::vector<Mix_Chunk *>& soundlist);

	int getDamage() const;
	void setDamage(const int &damage);

	bool isVisible() const;
	void setVisibility(const bool &visibility);

	int getCameraX() const;
	void setCameraX(const int &cameraX);

	virtual void TakeDamage(int damage);
	virtual void Shoot();
	bool CanShoot();

	//void Enemy::setBossTauntSound(); //For the boss sounds

protected:
	int mDamage,
		mCameraX,
		mShotTime, mOldShotTime,
		mShootDelay;
	bool mIsVisible;

	virtual void Die();
};
