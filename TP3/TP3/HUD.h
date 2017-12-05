#pragma once
#include "Joueur.h";
using namespace sf;
using namespace std;

namespace sideSpaceShooter
{
	class HUD
	{
	public:
		HUD();
		~HUD();
		void init();
		void ShowPlayerLife(Joueur joueur);
		void Draw();
	private:
		string playerLife;
		Text textPlayerLife;
	};
}