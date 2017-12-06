#include "ProjectileManager.h"

using namespace sideSpaceShooter;

ProjectileManager::ProjectileManager(Sprite * grilleDeTuiles[], const int MAX_TUILES, Animation * animations[], const int NB_SPRITE_SHEET_ANIMATION) : MAX_TUILES(MAX_TUILES), NB_SPRITE_SHEET_ANIMATION(NB_SPRITE_SHEET_ANIMATION)
{
	this->grilleDeTuiles = grilleDeTuiles;
	this->animations = animations;
}


ProjectileManager::~ProjectileManager()
{
	for (size_t i = 0; i < projectiles.size(); ++i)
	{
		delete projectiles[i];
	}
}


void ProjectileManager::GenerateProjectile(ProjectileType projectileType, Vector2f position, Vector2f direction)
{
	if (projectileType == laser)
	{
		Projectile* p = new ProjectileLaser(animations[animationLaser], animations[animationProjectileExplosion], 11, position, direction);
		projectiles.push_back(p);
	}
	
	else if (projectileType == bouleDeFeu)
	{
		Projectile* a = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, position, direction);
		projectiles.push_back(a);
		direction.y = 1;
		Projectile* b = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, position, direction);
		projectiles.push_back(b);
		direction.y = -1;
		Projectile* c = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, position, direction);
		projectiles.push_back(c);
	}
	
	else if (projectileType == missile)
	{
		Projectile* d = new ProjectileMissile(animations[animationMissile], animations[animationProjectileExplosion], 8, position, direction);
		projectiles.push_back(d);
	}

	
}
void ProjectileManager::Update()
{
	//Vérifie les projectiles morts
	for (size_t i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->GetState() == stateProjectileDead)
		{
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
		}
	}

	//Vérifie la collision entre un projectile et une tuile.
	for (size_t i = 0; i < projectiles.size(); ++i)
	{

		if (projectiles[i]->GetState() == stateProjectileMoving)
		{
			for (size_t j = 0; j < MAX_TUILES; ++j)
			{
				if (grilleDeTuiles[j] != nullptr)
				{
					//Détruit le projectile en cas de collision.
					if (projectiles[i]->IsColliding(grilleDeTuiles[j]->getGlobalBounds()))
					{
						projectiles[i]->Exploding();
						break;
					}
				}
			}
		}

		projectiles[i]->Update();
	}
}
void ProjectileManager::Drawn(RenderWindow& fenetre)
{
	for (size_t i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->Draw(fenetre);
	}
}