#pragma once

#include "Projectile.h"
#include "ProjectileLaser.h"
#include "ProjectileBouleDeFeu.h"
#include "ProjectileMissile.h"

enum Alliance { terran, alien };

namespace sideSpaceShooter
{
	class ProjectileManager
	{
	public:
		ProjectileManager(Sprite* grilleDeTuiles[], const int MAX_TUILES, Animation * animations[], const int NB_SPRITE_SHEET_ANIMATION);
		~ProjectileManager();
		void GenerateProjectile(ProjectileType projectileType, Vector2f position, Vector2f direction, Alliance Alliance);
		void Update();
		void Drawn(RenderWindow& fenetre);
		int TestCollision(const Animation *objet, Alliance alliance);

	private:
		const int MAX_TUILES;
		const int NB_SPRITE_SHEET_ANIMATION;
		Sprite** grilleDeTuiles;
		Animation ** animations;
		vector<Projectile*> projectiles[2];

	};
}
