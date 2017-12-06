#pragma once
#include "Ennemi.h"


//Laurent- 1562287

namespace sideSpaceShooter
{
	class EnnemiLanceurMissile : public Ennemi
	{
	public:
		EnnemiLanceurMissile(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, Vector2f position, ProjectileManager * projectileManager);
		~EnnemiLanceurMissile();



	protected:
		void Update(Vector2f playerPosition);

	};
}

