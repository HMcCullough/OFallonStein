#include "Character.h"

// Constructors
Character::Character(int health, double speed, double posX, double posY, double directionX, double directionY, int texture) :
	Object(posX, posY, directionX, directionY, texture, true)
{
	setHealth(health);
	setSpeed(speed);
	mIsDead = false;
}

Character::Character(int health, double speed, Vector2<double> pos, Vector2<double> dir, int texture) :
	Object(pos, dir, texture, true)
{
	setHealth(health);
	setSpeed(speed);
}

// Destructor
Character::~Character()
{
}

// Getters
int Character::getHealth() const { return mHealth; }
double Character::getSpeed() const { return mSpeed; }
int Character::getMaxHealth(){return mMaxHealth;}

//Setters
void Character::setMaxHealth(const int &maxHealth) { mMaxHealth = maxHealth; mHealth = maxHealth;}
void Character::setHealth(int health) { mHealth = health; }
void Character::setSpeed(double speed) { mSpeed = speed; }

void Character::setDamageSound(Mix_Chunk *damageSound) { mDamageSound = damageSound; }
void Character::setTauntSound(Mix_Chunk *tauntSound) { mTauntSound = tauntSound; }
void Character::setDeathSound(Mix_Chunk *deathSound) { mDeathSound = deathSound; }
void Character::setShootSound(Mix_Chunk *shootSound) { mShootSound = shootSound; }

bool Character::isDead() { return mIsDead; }

void Character::Move(double x, double y)
{
	setPosition(x, y);
}
