#include "Acteur.h"
Acteur::Acteur(/*std::string texturePath*/)
{
	acteurSpriteT.loadFromFile("Ressources\\Sprites\\joueur.png");
	acteurSprite = new Sprite(acteurSpriteT);
}
Acteur::~Acteur()
{

}