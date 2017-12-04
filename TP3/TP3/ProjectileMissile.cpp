#include "ProjectileMissile.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

ProjectileMissile::ProjectileMissile(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, int nbAnimation, float vitesseMax, float accelerationParSeconde,  Vector2f position, Vector2f direction) : Projectile(animationProjectileSprite, animationProjectileExplodingSprite, nbAnimation, vitesseMax, accelerationParSeconde, position, direction)
{

}


ProjectileMissile::~ProjectileMissile()
{

}

void ProjectileMissile::Update()
{
	if (state == moving)
	{
		if (remainingTimeBeforeChangeDirection <= 0)
		{
			direction.y *= -1;
			remainingTimeBeforeChangeDirection = TIME_BEFORE_EACH_DIRECTION_CHANGE;
		}
		velocity.x += direction.x * (accelerationParSeconde / 60);
		velocity.y += direction.y * (accelerationParSeconde*4 / 60);

		if (velocity.x > vitesseMax)
		{
			velocity.x = vitesseMax;
		}
		else if (velocity.x < -vitesseMax)
		{
			velocity.x = -vitesseMax;
		}

		if (velocity.y > vitesseMax*2)
		{
			velocity.y = vitesseMax*2;
		}
		else if (velocity.y < -vitesseMax*2)
		{
			velocity.y = -vitesseMax*2;
		}

		position.x += velocity.x;
		position.y += velocity.y;
		rotation = (atan(velocity.y / velocity.x) * (180.0 / M_PI));

		if (startFrame > 0)
		{	
			--startFrame;
			if (startFrame == 0)
			{
				direction.y = -1;
			}
		}
		else
		{
			--remainingTimeBeforeChangeDirection;
		}
		
	}

	
	UpdateAnimation();
}

void ProjectileMissile::UpdateAnimation()
{
	if (previousState != state)
	{
		previousState = state;
		nbFrameFromBeginAnimation = 0;
	}
	++nbFrameFromBeginAnimation;

	if (state == moving)
	{
		currentAnimationNumber = floor(nbFrameFromBeginAnimation / timeInFrameForEachAnimations);

		if (nbFrameFromBeginAnimation >= nbFramePourUnCycle)
		{
			nbFrameFromBeginAnimation = 24;
		}
	}
	else if (state == exploding)
	{
		currentAnimationNumber = floor(nbFrameFromBeginAnimation / 3);

		if (nbFrameFromBeginAnimation >= 47)
		{
			state = dead;
		}
	}
}

/// <summary>
/// Draws the specified fenetre.
/// </summary>
/// <param name="fenetre">The fenetre.</param>
void ProjectileMissile::Draw(RenderWindow& fenetre)
{
	if (state != dead)
	{
		if (state == moving)
		{
			animationsProjectilesSprites[state]->setRotation(rotation);
		}
		animationsProjectilesSprites[state]->setPosition(position);
		animationsProjectilesSprites[state]->SetProjectileTextureRect(currentAnimationNumber);

		fenetre.draw(*animationsProjectilesSprites[state]);
	}

}

