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
void Acteur::move(const float offSetX, const float offSetY)
{
	float vecteurX = offSetX;
	float vecteurY = offSetY;
	//Test sur les limites de l'écran
	if (getPosition().x < limiteGauche)
	{
		setPosition(limiteGauche, getPosition().y);
	}
	else if (getPosition().x + getGlobalBounds().width > limiteDroite)
	{
		setPosition(limiteDroite - getGlobalBounds().width, getPosition().y);
	}
	if(getPosition().x < limiteHaut)
	{
		setPosition(getPosition().x, limiteHaut);
	}
	else if(getPosition().y + getGlobalBounds().height > limiteBas)
	{
		setPosition(getPosition().x,limiteBas - getGlobalBounds().height);
	}


	if ((cantMoveRight && offSetX > 0) || (cantMoveLeft && offSetX < 0))
	{
		vecteurX = 0;
	}

	if ((cantMoveBot && offSetY > 0) || (cantMoveTop && offSetY < 0))
	{
		vecteurY = 0;
	}
	Sprite::move(vecteurX * VITESSE, vecteurY * VITESSE);
}

/// <summary>
/// Determines whether the specified objet is colliding.
/// </summary>
/// <param name="objet">The objet.</param>
/// <returns>
///   <c>true</c> if the specified objet is colliding; otherwise, <c>false</c>.
/// </returns>
bool Acteur::IsColliding(FloatRect objet)
{
	if (Sprite::getGlobalBounds().intersects(objet))
	{
		//Colision avec le planché
		if (((getPosition().y + getOrigin().y) - (objet.top)) <= 5 && ((getPosition().y + getOrigin().y) - (objet.top) >= -5))
		{
			cantMoveBot = true;
		}

		//Colision avec le plafond
	
		else if (((getPosition().y - getOrigin().y) - (objet.top + objet.height) <= 10) && ((getPosition().y - getOrigin().y) - (objet.top + objet.height) >= -10))
		{
			cantMoveTop = true;
		}

		//Colision avec le coté droit
		else if (getPosition().x + getOrigin().x - objet.left <= 5 && getPosition().x + getOrigin().x - objet.left >= -5)
		{
			cantMoveRight = true;
		}

		//Colision avec le coté gauche	
		else if (getPosition().x - getOrigin().x - objet.left - objet.width <= 5 && getPosition().x - getOrigin().x - objet.left - objet.width >= -5)
		{
			cantMoveLeft = true;
		}
		return true;
	}
	return false;
}

/// <summary>
/// Resets the cant move.
/// </summary>
void Acteur::ResetCantMove()
{
	cantMoveLeft = false;
	cantMoveRight = false;
	cantMoveTop = false;
	cantMoveBot = false;
}