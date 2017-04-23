#include "UI.h"

#define buttonWidth 400
#define buttonHeight 200

Button::Button(Vector2<double> upperLeft, void (* action)(), std::string filename)//, std::string hFilename)
{
	mUpperLeft.x = upperLeft.x; mUpperLeft.y = upperLeft.y;
	Do = action;
	bool success;
	
	mHover = false;

	//widens that sprite. ready to accept
	mSprite.resize(buttonWidth * buttonHeight);

	success |= loadImage(mSprite, mWidth, mHeight, filename);
	//success |= loadImage(mHoverSprite, mWidth, mHeight, hFilename);

	if (success)
	{
		std::cout << "Button image loaded" <<std::endl;
	}

	//sets bounds of button for mouse collision later
	mLowerRight.x = mUpperLeft.x + mWidth;
	mLowerRight.y = mUpperLeft.y + mHeight;
}

bool Button::OnClick(int clickx, int clicky)
{
	//debug garbage
	//std::cout << "r: " << mLowerRight.x << " l:" << mUpperLeft.x << "d: " << mLowerRight.y << "u: " << mUpperLeft.y << std::endl;

	//if click passed in is within button bounds, call function
	if (clickx < mLowerRight.x && clickx > mUpperLeft.x
	&& clicky < mLowerRight.y && clicky > mUpperLeft.y)
	{
		if (Do != nullptr)
			Do();
		return true;
	}

	return false;
}

bool Button::OnHover(int hoverx, int hovery)
{
	if (hoverx < mLowerRight.x && hoverx > mUpperLeft.x
	&& hovery < mLowerRight.y && hovery > mUpperLeft.y)
	{
		mHover = true;
		return true;
	}
	mHover = false;
	return false;
}

void Button::Draw()
{	
	ColorRGB color;

	for (int y = 0; y < mHeight; ++y)
	for (int x = 0; x < mWidth; ++x)
	{
		if (!mHover)
		{
			//picks out non-transparent pixels
			if ((mSprite[y * mWidth + x] & 0xFF000000) != 0)
				pset(x + mUpperLeft.x, y + mUpperLeft.y, INTtoRGB(mSprite[y * mWidth + x]));
		}
		else if (mHover)
		{
			if ((mSprite[y * mWidth + x] & 0xFF000000) != 0)
			{
				//Hunter's ridiculous solution
				//uses unreadable code from some website
				//color = INTtoRGB((mSprite[y * mWidth + x] << 1) & 8355711);

				//Ryan's good solution
				//divides all colors by two to darken image
				color = INTtoRGB((mSprite[y * mWidth + x]));
				color.r /= 2;
				color.g /= 2;
				color.b /= 2;
				pset(x + mUpperLeft.x, y + mUpperLeft.y, color);
			}
		}
	}
}