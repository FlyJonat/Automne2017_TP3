#pragma once
#include "Ennemi.h"


//Laurent- 1562287

namespace sideSpaceShooter
{
	class EnnemiDeBase : public Ennemi
	{
	public:
		EnnemiDeBase(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, const int SCORE_VALUE, ActeurType ACTEUR_TYPE, Vector2f position);
		~EnnemiDeBase();

		

	protected:
		void Update();

	};
}

