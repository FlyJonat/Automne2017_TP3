#include "Joueur.h"
using namespace sideSpaceShooter;


Joueur::Joueur(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, Vector2f position, ProjectileManager * projectileManager):Acteur(animationActeurSprite, animationActeurExplodingSprite, position, projectileManager)
{
	acteurType = acteurTypePlayer;
	vitesseMax = 12;
	accelerationParSeconde = 24;
	tempsEnFrameEntreDeuxTires = 15;
}
Joueur::~Joueur()
{
}

void Joueur::Update()
{
	Acteur::Update();
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
	return position.x - positionPrecedente.x;
}

void Joueur::Move(const Vector2f direction)
{
	positionPrecedente = position;
	Acteur::Move(direction);
}

const bool Joueur::GetReadyToAttack()
{
	return readyToAttack;
}