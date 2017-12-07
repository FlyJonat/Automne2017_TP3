#pragma once
#include "Ennemi.h"


//Laurent- 1562287

namespace sideSpaceShooter
{
	class EnnemiTurret : public Ennemi
	{
	public:
		EnnemiTurret(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, Vector2f position, ProjectileManager * projectileManager);
		~EnnemiTurret();



	protected:
		void Update(Vector2f playerPosition);

	};
}

