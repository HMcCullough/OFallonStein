#pragma once
#include "../E_Def.h"

//An Object is the master type for physical world objects
class Object
{
public:
	Object(double posX, double posY, double directionX, double directionY, int texture, bool rotates = true);
	Object(Vector2<double> pos, Vector2<double> dir, int texture, bool rotates = true);

	Vector2<double> getDirection() const;
	Vector2<double> getPosition() const;
	int getTexture() const;
	bool rotates() const;

	void setDirection(const Vector2<double> &dir);
	void setDirection(const double &dirX, const double &dirY);

	void setPosition(const Vector2<double> &pos);
	void setPosition(const double &posX, const double &posY);

	void setTexture(const int &texture);
	void setRotation(const bool &rotates);

	virtual void Move(double x, double y) = 0;

protected:
	Vector2<double>  mPosition, mDirection;
	int  mTexture; //For reference to the enum
	bool mRotates;
};
