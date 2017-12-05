#pragma once
#include "Ennemi.h"


//Laurent- 1562287

namespace sideSpaceShooter
{
	class EnnemiDeBase : public Ennemi
	{
	public:
		EnnemiDeBase(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, Vector2f position);
		~EnnemiDeBase();

		

	protected:
		void Update(Vector2f playerPosition);

	};
}

