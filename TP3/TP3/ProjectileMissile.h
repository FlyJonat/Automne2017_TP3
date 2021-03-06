#pragma once
#include "Projectile.h"

//Laurent- 1562287

namespace sideSpaceShooter
{
	class ProjectileMissile : public Projectile
	{
	public:
		ProjectileMissile(Animation *animationProjectileSprite, Animation * animationProjectileExplodingSprite, int nbAnimation, Vector2f position, Vector2f direction);
		~ProjectileMissile();
		void Update();
		void UpdateAnimation();

	private:
		static const int TIME_BEFORE_EACH_DIRECTION_CHANGE = 45;
		int remainingTimeBeforeChangeDirection = 22;
		int startFrame = 30;
	};
}