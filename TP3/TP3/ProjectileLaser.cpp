#include "ProjectileLaser.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

ProjectileLaser::ProjectileLaser(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, int nbAnimation, float vitesseMax, float accelerationParSeconde, Vector2f position, Vector2f direction):  Projectile(animationProjectileSprite, animationProjectileExplodingSprite, nbAnimation, vitesseMax, accelerationParSeconde, position, direction)
{

}


ProjectileLaser::~ProjectileLaser()
{

}

void ProjectileLaser::Update()
{
	if (state == moving)
	{
		velocity.x += direction.x * (accelerationParSeconde / 60);
		velocity.y += direction.y * (accelerationParSeconde / 60);

		if (velocity.x > vitesseMax)
		{
			velocity.x = vitesseMax;
		}
		else if (velocity.x < -vitesseMax)
		{
			velocity.x = -vitesseMax;
		}

		if (velocity.y > vitesseMax)
		{
			velocity.y = vitesseMax;
		}
		else if (velocity.y < -vitesseMax)
		{
			velocity.y = -vitesseMax;
		}

		position.x += velocity.x;
		position.y += velocity.y;
		rotation = (atan(velocity.y / velocity.x) * (180.0 / M_PI));
	}
	
	UpdateAnimation();
}

void ProjectileLaser::UpdateAnimation()
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
			nbFrameFromBeginAnimation = 0;
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
void ProjectileLaser::Draw(RenderWindow& fenetre)
{
	if (state != dead)
	{
		animationsProjectilesSprites[state]->setPosition(position);
		animationsProjectilesSprites[state]->SetProjectileTextureRect(currentAnimationNumber);

		fenetre.draw(*animationsProjectilesSprites[state]);
	}
	
}

