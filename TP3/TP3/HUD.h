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
		/*static*/ void ShowPlayerLife(Joueur joueur);
		void Draw();
		/*static*/ Text GetText();
	private:
		/*static*/ string playerLife;
		/*static*/ Text textPlayerLife;
	};
}