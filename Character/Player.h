#pragma once
#include "Character.h"
#include "../Objects/Gun.h"

class Player : public Character
{
public:
	// Constructors
	Player();
	Player(int health, int armor, int battery, double speed, double posX = 0.0, double posY = 0.0, double dirX = 0.0, double dirY = 0.0,
		   double cameraX = 0.0, double cameraY = 0.0);
	Player(int health, int armor, int battery, double speed, Vector2<double> pos, Vector2<double> dir, Vector2<double> camera);

	// Accessors
	// Getters
	Vector2<double> getCameraPlane() const;
	int getHealth() const;
	int getArmor() const;
	int getBattery() const;
	int getAmmo() const;
	Gun &getCurrentGun();

	// Setters
	void setCameraPlane(const Vector2<double> &cam);
	void setCameraPlane(const double &camX, const double &camY);

	void setHealth(const int &health);
	void setArmor(const int &armor);
	void setBattery(const int &battery);
	void setAmmo(const int &ammo);

	// Member Functions
	void TakeDamage(int damage) override;
	void Rotate(double rotSpeed);
	void Shoot() override;
	void AddGun(Vector2<int> screenPos, int damage, int shotDelay, int defaultTexture);
	void AddGun(int screenX, int screenY, int damage, int shotDelay, int defaultTexture);
	Mix_Chunk* PlayQuip(std::vector<Mix_Chunk*> & mSounds);

private:
	Vector2<double> mCameraPlane;

	int mArmor, mBattery, mCurrentGun, mAmmo;
	std::vector<Gun> mGuns;

	void Die();
};
