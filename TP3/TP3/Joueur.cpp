#include "Joueur.h"
Joueur::Joueur():Acteur("Ressources\\Sprites\\joueur.png")
{
}
Joueur::~Joueur()
{
}
void Joueur::move(const float offSetX, const float offSetY)
{
	Sprite::move(offSetX, offSetY);
	//Test sur les limites de l'�cran
	/*if (getPosition().x < limiteGauche)
	{
		setPosition(limiteGauche, getPosition().y);
	}
	else if (getPosition().x + getGlobalBounds().width > limiteDroite)
	{
		setPosition(limiteDroite - getGlobalBounds().width, getPosition().y);
	}*/
	setPosition(getPosition().x, getPosition().y);
}