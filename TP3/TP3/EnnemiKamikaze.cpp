#include "EnnemiKamikaze.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

EnnemiKamikaze::EnnemiKamikaze(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, Vector2f position, ProjectileManager * projectileManager) : Ennemi(animationProjectileSprite, animationProjectileExplodingSprite, position, projectileManager)
{
	scoreValue = 10;
	acteurType = acteurTypeKamikaze;
	vitesseMax = 6;
	accelerationParSeconde = 6;
	tempsEnFrameEntreDeuxTires = 60;
}

EnnemiKamikaze::~EnnemiKamikaze()
{

}

void EnnemiKamikaze::Update(Vector2f playerPosition)
{
	Acteur::Update();
	if (Ennemi::LookForPlayer(playerPosition))
	{
		Acteur::Move(CalculateDirectionToPlayer(playerPosition));
	}
	else
	{
		direction.x = 0;
		direction.y = 0;
		Acteur::Move(direction);
	}
}

