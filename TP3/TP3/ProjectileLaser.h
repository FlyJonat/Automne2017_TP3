#pragma once
#include "Projectile.h"
#include "AnimationProjectileLaser.h"
namespace sideSpaceShooter
{
	class ProjectileLaser : public Projectile
	{
	public:
		ProjectileLaser(AnimationProjectileLaser *projectileSprite, int nbAnimation, float vitesseMax, float accelerationParSeconde, Vector2f position, Vector2f direction);
		~ProjectileLaser();
		void Update();
		void UpdateAnimation();
		void Draw(RenderWindow& fenetre);

		AnimationProjectileLaser * projectileSprite;

	private :
		int timeInFrameForEachAnimations = 6;
	};
}