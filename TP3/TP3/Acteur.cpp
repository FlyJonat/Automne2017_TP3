#include "Acteur.h"
Acteur::Acteur(std::string texturePath):velocity(0,0)
{
	this->texturePath = texturePath;
}
Acteur::~Acteur()
{

}
bool Acteur::init()
{
	if(!acteurSpriteT.loadFromFile(texturePath))
	{
		return false;
	}
	setTexture(acteurSpriteT);
	return true;
}
void Acteur::move(const float offSetX, const float offSetY)
{
	Sprite::move(offSetX, offSetY);
	setPosition(getPosition().x, getPosition().y);
	//Test sur les limites de l'écran
	/*if (getPosition().x < limiteGauche)
	{
	setPosition(limiteGauche, getPosition().y);
	}
	else if (getPosition().x + getGlobalBounds().width > limiteDroite)
	{
	setPosition(limiteDroite - getGlobalBounds().width, getPosition().y);
	}*/
}