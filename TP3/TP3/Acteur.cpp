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
	this->limiteGauche = limiteGauche;
	this->limiteDroite = limiteDroite;
	this->limiteHaut = limiteHaut;
	this->limiteBas = limiteBas;
	return true;
}
void Acteur::move(const float offSetX, const float offSetY)
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
	if(getPosition().x < limiteHaut)
	{
		setPosition(getPosition().x, limiteHaut);
	}
	else if(getPosition().y + getGlobalBounds().height > limiteBas)
	{
		setPosition(getPosition().x,limiteBas - getGlobalBounds().height);
	}
}