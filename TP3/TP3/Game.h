#pragma once

#include <SFML/Graphics.hpp>
#include "Joueur.h"

using namespace sf;

namespace sideSpaceShooter
{
	class Game
	{
	public:
		Game();
		~Game();
		int run();
		int testTest();
		RenderWindow *mainWin = new RenderWindow;

	private:
		static const int LARGEUR = 1280;
		static const int HAUTEUR = 720;
		static const int MAX_TUILES = 10000;
		static const int NB_TUILES_METALIQUE = 2;
		static const int TAILLE_TUILES_X = 60;
		static const int TAILLE_TUILES_Y = 60;
		static const int LARGEUR_BACKGROUND = 2294;
		static const int NB_BACKGROUND = 2;
		static const int NB_ESPACE_BACKGROUND = 5;

		float deplacementBackgroundX;
		int currentBackground;
		Texture backgroundsT[NB_BACKGROUND];
		Sprite* backgrounds[NB_BACKGROUND];
		

		const float limiteGauche = 0;
		const float limiteDroite = LARGEUR_BACKGROUND * NB_ESPACE_BACKGROUND;
		const float limiteHaut = 0;
		const float limiteBas = 1200;

		const std::string textureBlocPath = "Ressources\\Sprites\\bloc";

		Sprite* grilleDeTuiles[MAX_TUILES];

		Texture tuilesMetaliquesT[NB_TUILES_METALIQUE];
	Vector2f velocity;

		bool init();
		void getInputs();
		void getInput();
		void update();
		void draw();

		View view;
		Event event;
		//Acteur
		Joueur* joueur;
		//touches
		std::map<Keyboard::Key, bool> inputs;
	};
}	