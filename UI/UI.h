#pragma once

#include "../E_Def.h"

class Button
{
public:
	Button(Vector2<double> upperLeft, void (* action)(), std::string filename);
	double getUpX() {return mUpperLeft.x;}
	double getUpY() {return mUpperLeft.y;}				//Upper left and bottom right bounds for a button
	double getLowX() {return mLowerRight.x;}
	double getLowY() {return mLowerRight.y;}
	bool OnClick(int clickx, int clicky);//Uses function ptr to define what a button does when pressed
	bool OnHover(int clickx, int clicky);//Used for hover animation
	void Draw();//Draws button
private:
	Vector2<double> mUpperLeft, mLowerRight;
	void (*Do)() = nullptr;

	//the sprite
	std::vector<Uint32> mSprite;
	std::vector<Uint32> mHoverSprite;

	bool mHover;
	long unsigned int mWidth;
	long unsigned int mHeight;
};
