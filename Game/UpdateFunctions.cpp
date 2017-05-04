#include "Game.h"
#include "../Menu/Menu.h"

// Number generators for the random pause menu background
std::default_random_engine gen;
std::uniform_int_distribution<int> dis(0,U32Size), dirDis(8,24);

// Handles user input and turns it into a movement vector
void Game::UpdateMovement()
{
	double moveSpeed = mFrameTime * 4.5; 		 // The constant value is in squares/second
	bool collides = false;						 // Stores whether or not the player collided with a wall
	Vector2<double> velocity,					 // Holds the direction and amount to move by
					newMapPos,					 // Holds the new position in the world
					pos = mPlayer.getPosition(), // Holds the player's position for reference
					dir = mPlayer.getDirection(),// Holds the player's current looking direction in world coordinates
					pDir(-dir.y, dir.x);		 // Vector perpendicular to the direction vector, calculated using a rotation matrix (note that it points to the left of the facing vector)

	// If the forward keys are pressed then we add the forward vector to the velocity
	if (keyDown(SDLK_w) || keyDown(SDLK_UP))
	{
		velocity.y += dir.y;
		velocity.x += dir.x;
	}
	// If the backwards keys are pressed then we subtract the forward vector from the velocity
	if (keyDown(SDLK_s) || keyDown(SDLK_DOWN))
	{
		velocity.y -= dir.y;
		velocity.x -= dir.x;
	}
	// If the move right key is pressed then we subtract the left prependicular vector from the velocity
	if (keyDown(SDLK_d))
	{
		velocity.y -= pDir.y;
		velocity.x -= pDir.x;
	}
	// If the move left key is pressed then we add the left perpendicular vector to the velocity
	if (keyDown(SDLK_a))
	{
		velocity.y += pDir.y;
		velocity.x += pDir.x;
	}

	// Do nothing if the player has not moved
	if (velocity.x != 0 && velocity.y != 0)
	{
		// Normalize the vector so that the magnitude is 1 and can be scaled by our speed
		velocity.normalize();
		velocity = moveSpeed * velocity;

		// If either shift or sprint key is pressed then scale the speed accordingly
		if(keyDown(SDLK_LSHIFT) || keyDown(SDLK_RSHIFT))
		{
			velocity = 1.75 * velocity;
		}

		// Set the new map position for testing
		newMapPos = pos + velocity;

		// Loop through a 3x3 square around the new position to check if there were any collsions (increasing 0.075 will increase the distance of collision checking)
		for (int i = -1; i <= 1 && !collides; ++i)
		{
			for (int j = -1; j <= 1 && !collides; ++j)
			{
				Vector2<double> check(i, j);
				check.normalize();

				if(newMapPos.x + check.x * .075 < mapWidth  && newMapPos.x + check.x * .075 >= 0 &&
				   newMapPos.y + check.y * .075 < mapHeight && newMapPos.y + check.y * .075 >= 0 &&
				   mMap[int(newMapPos.x + check.x * .075)][int(newMapPos.y + check.y * .075)].wall != false)
				   collides = true;
			}
		}

		if(!collides)
		{
			mPlayer.Move(newMapPos.x, newMapPos.y); /// Move the player to the new position if there were no collsion issues
		}
		else
		{
			// If there was a collision we still want to slide up against a wall
			velocity.normalize();
			double oldVelX = velocity.x;
			if (mMap[int(pos.x)][int(pos.y + velocity.y)].wall == false) // First we check if the y component collides
				velocity.x = 0;									  // If it doesn't then we know that it was the x component that caused collision we it is set to 0
			if (mMap[int(pos.x + oldVelX)][int(pos.y)].wall == false) // Then we check if the x component collides, note that modifying the x above does not affect the x here
				velocity.y = 0;									  // If it doesn't collide then we know the y component caused collision and can be removed
			if (mMap[int(pos.x + velocity.x)][int(pos.y + velocity.y)].wall == false) // Finally if the new position is open, the player moves there 
				mPlayer.Move(pos.x + 0.1 * velocity.x, pos.y + 0.1 * velocity.y);
		}
	}
}

void Game::UpdateRotation(float deltaMouse)
{
	// Speed modifiers
	double rotSpeed = mFrameTime * 2.5 * (deltaMouse != 0 ? 2 : 1); // The constant value is in radians/second

	// If the player wants to rotate to the right then we negate the speed
	if (keyDown(SDLK_RIGHT))
		rotSpeed *= -1;
	// Otherwise if the player wants to rotate to the left then we do not change the speed
	else if (keyDown(SDLK_LEFT))
		rotSpeed *= 1;
	// Finally if the player has not pressed anything the speed is set to 0
	else
		rotSpeed = 0;

	// The player then rotates by the amount preciously specified
	mPlayer.Rotate(rotSpeed);
}

void Game::CheckShoot()
{
	// Get the current gun and update it for animations
	Gun &gun = mPlayer.getCurrentGun();
	gun.update();

	// If the player presses a shoot button and the cooldown is finished and the player has ammo
	if ((keyDown(SDLK_RCTRL) || keyDown(SDLK_LCTRL)) && gun.canShoot() && mPlayer.getAmmo() > 0)
	{
		// Call PlayQuip which will randomly pick an Andy sound to play, then begin gun shooting animation
		//playSound(mPlayer.PlayQuip(mSounds));
		mPlayer.Shoot();

		// Iterate through the objects list
		for (int i = 0; i < mObjects.size(); ++i)
		{
			Object *obj = mObjects.at(i);
			Enemy *e = dynamic_cast<Enemy*>(obj);

			/* Check the following things for shot success:
			 		1) Check if the object is an enemy
					2) Check if the enemy is visible
					3) Check if some part of the enemy intersects the center of the screen
					4) Check if the enemy is within shot range*/
			if (e != nullptr && e->isVisible() &&
				e->getCameraX() == 0 &&
				(obj->getPosition() - mPlayer.getPosition()).getSqrMagnitude() < 50)
			{
				// If the object is an enemy then send damage and check if it died
				e->TakeDamage(gun.getDamage());
				if (e->isDead())
				{
					// If it died, reward ammo to the player (max at 100)
					mPlayer.setAmmo(mPlayer.getAmmo() + e->getMaxHealth()/2);
					if(mPlayer.getAmmo() >= 100) mPlayer.setAmmo(100);

					// Remove enemy from the list and decrement mNumEnemies
					mObjects.deleteAt(i);
					mNumEnemies--;
				}
			}
		}

		// Decrement the ammo count
		mPlayer.setAmmo(mPlayer.getAmmo() - 1);
	}

	// Continue the gun animation if it is still shooting
	if (gun.isShooting())
		gun.animate();

	// Check Enemies' shoot
	for (int i = 0; i < mNumEnemies; i++)
	{
		// Check if the current object is an enemy that can shoot (cooldown permitting)
		Enemy *e = dynamic_cast<Enemy *>(mObjects.at(i));
		if (e != nullptr && e->CanShoot())
		{
			// Begin the enemies shoot logic - reset the cooldown
			e->Shoot();

			Object *proj = nullptr;
			if (mIsBossLevel) // If this is a boss level then spawn slower bullets
				proj = new Projectile(e->getPosition(), mPlayer.getPosition() - e->getPosition(), 0.1, e->getDamage(), Textures::breakpoint);
			else
			{
				// If this is not a boss level then spawn faster bullets
				proj = new Projectile(e->getPosition(), mPlayer.getPosition() - e->getPosition(), SLOWSPEED/3.0, e->getDamage(), Textures::breakpoint);

				Vector2<double> stepDir; // Represents the signs of the direction vector components
				int side, hit = 0;		 // Side holds what side the wall was hit on and hit holds whether there was a hit at all

				// We raycast from the spawn position of the bullet to see where it hits on the map and then store the stepDir info in the projectile
				dynamic_cast<Projectile*>(proj)->setHitLocation(Raycast(mMap, proj->getPosition(), proj->getDirection(), stepDir, hit, side));
				dynamic_cast<Projectile*>(proj)->setStepDir(stepDir);
			}

			// Finally we insert the projectile at the end of the object list and increment the count
			mObjects.insertAtEnd(proj);
			mNumProjectiles++;
		}
	}
}


void Game::CheckQuit()
{
	// Can quit game by pressing '1'
	if (keyDown(SDLK_1))
		mQuit = true;
}

//replaces CheckQuit because pause now quits too
void Game::CheckPause()
{
	mPause = keyPressed(SDLK_ESCAPE);

	if (mPause)
	{
		int mx, my;
		//std::cout << "pause" << std::endl;

		Button ResumeButton(Vector2<double>(screenWidth/2 - 350, screenHeight/2 + 100),  nullptr, "Textures/UI/Resume.png");
		Button InfoButton(Vector2<double>(screenWidth/2 - 75, screenHeight/2 + 100), &ShowInfo, "Textures/UI/Info.png");
		Button ExitButton(Vector2<double>(screenWidth/2 + 150, screenHeight/2 + 100), nullptr, "Textures/UI/Exit.png");

		SDL_Event event;

		//YOU CAN OVERLOAD PARANTHESES
		Uint32 coolMod = gen();
		Uint32 coolMod2 = gen();
		int mod = gen();
		Uint32 colorOffset = dis(gen);
		//determines direction of lines
		Uint32 dir = dirDis(gen);
		Uint32 dir2 = dirDis(gen);
		
		//used for converting back and forth
		ColorRGB color;
		Uint32 colorI;

		//pause background
		//settled on fractal-like function that emulates DOS color depth sort of thing
		for (int i = 0; i < screenWidth; ++i)
		for (int j = 0; j < screenHeight; ++j)
		{
			//converts random num to color struct
			color = INTtoRGB((( i/dir * (coolMod % mod) + j/dir2 * (coolMod2 % mod)) + colorOffset) / 4);
			//black and white
			color.r = color.b;
			color.g *= 2;
			color.b = color.b;
			//converts back for printing to screen
			colorI = RGBtoINT(color);
			mBuffer[j][i] = colorI;
		}

		while (mPause)
		{
			//std::cout << "in loop" << std::endl;

			//used for button logic
			SDL_GetMouseState(&mx, &my);
			SDL_PollEvent(&event);

			readKeys();
			
			//this is where buttons logic should go
			ResumeButton.OnHover(mx, my);
			InfoButton.OnHover(mx, my);
			ExitButton.OnHover(mx, my);

			if (keyDown(SDLK_1))
				mQuit = true;

			if( event.type == SDL_MOUSEBUTTONUP )
			{	
				SDL_PollEvent(&event);
				InfoButton.OnClick(mx, my);
				if (ResumeButton.OnClick(mx, my))
					mPause = false;
				if (ExitButton.OnClick(mx, my))
					{mQuit = true; mPause = false;};
			}
			
			if (keyPressed(SDLK_ESCAPE))
			{ 
				//std::cout << "unpause" << std::endl;
				mPause = false;
			}

			SDL_ShowCursor(1);
			drawBuffer(mBuffer[0]);

			// Draws all of the buttons to screen
			ResumeButton.Draw();
			InfoButton.Draw();
			ExitButton.Draw();
		
			redraw();
		}
	}
}

bool Game::CheckWin()
{
	// If all enemies are dead and no bullets are currently present then the player wins
	if(mObjects.size() == 0)
		return true;

	// Pressing 2 also causes a win
	if (keyDown(SDLK_2))
	{
		sleep(1);
		return true;
	}

	return false;
}

void Game::CheckHit()
{
	// Only begin checking if there are projectiles to check
	if (mNumProjectiles > 0)
	{
		// We begin at mNumEnemies since enemies are the only other things in the world so we can skip checking all of the enemies
		for (int i = mNumEnemies; i < mObjects.size(); ++i)
		{
			// We check the type of the current item to confirm it is a projectile
			Projectile *obj = dynamic_cast<Projectile *>(mObjects.at(i));
			if (obj)
			{
				if (!mIsBossLevel)
					obj->Move(obj->getDirection()); // If it is not a boss level then the projectiles move in the same direction as always
				else
					obj->Move(mPlayer.getPosition() - obj->getPosition()); // If it is a boss level then the projectile will track the player (calculates the vector from the projectile to the player)
				Vector2<double> pos = obj->getPosition(); // Stores the new position of the projectile

				if (pos.x > mapWidth || pos.x < 0 ||			// If the position is out of the x-bounds
				 	pos.y > mapHeight || pos.y < 0 ||			// Or the position is out of the y-bounds
					mMap[int(pos.x)][int(pos.y)].wall != 0 ||	// Or the position is in a wall
					(obj->HasHit() && !mIsBossLevel))			// Or the projectile has passed it's hit position
				{
					// Then delete the projectile and decrement mNumProjectiles
					mObjects.deleteAt(i);
					mNumProjectiles--;
				}
				else if (obj->getPosition().distanceTo(mPlayer.getPosition()) < 0.6) // Otherwise check if the distance to the player is within range
				{
					// If the projectile is within range of the player then we send damage to the player and
					// then we delete the projectile and decrement mNumProjectiles
					mPlayer.TakeDamage(obj->getDamage());
					mObjects.deleteAt(i);
					mNumProjectiles--;
				}
			}
		}
	}
}

void Game::CheckPickup()
{
	for (int i = mNumEnemies; i < mObjects.size(); ++i)
	{
		Pickup *pickup = dynamic_cast<Pickup *>(mObjects.at(i));
		if (pickup != nullptr && (pickup->getPosition() - mPlayer.getPosition()).getSqrMagnitude() < 0.25)
		{
			mPlayer.setHealth(mPlayer.getHealth() + pickup->getHealAmount());
			mObjects.deleteAt(i);
		}
	}
}
