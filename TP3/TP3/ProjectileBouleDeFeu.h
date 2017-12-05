#pragma once
#include "Projectile.h"

//Laurent- 1562287

namespace sideSpaceShooter
{
	class ProjectileBouleDeFeu : public Projectile
	{
	public:
		ProjectileBouleDeFeu(Animation *animationProjectileSprite, Animation * animationProjectileExplodingSprite, int nbAnimation,  Vector2f position, Vector2f direction);
		~ProjectileBouleDeFeu();
		void Update();
		void UpdateAnimation();

	private:
		bool revertingAnimation = false;
	};
}