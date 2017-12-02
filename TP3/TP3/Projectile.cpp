# include "Projectile.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

Projectile::Projectile(int nbAnimation, float vitesseMax, float accelerationParSeconde, Vector2f position, Vector2f direction) : nbAnimation(nbAnimation), vitesseMax(vitesseMax), accelerationParSeconde(accelerationParSeconde), position(position), direction(direction)
{

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
bool Projectile::IsColliding(const Vector2f& positionObjet, const int largeurObjet, const int hauteurObjet)
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
void Projectile::HaveToDie()
{
	haveToDie = true;
}
/// <summary>
/// Gets the have to die.
/// </summary>
/// <returns></returns>
bool Projectile::GetHaveToDie()
{
	return haveToDie;
}