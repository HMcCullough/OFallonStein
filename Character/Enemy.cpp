#include "Enemy.h"

Enemy::Enemy(int health, int damage, double speed, Vector2<double> pos, int texture) :
	Character(health, speed, 0, 0, 0, 0, texture)
{
	setPosition(pos);
	setDamage(damage);
	setCameraX(0);
	mShotTime = mOldShotTime = 0;
	mShootDelay = 40;
}

Enemy::Enemy(int health, int damage, double speed, double posX, double posY, int texture) :
	Character(health, speed, posX, posY, 0, 0, texture)
{
	setDamage(damage);
	setCameraX(0);
	mShotTime = mOldShotTime = 0;
	mShootDelay = 40;
}

Enemy::Enemy(const Enemies & enemy, double posX, double posY, std::vector<Mix_Chunk *>& soundlist) :
	Character(0, 0, posX, posY, 0, 0, 0)
{
	setPosition(posX, posY);
	switch(enemy)
	{
		case Enemies::eCockroach:
			setSpeed(FASTSPEED);
			setMaxHealth(SMALLHEALTH);
			setDamage(SMALLDMG);
			setTexture(Textures::cock);
			setHurtTexture(Textures::cockHurt);
			setDamageSound(soundlist[Sounds::Cockroach]);
			setDeathSound(soundlist[Sounds::CockroachDeath]);
			break;
		case Enemies::eCaterpillar:
			setSpeed(MEDSPEED);
			setMaxHealth(MEDHEALTH);
			setDamage(MEDDMG);
			setTexture(Textures::caterpillar);
			setHurtTexture(Textures::caterpillarHurt);
			setDeathSound(soundlist[Sounds::Caterpillar]);
			break;
		case Enemies::eGrasshopper:
			setSpeed(FASTSPEED);
			setMaxHealth(SMALLHEALTH);
			setDamage(SMALLDMG);
			setTexture(Textures::grasshopper);
			setHurtTexture(Textures::grasshopperHurt);
			setDeathSound(soundlist[Sounds::Grasshopper]);
			break;
		case Enemies::eMosquito:
			setSpeed(FASTSPEED);
			setMaxHealth(SMALLHEALTH);
			setDamage(BIGDMG);
			setTexture(Textures::mosquito);
			setHurtTexture(Textures::mosquitoHurt);
			setDamageSound(soundlist[Sounds::Mosquito]);
			setDeathSound(soundlist[Sounds::MosqDeath]);
			break;
		case Enemies::eSpider:
			setSpeed(FASTSPEED);
			setMaxHealth(BIGHEALTH);
			setDamage(BIGDMG);
			setTexture(Textures::spider);
			setHurtTexture(Textures::spiderHurt);
			setDeathSound(soundlist[Sounds::Spider]);
			break;
		case Enemies::eWasp:
			setSpeed(FASTSPEED);
			setMaxHealth(MEDHEALTH);
			setDamage(BIGDMG);
			setTexture(Textures::wasp);
			setHurtTexture(Textures::waspHurt);
			setDamageSound(soundlist[Sounds::Wasp]);
			setDeathSound(soundlist[Sounds::WaspDead]);
			break;
		case Enemies::eWorm:
			setSpeed(SLOWSPEED);
			setMaxHealth(MEDHEALTH);
			setDamage(MEDDMG);
			setTexture(Textures::worm);
			setHurtTexture(Textures::wormHurt);
			setDamageSound(soundlist[Sounds::Worm2]);
			setDeathSound(soundlist[Sounds::Worm]);
			break;
		case Enemies::eBoss:
			setSpeed(BOSSSPEED);
			setMaxHealth(BOSSHEALTH);
			setDamage(BOSSDMG);
			setTexture(Textures::geek);
			break;
		default:
		break;
	}

	mShotTime = mOldShotTime = 0;
	mShootDelay = 40;
}

int Enemy::getDamage() const { return mDamage; }
void Enemy::setDamage(const int &damage) { mDamage = damage; }

bool Enemy::isVisible() const { return mIsVisible; }
void Enemy::setVisibility(const bool &visibility) { mIsVisible = visibility; }

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

	if(getHealth() < getMaxHealth() / 2)
	{
		setTexture(getHurtTexture());
	}
}

void Enemy::Shoot()
{
	mOldShotTime = mShotTime;
	mShotTime += mShootDelay;
}

bool Enemy::CanShoot()
{
	return mOldShotTime++ > mShotTime;
}

void Enemy::Die()
{
	playSound(mDeathSound);
	mIsDead = true;
}

void Enemy::setHurtTexture(int texture)
{
	mHurtTexture = texture;
}

int Enemy::getHurtTexture(){return mHurtTexture;}

/*void Enemy::setBossTauntSound(std::vector<Mix_Chunk *>& soundlist)
{

}*/
