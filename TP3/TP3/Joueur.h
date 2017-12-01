#pragma once
#include "Acteur.h"
namespace sideSpaceShooter
{
	class Joueur :public Acteur
	{
	public:
		Joueur();
		~Joueur();
		void move(const float offSetX, const float offSetY);
	};
}