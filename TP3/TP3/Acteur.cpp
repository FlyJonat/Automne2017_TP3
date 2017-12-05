	#include "Acteur.h"

using namespace sideSpaceShooter;
using namespace std;


//Laurent- 1562287

Acteur::Acteur(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, Vector2f position) : position(position)
{
	this->animationsActeurSprites[stateActeurALife] = animationActeurSprite;
	this->animationsActeurSprites[stateActeurExploding] = animationActeurExplodingSprite;

	originOffset = animationsActeurSprites[stateActeurALife]->getOrigin();
	srand(time(NULL));
}
Acteur::~Acteur()
{

}

void Acteur::Update()
{
	if (tempsDeRecharge > 0)
	{
		--tempsDeRecharge;
	}
	else
	{
	}
}
{
	{
	}
	{
	}
	{
	}


	if (directionX != 0)
	{
		velocity.x += directionX * (accelerationParSeconde / 60);
	}
	else
	{
		velocity.x += velocity.x * -(autoDeccelerationParSeconde / 60);
	}

	if (directionY != 0)
	{
		velocity.y += directionY * (accelerationParSeconde / 60);
	}
	else
	{
		velocity.y += velocity.y * -(autoDeccelerationParSeconde / 60);
	}

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
}

/// <summary>
/// Determines whether the specified objet is colliding.
/// </summary>
/// <param name="objet">The objet.</param>
/// <returns>
///		<c>true</c> if the specified objet is colliding; otherwise, <c>false</c>.
/// </returns>
bool Acteur::IsColliding(FloatRect objet)
{
	{
		//Colision avec le planché
		if (((position.y + originOffset.y) - (objet.top)) >= 0 && ((position.y + originOffset.y) - (objet.top) <= 30))
		{
			velocity.y *= -1;
			position.y += -((position.y + originOffset.y) - (objet.top));
		}

		//Colision avec le plafond
		else if (((position.y - originOffset.y) - (objet.top + objet.height) <= 0) && ((position.y - originOffset.y) - (objet.top + objet.height) >= -30))
		{
			velocity.y *= -1;
			position.y += -((position.y - originOffset.y) - (objet.top + objet.height));
		}

		//Colision avec le coté droit
		else if (position.x + originOffset.x - objet.left >= 0 && position.x + originOffset.x - objet.left <= 30)
		{
			velocity.x *= -1;
			position.x += -(position.x + originOffset.x - objet.left);
		}

		//Colision avec le coté gauche	
		
		else if ((position.x - originOffset.x) - (objet.left + objet.width) <= 0 && (position.x - originOffset.x) - (objet.left - objet.width) >= -30)
		{
			velocity.x *= -1;
			position.x += -((position.x - originOffset.x) - (objet.left + objet.width));
		}
		animationsActeurSprites[state]->setPosition(position);
		return true;
	}
	return false;
}

void Acteur::Shoot()
{
	tempsDeRecharge = tempsEnFrameEntreDeuxTires;
}

{
}