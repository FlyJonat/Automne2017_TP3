#pragma once
#include "Acteur.h"

//Laurent- 1562287

namespace sideSpaceShooter
{
	class Ennemi : public Acteur
	{
	public:
		Ennemi(Animation * animationsActeurSprites, Animation * animationActeurExplodingSprite, const int SCORE_VALUE, ActeurType ACTEUR_TYPE, Vector2f position);
		virtual ~Ennemi();

		void Move(const int directionX, const int directionY);
		void Update();
		const int GetScoreValue();
		


	protected:
		virtual void UpdateAnimation();

		const int SCORE_VALUE = 0;
		const float SIGHT_RANGE = 5;

		


	};
}