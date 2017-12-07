# include "Projectile.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

Projectile::Projectile(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, int nbAnimation, Vector2f position, Vector2f direction) : nbAnimation(nbAnimation), position(position), direction(direction)
{
	this->animationsProjectilesSprites[stateProjectileMoving] = animationProjectileSprite;
	this->animationsProjectilesSprites[stateProjectileExploding] = animationProjectileExplodingSprite;
	nbFramePourUnCycle = (nbAnimation * timeInFrameForEachAnimations) -1;
	srand(time(NULL));
}


/// <summary>
/// Sets the position.
/// </summary>
/// <param name="position">The position.</param>
void Projectile::setPosition(const Vector2f& position)
{
	this->position = position;
}

/// <summary>
/// Updates this instance.
/// </summary>
void Projectile::Update()
{
	
}

/// <summary>
/// Draws the specified fenetre.
/// </summary>
/// <param name="fenetre">The fenetre.</param>
void Projectile::Draw(RenderWindow& fenetre)
{
	if (state != stateProjectileDead)
	{
		animationsProjectilesSprites[state]->setRotation(rotation);
		animationsProjectilesSprites[state]->setPosition(position);
		animationsProjectilesSprites[state]->SetProjectileTextureRect(currentAnimationNumber);

		fenetre.draw(*animationsProjectilesSprites[state]);
	}
}

/// <summary>
/// Determines whether the specified position objet is colliding.
/// </summary>
/// <param name="positionObjet">The position objet.</param>
/// <param name="largeurObjet">The largeur objet.</param>
/// <param name="hauteurObjet">The hauteur objet.</param>
/// <returns>
///   <c>true</c> if the specified position objet is colliding; otherwise, <c>false</c>.
/// </returns>
const bool Projectile::IsColliding(FloatRect objet)
{

	animationsProjectilesSprites[state]->setPosition(position);
	if (animationsProjectilesSprites[state]->getGlobalBounds().intersects(objet))
	{
		return true;
	}
	return false;
}

/// <summary>
/// Haves to die.
/// </summary>
void Projectile::Exploding()
{
	state = stateProjectileExploding;
	rotation = GetRandomNum(360);
}

const StateProjectile Projectile::GetState()
{
	return state;
}

int Projectile::GetRandomNum(int max)
{
	int numRandom = 0;
	return numRandom = rand() % max;
}

const FloatRect Projectile::GetGlobalBounds()
{
	animationsProjectilesSprites[state]->setPosition(position);
	return animationsProjectilesSprites[state]->getGlobalBounds();
}