#include "Joueur.h"
using namespace sideSpaceShooter;


Joueur::Joueur():Acteur("Ressources\\Sprites\\joueur.png")
{
}
Joueur::~Joueur()
{
}
const int Joueur::GetNextShotOffset()
{
	if (nextShotOffset == 1)
	{
		nextShotOffset = 2.0f;
	}
	else
	{
		nextShotOffset = 1;
	}
	return nextShotOffset;
}