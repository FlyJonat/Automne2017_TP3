#pragma once

#include "Joueur.h"
#include "EnnemiDeBase.h"
#include "ProjectileLaser.h"
#include "ProjectileBouleDeFeu.h"
#include "ProjectileMissile.h"
#include "Animation.h"

using namespace sf;

//Laurent- 1562287

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

		bool init();
		void getInputs();
		void getInput();
		void update();
		void draw();
		void checkIfIsDead();

		static const int LARGEUR = 1280;
		static const int HAUTEUR = 720;
		static const int MAX_TUILES = 10000;
		static const int NB_TUILES_METALIQUE = 2;
		static const int TAILLE_TUILES_X = 60;
		static const int TAILLE_TUILES_Y = 60;
		static const int LARGEUR_BACKGROUND = 2294;
		static const int NB_BACKGROUND = 2;
		static const int NB_ESPACE_BACKGROUND = 5;
		static const int NB_SPRITE_SHEET_ANIMATION = 13;

		const std::string textureBlocPath = "Ressources\\Sprites\\bloc";

		static const int NB_COLONES_JOUEUR_ANIMATION = 1;
		static const int NB_LIGNES_JOUEUR_ANIMATION = 1;
		static const int NB_ANIMES_JOUEUR_ANIMATION = 1;
		const std::string textureJoueurPath = "Ressources\\Sprites\\joueur.png";
		
		static const int NB_COLONES_LASER_ANIMATION = 1;
		static const int NB_LIGNES_LASER_ANIMATION = 11;
		static const int NB_ANIMES_LASER_ANIMATION = 11;
		const std::string textureLaserPath = "Ressources\\Sprites\\projectile_laser.png";

		static const int NB_COLONES_BOULE_DE_FEU_ANIMATION = 6;
		static const int NB_LIGNES_BOULE_DE_FEU_ANIMATION = 1;
		static const int NB_ANIMES_BOULE_DE_FEU_ANIMATION = 6;
		const std::string textureBouleDeFeuPath = "Ressources\\Sprites\\projectile_boules_de_feux.png";

		static const int NB_COLONES_MISSILE_ANIMATION = 4;
		static const int NB_LIGNES_MISSILE_ANIMATION = 2;
		static const int NB_ANIMES_MISSILE_ANIMATION = 8;
		const std::string textureMissilePath = "Ressources\\Sprites\\projectile_missiles.png";

		static const int NB_COLONES_EXPLOSION_PROJECTILE_ANIMATION = 4;
		static const int NB_LIGNES_EXPLOSION_PROJECTILE_ANIMATION = 4;
		static const int NB_ANIMES_EXPLOSION_PROJECTILE_ANIMATION = 16;
		const std::string textureExplosionProjectilePath = "Ressources\\Sprites\\explosion_Projectile.png";

		float deplacementBackgroundX;
		float deplacementBackgroundTotal = 0;
		int currentBackground;
		Texture backgroundsT[NB_BACKGROUND];
		Sprite* backgrounds[NB_BACKGROUND];
		
		const float limiteGauche = 0;
		const float limiteDroite = LARGEUR_BACKGROUND * NB_ESPACE_BACKGROUND;
		const float limiteHaut = 0;
		const float limiteBas = 1200;

		unsigned int timer = 0;

		
		Sprite* grilleDeTuiles[MAX_TUILES];
		Texture tuilesMetaliquesT[NB_TUILES_METALIQUE];
		Vector2f velocity;

		//Acteur
		Joueur* joueur;
		int blocCollisionAvecJoueur;

		vector<Ennemi*> Ennemis;
		vector<Projectile*> projectiles;
		Animation * animations[NB_SPRITE_SHEET_ANIMATION];

		//touches
		std::map<Keyboard::Key, bool> inputs;

		View view;
		Event event;
	};
}	