#include "Object.h"

class Pickup : public Object
{
public:
    Pickup(double posX, double posY, int texture, int heal, int arm);

    int getHealAmount() const;
    int getArmAmount()  const;

    void setHealAmount(const int &heal);
    void setArmAmount(const int &arm);

    void Move(double x, double y);

private:
    int mHealAmount,
        mArmAmount;
};