#include "Projectile.h"

Projectile::Projectile(double posX, double posY, double directionX, double directionY, double speed, int damage, int texture):
	Object(posX, posY, directionX, directionY, texture, false)
{
	mDamage = damage;
	mSpeed = speed;
	mPreviousPosition = Vector2<double>(posX, posY);
}

Projectile::Projectile(Vector2<double> pos, Vector2<double> dir, double speed, int damage, int texture):
	Object(pos, dir, texture, false)
{
	mDamage = damage;
	mSpeed = speed;
	mPreviousPosition = pos;
}

int Projectile::getDamage(){return mDamage;}
void Projectile::setDamage(int newDamage){mDamage = newDamage;}

double Projectile::getSpeed() {return mSpeed;}
void Projectile::setSpeed(double newSpeed){mSpeed = newSpeed;}

void Projectile::setHitLocation(const Vector2<int> &hit) { mHitLocation = hit; }

bool Projectile::HasHit()
{
	if 		(mPreviousPosition.x < mHitLocation.x && mPosition.x > mHitLocation.x)
		return true;
	else if (mPreviousPosition.x > mHitLocation.x && mPosition.x < mHitLocation.x)
		return true;
	else if (mPreviousPosition.y < mHitLocation.y && mPosition.y > mHitLocation.y)
		return true;
	else if (mPreviousPosition.y > mHitLocation.y && mPosition.y < mHitLocation.y)
		return true;
}

void Projectile::Move(Vector2<double> dir) { Move(dir.x, dir.y); }
void Projectile::Move(double x, double y) // Direction
{
	if (x != mDirection.x || y != mDirection.y)
		setDirection(x, y);
	mPreviousPosition = mPosition;
	setPosition(mPosition + mSpeed * mDirection);
}