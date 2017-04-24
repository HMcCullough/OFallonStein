#include "Projectile.h"

Projectile(double posX, double posY, double directionX, double directionY, double speed, int damage, int texture):
	Object(posX, posY, directionX, directionY, texture, false)
{
	mDamage = damage;
	mSpeed = speed;
}

Projectile(Vector2<double> pos, Vector2<double> dir, double speed, int damage, int texture):
	Object(pos, dir, texture, false)
{
	mDamage = damage;
	mSpeed = speed;
}

int getDamage(){return mDamage;}
void setDamage(int newDamage){mDamage = newDamage;}

double getSpeed() {return mSpeed;}
void setSpeed(double newSpeed){mSpeed = newSpeed;}