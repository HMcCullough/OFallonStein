#include "Pickup.h"

Pickup::Pickup(double posX, double posY, int texture, int heal, int arm) :
    Object(posX, posY, 0, 0, texture)
{
    mHealAmount = heal;
    mArmAmount  = arm;
}

int Pickup::getHealAmount() const { return mHealAmount; }
int Pickup::getArmAmount()  const { return mArmAmount; }

void Pickup::setHealAmount(const int &heal) { mHealAmount = heal; }
void Pickup::setArmAmount(const int &arm) { mArmAmount = arm; }

void Pickup::Move(double x, double y)
{
}