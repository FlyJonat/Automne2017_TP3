#include "Ennemi.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

Ennemi::Ennemi(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, const int SCORE_VALUE, ActeurType ACTEUR_TYPE, Vector2f position) : Acteur(animationActeurSprite, animationActeurExplodingSprite, ACTEUR_TYPE, position), SCORE_VALUE(SCORE_VALUE)
{

}

Ennemi::~Ennemi()
{

}

/// <summary>
/// Deplacement des Ennemis
/// </summary>
void Ennemi::Move(const int directionX, const int directionY)
{
	
}


void Ennemi::Update()
{
	
	UpdateAnimation();

}

void Ennemi::UpdateAnimation()
{

}

const int Ennemi::GetScoreValue()
{
	return SCORE_VALUE;
}

