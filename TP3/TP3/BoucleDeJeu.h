#pragma once

#include "Scene.h"
#include "Joueur.h"
#include "EnnemiDeBase.h"
#include "EnnemiKamikaze.h"
#include "EnnemiLanceurMissile.h"
#include "EnnemiTurret.h"
#include "ProjectileManager.h"
#include "HUD.h"

using namespace sf;

//Laurent- 1562287

namespace sideSpaceShooter 
{
	class BoucleDeJeu : public Scene
	{
	public:
		BoucleDeJeu();
		~BoucleDeJeu();
		scenes run();
		int testTest();
		bool init(RenderWindow * const window);

	private:

		
		void getInputs();
		void getInput();
		void update();
		void draw();


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

		static const int NB_COLONES_ENNEMI_DE_BASE_ANIMATION = 1;
		static const int NB_LIGNES_ENNEMI_DE_BASE_ANIMATION = 1;
		static const int NB_ANIMES_ENNEMI_DE_BASE_ANIMATION = 1;
		const std::string textureEnnemiDeBasePath = "Ressources\\Sprites\\ennemi_de_base.png";

		static const int NB_COLONES_ENNEMI_KAMIKAZE_ANIMATION = 1;
		static const int NB_LIGNES_ENNEMI_KAMIKAZE_ANIMATION = 1;
		static const int NB_ANIMES_ENNEMI_KAMIKAZE_ANIMATION = 1;
		const std::string textureEnnemiKamikazePath = "Ressources\\Sprites\\ennemi_kamikaze.png";

		static const int NB_COLONES_ENNEMI_LANCEUR_MISSILE_ANIMATION = 1;
		static const int NB_LIGNES_ENNEMI_LANCEUR_MISSILE_ANIMATION = 1;
		static const int NB_ANIMES_ENNEMI_LANCEUR_MISSILE_ANIMATION = 1;
		const std::string textureEnnemiLanceurMissilePath = "Ressources\\Sprites\\ennemi_lanceur_missiles.png";

		static const int NB_COLONES_ENNEMI_TURRET_ANIMATION = 1;
		static const int NB_LIGNES_ENNEMI_TURRET_ANIMATION = 1;
		static const int NB_ANIMES_ENNEMI_TURRET_ANIMATION = 1;
		const std::string textureEnnemiTurretPath = "Ressources\\Sprites\\ennemi_turret.png";
		
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

		Ennemi*  ennemi;
		vector<Ennemi*> ennemis;

		Animation * animations[NB_SPRITE_SHEET_ANIMATION];
		ProjectileManager * projectileManager;

		//touches
		std::map<Keyboard::Key, bool> inputs;

		View view;
		Event event;

		//Text pointage;
	};
}	