#include "ProjectileLaser.h"

using namespace sideSpaceShooter;

ProjectileLaser::ProjectileLaser(AnimationProjectileLaser * projectileSprite, int nbAnimation, float vitesseMax, float accelerationParSeconde, Vector2f position, Vector2f direction):  Projectile(nbAnimation, vitesseMax, accelerationParSeconde, position, direction)
{
	this->projectileSprite = projectileSprite;
}


ProjectileLaser::~ProjectileLaser()
{

}

void ProjectileLaser::Update()
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
	UpdateAnimation();
}

void ProjectileLaser::UpdateAnimation()
{
	++nbFrameFromBeginAnimation;

	currentAnimationNumber = floor(nbFrameFromBeginAnimation / 6);

	if (nbFrameFromBeginAnimation >= (65))
	{
		nbFrameFromBeginAnimation = 0;
	}
}

/// <summary>
/// Draws the specified fenetre.
/// </summary>
/// <param name="fenetre">The fenetre.</param>
void ProjectileLaser::Draw(RenderWindow& fenetre)
{
	projectileSprite->setPosition(position);
	projectileSprite->SetProjectileTextureRect(currentAnimationNumber);
	fenetre.draw(*projectileSprite);
}

