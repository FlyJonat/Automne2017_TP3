#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Joueur.h"

using namespace sf;

namespace sideSpaceShooter
{
	class Game
	{
	public:
		Game();
		int run();
		int testTest();
		RenderWindow *mainWin = new RenderWindow;

	private:
		static const int LARGEUR = 1280;
		static const int HAUTEUR = 720;
		static const int MAX = 10000;
		static const int NB_TUILES_METALIQUE = 2;
		static const int TAILLE_TUILES_X = 60;
		static const int TAILLE_TUILES_Y = 60;

		const float limiteGauche = 0;
		const float limiteDroite = 2294 * 2;
		const float limiteHaut = 0;
		const float limiteBas = 1200;

		const std::string textureBlocPath = "Ressources\\Sprites\\bloc";

		Sprite* grilleDeTuiles[MAX];

		Texture tuilesMetaliquesT[NB_TUILES_METALIQUE];


		bool init();
		void getInputs();
		void getInput();
		void update();
		void draw();

		View view;
		Event event;
		//Acteur
		Joueur joueur;
		//touches
		std::map<Keyboard::Key, bool> inputs;
		//background
		int nbBackground;
		float deplacementBackgroundX;
		float deplacementBackgroundY;
		Texture backgroundsT[2];
		Sprite* backgrounds[2];
	};
}