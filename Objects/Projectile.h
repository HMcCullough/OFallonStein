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

	void setHitLocation(const Vector2<int> &hit);
	void setStepDir(const Vector2<double> &stepDir);

	bool HasHit();

	void Move(Vector2<double> dir);
	void Move(double x, double y);

private:
	int mDamage;	
	double mSpeed;
	Vector2<double> mPreviousPosition,
					mStepDir;
	Vector2<int>    mHitLocation;
};