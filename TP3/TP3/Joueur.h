#pragma once
#include "Acteur.h"

//Jonathan 1535076 sauf GetNextShotOffSet et nextShotOffset
namespace sideSpaceShooter
{
	class Joueur :public Acteur
	{
	public:
		Joueur();
		~Joueur();
		const int GetNextShotOffset();
		float GetDeplacement();
		void Move(const Vector2f direction, FloatRect objet);
		void Move(const Vector2f direction);
	private :
		float nextShotOffset = 1;
		Vector2f positionPrecedente;
		Vector2f positionActuelle;
	};
}