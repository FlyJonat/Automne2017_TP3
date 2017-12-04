#pragma once
#include "Acteur.h"

//Jonathan 1535076 sauf GetNextShotOffSet et nextShotOffset
namespace sideSpaceShooter
{
	class Joueur :public Acteur
	{
	public:
		Joueur(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, ActeurType ACTEUR_TYPE, Vector2f position);
		~Joueur();
		const int GetNextShotOffset();
		float GetDeplacement();
		void Update();
		void Move(const Vector2f direction);
	private :
		float nextShotOffset = 1;
		Vector2f positionPrecedente;

	};
}