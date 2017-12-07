#include "EnnemiTurret.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

EnnemiTurret::EnnemiTurret(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, Vector2f position, ProjectileManager * projectileManager) : Ennemi(animationProjectileSprite, animationProjectileExplodingSprite, position, projectileManager)
{
	scoreValue = 10;
	acteurType = acteurTypeTurret;
	vitesseMax = 0;
	accelerationParSeconde = 0;
	tempsEnFrameEntreDeuxTires = 60;
}

EnnemiTurret::~EnnemiTurret()
{

}

void EnnemiTurret::Update(Vector2f playerPosition)
{
	Acteur::Update();
	if (Ennemi::LookForPlayer(playerPosition))
	{	
		if (readyToAttack)
		{
			CalculateDirectionToPlayer(playerPosition);
			Shoot();
			Vector2f positionProjectile;
			positionProjectile.x = position.x;
			positionProjectile.y = position.y -20;
			projectileManager->GenerateProjectile(missile, positionProjectile, direction, alien);
		}
	}
	rotation = 0;
}

