#include "Ennemi.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

Ennemi::Ennemi(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, Vector2f position) : Acteur(animationActeurSprite, animationActeurExplodingSprite, position)
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


void Ennemi::Update(Vector2f playerPosition)
{
	
	UpdateAnimation();

}

void Ennemi::UpdateAnimation()
{

}

const int Ennemi::GetScoreValue()
{
	return scoreValue;
}

bool Ennemi::LookForPlayer(Vector2f playerPosition)
{
	
	if (position.x - SIGHT_RANGE <= playerPosition.x && position.x + SIGHT_RANGE >= playerPosition.x)
	{
		return true;
	}
	return false;
}

const bool Ennemi::GetWantToAttack()
{
	return wantToAttack;
}
