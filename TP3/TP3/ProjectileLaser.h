#pragma once
#include "Projectile.h"

//Laurent- 1562287

namespace sideSpaceShooter
{
	class ProjectileLaser : public Projectile
	{
	public:
		ProjectileLaser(Animation *animationProjectileSprite, Animation * animationProjectileExplodingSprite, int nbAnimation, float vitesseMax, float accelerationParSeconde, Vector2f position, Vector2f direction);
		~ProjectileLaser();
		void Update();
		void UpdateAnimation();
		void Draw(RenderWindow& fenetre);

	private :
		
	};
}