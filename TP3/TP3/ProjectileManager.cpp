#include "ProjectileManager.h"

using namespace sideSpaceShooter;

ProjectileManager::ProjectileManager(Sprite * grilleDeTuiles[], const int MAX_TUILES, Animation * animations[], const int NB_SPRITE_SHEET_ANIMATION) : MAX_TUILES(MAX_TUILES), NB_SPRITE_SHEET_ANIMATION(NB_SPRITE_SHEET_ANIMATION)
{
	this->grilleDeTuiles = grilleDeTuiles;
	this->animations = animations;
}


ProjectileManager::~ProjectileManager()
{
	for (size_t i = 0; i < 2; ++i)
	{
		for (size_t j = 0; j < projectiles[i].size(); ++j)
		{
			delete projectiles[i][j];
		}
	}
}


void ProjectileManager::GenerateProjectile(ProjectileType projectileType, Vector2f position, Vector2f direction, Alliance Alliance)
{
	
	if (projectileType == laser)
	{
		Projectile* p = new ProjectileLaser(animations[animationLaser], animations[animationProjectileExplosion], 11, position, direction);
		projectiles[Alliance].push_back(p);
	}
	
	else if (projectileType == bouleDeFeu)
	{
		Projectile* a = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, position, direction);
		projectiles[Alliance].push_back(a);
		direction.y = 1;
		Projectile* b = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, position, direction);
		projectiles[Alliance].push_back(b);
		direction.y = -1;
		Projectile* c = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, position, direction);
		projectiles[Alliance].push_back(c);
	}
	
	else if (projectileType == missile)
	{
		Projectile* d = new ProjectileMissile(animations[animationMissile], animations[animationProjectileExplosion], 8, position, direction);
		projectiles[Alliance].push_back(d);
	}

	
}
void ProjectileManager::Update()
{
	//Vérifie les projectiles morts
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < projectiles[i].size(); j++)
		{
			if (projectiles[i][j]->GetState() == stateProjectileDead)
			{
				delete projectiles[i][j];
				projectiles[i].erase(projectiles[i].begin() + j);
			}
		}
	}

	for (size_t i = 0; i < projectiles[terran].size(); ++i)
	{
		if (projectiles[terran][i]->GetState() == stateProjectileMoving)
		{
			for (size_t j = 0; j < projectiles[alien].size(); j++)
			{
				//Détruit le projectile en cas de collision.
				if (projectiles[alien][j]->GetState() == stateProjectileMoving && projectiles[terran][i]->IsColliding(projectiles[alien][j]->GetGlobalBounds()))
				{
					projectiles[terran][i]->Exploding();
					projectiles[alien][j]->Exploding();
					break;
				}
			}
		}
	}
	for (size_t i = 0; i < 2; i++)
	{
		//Vérifie la collision entre un projectile et une tuile.
		for (size_t j = 0; j < projectiles[i].size(); ++j)
		{

			if (projectiles[i][j]->GetState() == stateProjectileMoving)
			{
				for (size_t k = 0; k < MAX_TUILES; ++k)
				{
					if (grilleDeTuiles[k] != nullptr)
					{
						//Détruit le projectile en cas de collision.
						if (projectiles[i][j]->IsColliding(grilleDeTuiles[k]->getGlobalBounds()))
						{
							projectiles[i][j]->Exploding();
							break;
						}
					}
				}
			}

			projectiles[i][j]->Update();
		}
	}
}

int ProjectileManager::TestCollision(const Animation *objet, Alliance alliance)
{
	int nbDammages = 0;
	for (size_t i = 0; i < projectiles[alliance].size(); ++i)
	{
		if (projectiles[alliance][i]->GetState() == stateProjectileMoving)
		{
			//Détruit le projectile en cas de collision.
			if (projectiles[alliance][i]->GetState() == stateProjectileMoving && projectiles[alliance][i]->IsCollidingPixelPerfect(objet))
			{
				projectiles[alliance][i]->Exploding();
				nbDammages += projectiles[alliance][i]->GetDammage();
			}
		}
	}
	return nbDammages;
}
void ProjectileManager::Drawn(RenderWindow& fenetre)
{
	for (size_t i = 0; i < 2; ++i)
	{
		for (size_t j = 0; j < projectiles[i].size(); ++j)
		{
			projectiles[i][j]->Draw(fenetre);
		}
	}
}