#include "Enemy.h"

Enemy::Enemy(int health, int damage, double speed, Vector2<double> pos, int texture) :
	Character(health, speed, 0, 0, 0, 0, texture)
{
	setPosition(pos);
	setDamage(damage);
	setCameraX(0);
}

Enemy::Enemy(int health, int damage, double speed, double posX, double posY, int texture) :
	Character(health, speed, posX, posY, 0, 0, texture)
{
	setDamage(damage);
	setCameraX(0);
}

Enemy::Enemy(const Enemies & enemy, double posX, double posY) :
	Character(0, 0, posX, posY, 0, 0, 0)
{
	setPosition(posX, posY);
	switch(enemy)
	{
		case Enemies::Cockroach:
			setSpeed(FASTSPEED);
			setHealth(SMALLHEALTH);
			setDamage(SMALLDMG);
			setTexture(Textures::cock);
			break;
		case Enemies::Caterpillar:
			setSpeed(MEDSPEED);
			setHealth(MEDHEALTH);
			setDamage(MEDDMG);
			setTexture(Textures::caterpillar);
			break;
		case Enemies::Grasshopper:
			setSpeed(FASTSPEED);
			setHealth(SMALLHEALTH);
			setDamage(SMALLDMG);
			setTexture(Textures::grasshopper);
			break;
		case Enemies::Mosquito:
			setSpeed(FASTSPEED);
			setHealth(SMALLHEALTH);
			setDamage(BIGDMG);
			setTexture(Textures::mosquito);
			break;
		case Enemies::Spider:
			setSpeed(FASTSPEED);
			setHealth(BIGHEALTH);
			setDamage(BIGDMG);
			setTexture(Textures::spider);
			break;
		case Enemies::Wasp:
			setSpeed(FASTSPEED);
			setHealth(MEDHEALTH);
			setDamage(BIGDMG);
			setTexture(Textures::wasp);
			break;
		case Enemies::Worm:
			setSpeed(SLOWSPEED);
			setHealth(MEDHEALTH);
			setDamage(MEDDMG);
			setTexture(Textures::worm);
			break;
		case Enemies::Boss:
			setSpeed(BOSSSPEED);
			setHealth(BOSSHEALTH);
			setDamage(BOSSDMG);
			setTexture(Textures::geek);
			break;
		default:
		break;
	}
}

int Enemy::getDamage() const { return mDamage; }
void Enemy::setDamage(const int &damage) { mDamage = damage; }

bool Enemy::isVisible() const { return mIsVisible; }
void Enemy::setVisibility(const bool &visibility) { mIsVisible = visibility; }

bool Enemy::canSeePlayer() const { return mCanSeePlayer; }
void Enemy::setPlayerVisibility(const bool &canSeePlayer) { mCanSeePlayer = canSeePlayer; }

int Enemy::getCameraX() const
{
	return mCameraX;
}

void Enemy::setCameraX(const int &cameraX)
{
	mCameraX = cameraX;
}

void Enemy::TakeDamage(int damage)
{
	setHealth(getHealth() - damage);
	if (getHealth() <= 0) { Die(); }
	else { playSound(mDamageSound); }
}

void Enemy::Shoot()
{
}

void Enemy::Die()
{
	playSound(mDeathSound);
	mIsDead = true;
}
