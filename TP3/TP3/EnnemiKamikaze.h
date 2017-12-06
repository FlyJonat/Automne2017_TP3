#pragma once
#include "Ennemi.h"


//Laurent- 1562287

namespace sideSpaceShooter
{
	class EnnemiKamikaze : public Ennemi
	{
	public:
		EnnemiKamikaze(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, Vector2f position, ProjectileManager * projectileManager);
		~EnnemiKamikaze();



	protected:
		void Update(Vector2f playerPosition);

	};
}

