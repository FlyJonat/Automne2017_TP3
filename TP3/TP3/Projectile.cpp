# include "Projectile.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

Projectile::Projectile(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, int nbAnimation, float vitesseMax, float accelerationParSeconde, Vector2f position, Vector2f direction) : nbAnimation(nbAnimation), vitesseMax(vitesseMax), accelerationParSeconde(accelerationParSeconde), position(position), direction(direction)
{
	this->animationsProjectilesSprites[moving] = animationProjectileSprite;
	this->animationsProjectilesSprites[exploding] = animationProjectileExplodingSprite;
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
const bool Projectile::IsColliding(const Vector2f& positionObjet, const int largeurObjet, const int hauteurObjet)
{

	if ((position.x >= positionObjet.x - (largeurObjet / 2) && position.x <= positionObjet.x + (largeurObjet / 2)) && (position.y >= positionObjet.y - (hauteurObjet / 2) && position.y <= positionObjet.y + (hauteurObjet / 2)))
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
	state = exploding;
	rotation = GetRandomNum(360);
}

const State Projectile::GetState()
{
	return state;
}

int Projectile::GetRandomNum(int max)
{
	int numRandom = 0;
	return numRandom = rand() % max;
}