#include "Acteur.h"

using namespace sideSpaceShooter;
using namespace std;

//Laurent- 1562287

Acteur::Acteur(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, ActeurType ACTEUR_TYPE, Vector2f position) : ACTEUR_TYPE(ACTEUR_TYPE), position(position)
{
	this->animationsActeurSprites[stateActeurALife] = animationActeurSprite;
	this->animationsActeurSprites[stateActeurExploding] = animationActeurExplodingSprite;
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
		readyToAttack = true;
	}
	UpdateAnimation();
}

void Acteur::UpdateAnimation()
{
	if (state != stateActeurExploding && state != stateActeurDead)
	{
		currentAnimationNumber = 0;
	}
	else
	{
		currentAnimationNumber = floor(nbFrameFromBeginAnimation / timeInFrameForEachAnimations);

		if (nbFrameFromBeginAnimation >= nbFramePourUnCycle)
		{
			state = stateActeurDead;
		}
		++nbFrameFromBeginAnimation;
	}
}

/// <summary>
/// Draws the specified fenetre.
/// </summary>
/// <param name="fenetre">The fenetre.</param>
void Acteur::Draw(RenderWindow& fenetre)
{
	if (state != stateActeurDead)
	{
		animationsActeurSprites[state]->setRotation(rotation);
		animationsActeurSprites[state]->setPosition(position);
		animationsActeurSprites[state]->SetProjectileTextureRect(currentAnimationNumber);

		fenetre.draw(*animationsActeurSprites[state]);
	}

}

void Acteur::Move(const Vector2f direction)
{
	float directionX = direction.x;
	float directionY = direction.y;


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
	position.x += velocity.x;
	position.y += velocity.y;
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
	animationsActeurSprites[state]->setPosition(position);

	if (animationsActeurSprites[state]->getGlobalBounds().intersects(objet))
	{
		//Colision avec le planché
		if (((animationsActeurSprites[state]->getPosition().y + animationsActeurSprites[state]->getOrigin().y) - (objet.top)) <= 30 && ((animationsActeurSprites[state]->getPosition().y + animationsActeurSprites[state]->getOrigin().y) - (objet.top) >= -30))
		{
			velocity.y *= -1;
			animationsActeurSprites[state]->move(0,-((animationsActeurSprites[state]->getPosition().y + animationsActeurSprites[state]->getOrigin().y) - (objet.top)));
		}

		//Colision avec le plafond
	
		else if (((animationsActeurSprites[state]->getPosition().y - animationsActeurSprites[state]->getOrigin().y) - (objet.top + objet.height) <= 30) && ((animationsActeurSprites[state]->getPosition().y - animationsActeurSprites[state]->getOrigin().y) - (objet.top + objet.height) >= -30))
		{
			velocity.y *= -1;
			animationsActeurSprites[state]->move(0, -((animationsActeurSprites[state]->getPosition().y - animationsActeurSprites[state]->getOrigin().y) - (objet.top + objet.height)));
		}

		//Colision avec le coté droit
		else if (animationsActeurSprites[state]->getPosition().x + animationsActeurSprites[state]->getOrigin().x - objet.left <= 30 && animationsActeurSprites[state]->getPosition().x + animationsActeurSprites[state]->getOrigin().x - objet.left >= -30)
		{
			velocity.x *= -1;
			animationsActeurSprites[state]->move(-(animationsActeurSprites[state]->getPosition().x + animationsActeurSprites[state]->getOrigin().x - objet.left), 0);
		}

		//Colision avec le coté gauche	
		else if (animationsActeurSprites[state]->getPosition().x - animationsActeurSprites[state]->getOrigin().x - objet.left - objet.width <= 30 && animationsActeurSprites[state]->getPosition().x - animationsActeurSprites[state]->getOrigin().x - objet.left - objet.width >= -30)
		{
			velocity.x *= -1;
			animationsActeurSprites[state]->move(-(animationsActeurSprites[state]->getPosition().x - animationsActeurSprites[state]->getOrigin().x - objet.left - objet.width), 0);
		}
		return true;
	}
	return false;
}

const StateActeur Acteur::GetState()
{
	return state;
}


void Acteur::Shoot()
{
	readyToAttack = false;
	tempsDeRecharge = tempsEnFrameEntreDeuxTires;
}

const bool Acteur::GetReadyToAttack() const
{
	return readyToAttack;
}

const Vector2f Acteur::GetPosition()
{
	return position;
}