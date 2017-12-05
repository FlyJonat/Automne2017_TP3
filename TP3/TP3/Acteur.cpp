#include "Acteur.h"

using namespace sideSpaceShooter;
using namespace std;

Acteur::Acteur(std::string texturePath):velocity(0,0)
{
	this->texturePath = texturePath;
}
Acteur::~Acteur()
{

}
bool Acteur::init(float limiteGauche, float limiteDroite,float limiteHaut, float limiteBas)
{
	if(!acteurSpriteT.loadFromFile(texturePath))
	{
		return false;
	}
	setTexture(acteurSpriteT);
	setOrigin(acteurSpriteT.getSize().x / 2, acteurSpriteT.getSize().y / 2);
	this->limiteGauche = limiteGauche;
	this->limiteDroite = limiteDroite;
	this->limiteHaut = limiteHaut;
	this->limiteBas = limiteBas;
	return true;
}

void Acteur::Update()
{
	if (tempsDeRecharge > 0)
	{
		--tempsDeRecharge;
	}
	else
	{
		isCanShoot = true;
	}
}
void Acteur::Move(const Vector2f direction)
{
	float directionX = direction.x;
	float directionY = direction.y;
	//Test sur les limites de l'écran
	if (getPosition().x < limiteGauche)
	{
		setPosition(limiteGauche, getPosition().y);
	}
	else if (getPosition().x + getGlobalBounds().width > limiteDroite)
	{
		setPosition(limiteDroite - getGlobalBounds().width, getPosition().y);
	}
	if (getPosition().x < limiteHaut)
	{
		setPosition(getPosition().x, limiteHaut);
	}
	else if (getPosition().y + getGlobalBounds().height > limiteBas)
	{
		setPosition(getPosition().x, limiteBas - getGlobalBounds().height);
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
	Sprite::move(velocity);
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
	if (Sprite::getGlobalBounds().intersects(objet))
	{
		//Colision avec le planché
		if (((getPosition().y + getOrigin().y) - (objet.top)) <= 20 && ((getPosition().y + getOrigin().y) - (objet.top) >= -20))
		{
			velocity.y *= -1;
			Sprite::move(0,-((getPosition().y + getOrigin().y) - (objet.top)));
		}

		//Colision avec le plafond
	
		else if (((getPosition().y - getOrigin().y) - (objet.top + objet.height) <= 20) && ((getPosition().y - getOrigin().y) - (objet.top + objet.height) >= -20))
		{
			velocity.y *= -1;
			Sprite::move(0, -((getPosition().y - getOrigin().y) - (objet.top + objet.height)));
		}

		//Colision avec le coté droit
		else if (getPosition().x + getOrigin().x - objet.left <= 20 && getPosition().x + getOrigin().x - objet.left >= -20)
		{
			velocity.x *= -1;
			Sprite::move(-(getPosition().x + getOrigin().x - objet.left), 0);
		}

		//Colision avec le coté gauche	
		else if (getPosition().x - getOrigin().x - objet.left - objet.width <= 20 && getPosition().x - getOrigin().x - objet.left - objet.width >= -20)
		{
			velocity.x *= -1;
			Sprite::move(-(getPosition().x - getOrigin().x - objet.left - objet.width), 0);
		}
		return true;
	}
	return false;
}

void Acteur::Shoot()
{
	isCanShoot = false;
	tempsDeRecharge = tempsEnFrameEntreDeuxTires;
}

const bool Acteur::GetIsCanShoot()
{
	return isCanShoot;
}