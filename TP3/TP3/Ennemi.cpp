#include "Ennemi.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

Ennemi::Ennemi(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, Vector2f position, ProjectileManager * projectileManager) : Acteur(animationActeurSprite, animationActeurExplodingSprite, position, projectileManager)
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
	if (position.y - SIGHT_RANGE <= playerPosition.y && position.y + SIGHT_RANGE >= playerPosition.y)
	{
		if (position.x - SIGHT_RANGE <= playerPosition.x && position.x + SIGHT_RANGE >= playerPosition.x)
		{
			return true;
		}
	}
	
	return false;
}


Vector2f Ennemi::CalculateDirectionToPlayer(Vector2f playerPosition)
{
	Vector2f distanceAParcourir;
	distanceAParcourir = playerPosition - position;

	direction.x = (distanceAParcourir.x / fabs(distanceAParcourir.x + distanceAParcourir.y));
	direction.y = (distanceAParcourir.y / fabs(distanceAParcourir.x + distanceAParcourir.y));

	rotation = (atan (direction.y / direction.x) * (180.0 / M_PI));
	if (direction.x > 0)
	{
		rotation += 180;
	}
	return direction;
}
