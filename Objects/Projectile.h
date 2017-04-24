#pragma once

#include "Object.h"

class Projectile : public Object
{
public:
	Projectile(double posX, double posY, double directionX, double directionY, double speed, int damage, int texture);
	Projectile(Vector2<double> pos, Vector2<double> dir, double speed, int damage, int texture);

	int getDamage();
	void setDamage(int newDamage);

	double getSpeed();
	void setSpeed(double newSpeed);
private:
	int mDamage;	
	double mSpeed;
};