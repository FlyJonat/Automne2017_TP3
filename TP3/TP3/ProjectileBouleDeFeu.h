#pragma once
#include "Projectile.h"

namespace sideSpaceShooter
{
	class ProjectileBouleDeFeu : public Projectile
	{
	public:
		ProjectileBouleDeFeu(Animation *animationProjectileSprite, Animation * animationProjectileExplodingSprite, int nbAnimation, float vitesseMax, float accelerationParSeconde, Vector2f position, Vector2f direction);
		~ProjectileBouleDeFeu();
		void Update();
		void UpdateAnimation();
		void Draw(RenderWindow& fenetre);

	private:
		bool revertingAnimation = false;
	};
}