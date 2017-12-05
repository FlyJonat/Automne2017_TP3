#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>
#include <math.h>

using namespace sf;

//Jonathan 1535076 sauf pour IsColliding, Update, Shoot, GetIsCanShoot, variables de temps et d'accélération

namespace sideSpaceShooter
{
	{

	public:
		Acteur(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, Vector2f position);
		~Acteur();

		void Update();
		void Shoot();
	protected:
		
		int tempsDeRecharge = 0;

		float autoDeccelerationParSeconde = 1.0;		

		ActeurType acteurType;

		StateActeur state = stateActeurALife; //Etat actuel de l'ennemi.
		StateActeur previousState = stateActeurALife; //Etat precedant de l'ennemi.

		Vector2f direction;
		Vector2f velocity;
		Vector2f originOffset;

	};
}