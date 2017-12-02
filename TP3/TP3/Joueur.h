#pragma once
#include "Acteur.h"

namespace sideSpaceShooter
{
	class Joueur :public Acteur
	{
	public:
		Joueur();
		~Joueur();
		const int GetNextShotOffset();
	private :
		float nextShotOffset = 1;
	};
}