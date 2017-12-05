#pragma once
#include "Acteur.h"

//Laurent- 1562287

namespace sideSpaceShooter
{
	class Ennemi : public Acteur
	{
	public:
		Ennemi(Animation * animationsActeurSprites, Animation * animationActeurExplodingSprite, Vector2f position);
		virtual ~Ennemi();

		void Move(const int directionX, const int directionY);
		virtual void Update(Vector2f playerPosition);
		const int GetScoreValue();
		const bool GetWantToAttack();


	protected:
		virtual void UpdateAnimation();
		bool LookForPlayer(Vector2f playerPosition);

		const float SIGHT_RANGE = 500;

		bool wantToAttack = false;
		int scoreValue = 0;
		


	};
}