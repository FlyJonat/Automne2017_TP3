#include "EnnemiLanceurMissile.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

EnnemiLanceurMissile::EnnemiLanceurMissile(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, Vector2f position, ProjectileManager * projectileManager) : Ennemi(animationProjectileSprite, animationProjectileExplodingSprite, position, projectileManager)
{
	scoreValue = 10;
	acteurType = acteurTypeLanceurMissile;
	vitesseMax = 6;
	accelerationParSeconde = 6;
	tempsEnFrameEntreDeuxTires = 60;
}

EnnemiLanceurMissile::~EnnemiLanceurMissile()
{

}

void EnnemiLanceurMissile::Update(Vector2f playerPosition)
{
	Acteur::Update();
	if (Ennemi::LookForPlayer(playerPosition))
	{
		Acteur::Move(-CalculateDirectionToPlayer(playerPosition));
		if (readyToAttack)
		{
			Shoot();
			projectileManager->GenerateProjectile(missile, position, direction, alien);
		}

	}
	else
	{
		direction.x = 0;
		direction.y = 0;
		Acteur::Move(direction);
	}
}

