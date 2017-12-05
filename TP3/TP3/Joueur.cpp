#include "Joueur.h"
using namespace sideSpaceShooter;


Joueur::Joueur(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, Vector2f position):Acteur(animationActeurSprite, animationActeurExplodingSprite, position)
{
	acteurType = acteurTypePlayer;
	vitesseMax = 6;
	accelerationParSeconde = 6;
	tempsEnFrameEntreDeuxTires = 15;
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
/// <summary>
/// Avoir la distance qu'un joueur a parcouru.
/// </summary>
/// <returns></returns>
float Joueur::GetDeplacement()
{
}
void Joueur::Move(const Vector2f direction)
{
	Acteur::Move(direction);
}