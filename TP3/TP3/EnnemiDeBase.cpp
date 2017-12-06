#include "EnnemiDeBase.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

EnnemiDeBase::EnnemiDeBase(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, Vector2f position, ProjectileManager * projectileManager) : Ennemi(animationProjectileSprite, animationProjectileExplodingSprite, position, projectileManager)
{
	scoreValue = 10;
	acteurType = acteurTypeEnnemiDeBase;
	vitesseMax = 6;
	accelerationParSeconde = 6;
	tempsEnFrameEntreDeuxTires = 60;
}

EnnemiDeBase::~EnnemiDeBase()
{

}

void EnnemiDeBase::Update(Vector2f playerPosition)
{
	Acteur::Update();
	if (Ennemi::LookForPlayer(playerPosition))
	{
		Acteur::Move(-CalculateDirectionToPlayer(playerPosition));
		if (readyToAttack)
		{
			Shoot();
			projectileManager->GenerateProjectile(laser, position, direction);
		}
		
	}
	else
	{
		direction.x = 0;
		direction.y = 0;
		Acteur::Move(direction);
	}
}

