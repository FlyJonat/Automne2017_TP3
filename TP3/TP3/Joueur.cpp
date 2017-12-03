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
/// <summary>
/// Avoir la distance qu'un joueur a parcouru.
/// </summary>
/// <returns></returns>
float Joueur::GetDeplacement()
{
	return positionActuelle.x - positionPrecedente.x;
}
/// <summary>
/// Déplace le joueur dépendamment s'il est entré en collision avec un bloc.
/// </summary>
/// <param name="direction">The direction.</param>
/// <param name="objet">The objet.</param>
void Joueur::Move(const Vector2f direction, FloatRect objet)
{
	positionPrecedente = getPosition();
	Acteur::Move(direction);
	Acteur::IsColliding(objet);
	positionActuelle = getPosition();
}
void Joueur::Move(const Vector2f direction)
{
	positionPrecedente = getPosition();
	Acteur::Move(direction);
	positionActuelle = getPosition();
}