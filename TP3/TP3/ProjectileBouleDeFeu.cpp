#include "ProjectileBouleDeFeu.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

ProjectileBouleDeFeu::ProjectileBouleDeFeu(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, int nbAnimation, Vector2f position, Vector2f direction) : Projectile(animationProjectileSprite, animationProjectileExplodingSprite, nbAnimation, position, direction)
{
	vitesseMax = 5;
	accelerationParSeconde = 60;
	dammage = 2;
}


ProjectileBouleDeFeu::~ProjectileBouleDeFeu()
{

}

void ProjectileBouleDeFeu::Update()
{
	if (state == stateProjectileMoving)
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
		if (direction.x < 0)
		{
			rotation += 180;
		}
	}

	

	UpdateAnimation();
}

void ProjectileBouleDeFeu::UpdateAnimation()
{
	if (previousState != state)
	{
		previousState = state;
		nbFrameFromBeginAnimation = 0;
	}
	

	if (state == stateProjectileMoving)
	{
		if (revertingAnimation)
		{
			--nbFrameFromBeginAnimation;
		}
		else
		{
			++nbFrameFromBeginAnimation;
		}

		if (nbFrameFromBeginAnimation >= nbFramePourUnCycle)
		{
			revertingAnimation = true;
		}
		else if (nbFrameFromBeginAnimation <= 0)
		{
			revertingAnimation = false;
		}

		currentAnimationNumber = floor(nbFrameFromBeginAnimation / timeInFrameForEachAnimations);
	}
	else if (state == stateProjectileExploding)
	{
		currentAnimationNumber = floor(nbFrameFromBeginAnimation / 3);
		++nbFrameFromBeginAnimation;
		if (nbFrameFromBeginAnimation >= 47)
		{
			state = stateProjectileDead;
		}
	}
}
