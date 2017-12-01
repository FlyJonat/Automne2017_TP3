#include "Joueur.h"
using namespace sideSpaceShooter;


Joueur::Joueur():Acteur("Ressources\\Sprites\\joueur.png")
{
}
Joueur::~Joueur()
{
}
void Joueur::move(const float offSetX, const float offSetY)
{
	Sprite::move(offSetX, offSetY);
	//Test sur les limites de l'écran
	if (getPosition().x < limiteGauche)
	{
		setPosition(limiteGauche, getPosition().y);
	}
	else if (getPosition().x + getGlobalBounds().width > limiteDroite)
	{
		setPosition(limiteDroite - getGlobalBounds().width, getPosition().y);
	}
	if (getPosition().y < limiteHaut)
	{
		setPosition(getPosition().x, limiteHaut);
	}
	else if (getPosition().y + getGlobalBounds().height > limiteBas)
	{
		setPosition(getPosition().x, limiteBas - getGlobalBounds().height);
	}
}