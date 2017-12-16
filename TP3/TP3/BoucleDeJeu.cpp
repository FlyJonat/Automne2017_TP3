
#include <fstream>
#include <sstream>
#include "BoucleDeJeu.h"

using namespace sideSpaceShooter;
using namespace std;

//Laurent- 1562287

BoucleDeJeu::BoucleDeJeu()
{

}

BoucleDeJeu::~BoucleDeJeu()
{
	delete joueur;
	for (size_t i = 0; i < NB_SPRITE_SHEET_ANIMATION; ++i)
	{
		delete animations[i];
	}
	for (size_t i = 0; i < NB_BACKGROUND; ++i)
	{
		delete backgrounds[i];
	}
	for (size_t i = 0; i < MAX_TUILES; ++i)
	{
		delete grilleDeTuiles[i];
	}
	
	for (size_t i = 0; i < ennemis.size(); ++i)
	{
		delete ennemis[i];
	}
	delete projectileManager;
}
int BoucleDeJeu::testTest()
{
	return 0;
}

Scene::scenes BoucleDeJeu::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}
	return transitionVersScene;
}

bool BoucleDeJeu::init(RenderWindow * const window)
{
	deplacementBackgroundTotal = 0;

	for (size_t i = 0; i < NB_SPRITE_SHEET_ANIMATION; ++i)
	{
		animations[i] = nullptr;
	}

	animations[animationJoueur] = new Animation(NB_COLONES_JOUEUR_ANIMATION, NB_LIGNES_JOUEUR_ANIMATION, NB_ANIMES_JOUEUR_ANIMATION);
	if (!animations[animationJoueur]->init(textureJoueurPath))
	{
		return false;
	}
	
	animations[animationEnnemiDeBase] = new Animation(NB_COLONES_ENNEMI_DE_BASE_ANIMATION, NB_LIGNES_ENNEMI_DE_BASE_ANIMATION, NB_ANIMES_ENNEMI_DE_BASE_ANIMATION);
	if (!animations[animationEnnemiDeBase]->init(textureEnnemiDeBasePath))
	{
		return false;
	}

	animations[animationKamikaze] = new Animation(NB_COLONES_ENNEMI_KAMIKAZE_ANIMATION, NB_LIGNES_ENNEMI_KAMIKAZE_ANIMATION, NB_ANIMES_ENNEMI_KAMIKAZE_ANIMATION);
	if (!animations[animationKamikaze]->init(textureEnnemiKamikazePath))
	{
		return false;
	}

	animations[animationLanceurMissile] = new Animation(NB_COLONES_ENNEMI_LANCEUR_MISSILE_ANIMATION, NB_LIGNES_ENNEMI_LANCEUR_MISSILE_ANIMATION, NB_ANIMES_ENNEMI_LANCEUR_MISSILE_ANIMATION);
	if (!animations[animationLanceurMissile]->init(textureEnnemiLanceurMissilePath))
	{
		return false;
	}

	animations[animationTurret] = new Animation(NB_COLONES_ENNEMI_TURRET_ANIMATION, NB_LIGNES_ENNEMI_TURRET_ANIMATION, NB_ANIMES_ENNEMI_TURRET_ANIMATION);
	if (!animations[animationTurret]->init(textureEnnemiTurretPath))
	{
		return false;
	}

	animations[animationLaser] = new Animation(NB_COLONES_LASER_ANIMATION, NB_LIGNES_LASER_ANIMATION, NB_ANIMES_LASER_ANIMATION);
	if (!animations[animationLaser]->init(textureLaserPath))
	{
		return false;
	}

	animations[animationMissile] = new Animation(NB_COLONES_MISSILE_ANIMATION, NB_LIGNES_MISSILE_ANIMATION, NB_ANIMES_MISSILE_ANIMATION);
	if (!animations[animationMissile]->init(textureMissilePath))
	{
		return false;
	}

	animations[animationBouleDeFeu] = new Animation(NB_COLONES_BOULE_DE_FEU_ANIMATION, NB_LIGNES_BOULE_DE_FEU_ANIMATION, NB_ANIMES_BOULE_DE_FEU_ANIMATION);
	if (!animations[animationBouleDeFeu]->init(textureBouleDeFeuPath))
	{
		return false;
	}

	animations[animationProjectileExplosion] = new Animation(NB_COLONES_EXPLOSION_PROJECTILE_ANIMATION, NB_LIGNES_EXPLOSION_PROJECTILE_ANIMATION, NB_ANIMES_EXPLOSION_PROJECTILE_ANIMATION);
	if (!animations[animationProjectileExplosion]->init(textureExplosionProjectilePath))
	{
		return false;
	}

	
	// Chargement des sprites pour les tuiles
	for (int i = 0; i < NB_TUILES_METALIQUE; ++i)
	{
		if (!tuilesMetaliquesT[i].loadFromFile("Ressources\\Sprites\\bloc" + to_string(i) + ".png"))
		{
			return false;
		}
	}

	for (size_t i = 0; i < MAX_TUILES; i++)
	{
		grilleDeTuiles[i] = nullptr;
	}

	projectileManager = new ProjectileManager(grilleDeTuiles, MAX_TUILES, animations, NB_SPRITE_SHEET_ANIMATION);

	srand(time(NULL));

	Vector2f position;
	position.x = 0;
	position.y = 0;
	// On charge un niveau à partir d'un fichier .txt
	ifstream readLevel("Ressources\\Level\\level1.txt"); // Lecture d'un niveau par fichier texte
	string currentLine; // Ligne courante
	int levelLine = 0; // Indique à quel niveau du tableau on est rendu.
	int numTuile = 0;
	int numRandom = 0;
	while (getline(readLevel, currentLine))
	{
		if ((int)currentLine.at(0) != 35)
		{

			for (int i = 0; i < currentLine.length(); ++i)
			{

				int currentNumber = (int)currentLine.at(i);
				switch (currentNumber)
				{
				case 49: // Joueur
					position.x = (i * TAILLE_TUILES_X);
					position.y = (levelLine * TAILLE_TUILES_Y);
					joueur = new Joueur(animations[animationJoueur], animations[animationProjectileExplosion], position, projectileManager);
					break;
				case 50: // Obstacle
					numRandom = rand() % NB_TUILES_METALIQUE;
					grilleDeTuiles[numTuile] = new Sprite(tuilesMetaliquesT[numRandom]);
					grilleDeTuiles[numTuile]->setPosition(i * TAILLE_TUILES_X, levelLine* TAILLE_TUILES_Y);
					grilleDeTuiles[numTuile]->setOrigin(tuilesMetaliquesT[numRandom].getSize().x / 2, tuilesMetaliquesT[numRandom].getSize().y / 2);
					++numTuile;
					break;
				case 51: // 
					break;
				case 97: // Ennemi de base
					position.x = (i * TAILLE_TUILES_X);
					position.y = (levelLine * TAILLE_TUILES_Y);
					
					ennemi = new EnnemiDeBase(animations[animationEnnemiDeBase], animations[animationProjectileExplosion], position, projectileManager);
					ennemis.push_back(ennemi);
					
					break;
				case 98: // Ennemi Kamikaze
					position.x = (i * TAILLE_TUILES_X);
					position.y = (levelLine * TAILLE_TUILES_Y);

					ennemi = new EnnemiKamikaze(animations[animationKamikaze], animations[animationProjectileExplosion], position, projectileManager);
					ennemis.push_back(ennemi);

					break;

				case 99: // Ennemi lanceur de missile
					position.x = (i * TAILLE_TUILES_X);
					position.y = (levelLine * TAILLE_TUILES_Y);

					ennemi = new EnnemiLanceurMissile(animations[animationLanceurMissile], animations[animationProjectileExplosion], position, projectileManager);
					ennemis.push_back(ennemi);

					break;

				case 100: // Ennemi lanceur de missile
					position.x = (i * TAILLE_TUILES_X);
					position.y = (levelLine * TAILLE_TUILES_Y);

					ennemi = new EnnemiTurret(animations[animationTurret], animations[animationProjectileExplosion], position, projectileManager);
					ennemis.push_back(ennemi);

					break;
				
				default:
					break;
				}
			}
			levelLine++;
		}
	}

	

	//Initialisation du background
	for(int i = 0; i < NB_BACKGROUND; ++i)
	{
		if (!backgroundsT[i].loadFromFile("Ressources\\Backgrounds\\background.png"))
		{
			return false;
		}
		backgrounds[i] = new Sprite(backgroundsT[i]);
		backgrounds[i]->setPosition((limiteDroite / NB_ESPACE_BACKGROUND) * i, 0);
	}
	
	currentBackground = 0;
	//HUD::ShowPlayerLife(*joueur);
	//pointage = HUD::GetText();

	this->mainWin = window;
	isRunning = true;
	return true;
}

void BoucleDeJeu::getInputs()
{
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		getInput();
		if (event.type == Event::Closed)
		{
			mainWin->setView(view);
			isRunning = false;
			transitionVersScene = (scenes)vue.staySameWindow(0); // + 1 pour dire qu'il y a une incrémentation de plus, car si c'est égal à 0, on ne change pas de fenêtre.
		}
	}
}
void BoucleDeJeu::getInput()
{
	//x sur la fenêtre
	if (event.type == Event::Closed)
	{
		//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
		//fin à l'application
	}
	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			//isRunning = false;
		}
		else
		{
			inputs[event.key.code] = true;
		}
	}
	if (event.type == Event::KeyReleased)
	{
		if (event.key.code != Keyboard::Escape)
			inputs[event.key.code] = false;
	}
}
void BoucleDeJeu::update()
{
	joueur->Update();
	//Vérification si le joueur a eu une collision avec un bloc
	for (size_t i = 0; i < MAX_TUILES; i++)
	{
		if (grilleDeTuiles[i] != nullptr)
		{
			joueur->IsColliding(grilleDeTuiles[i]->getGlobalBounds());
		}
		else
		{
			break;
		}
	}
	Vector2f direction;
	direction.x = 0;
	direction.y = 0;
	deplacementBackgroundX = 0;
	//Déplacement
	if (inputs[Keyboard::Left] && !inputs[Keyboard::Right])
	{
		direction.x = -1;
	}
	else if (inputs[Keyboard::Right] && !inputs[Keyboard::Left])
	{
		direction.x = 1;
	}
	if (inputs[Keyboard::Up] && !inputs[Keyboard::Down])
	{
		direction.y = -1;
	}
	else if (inputs[Keyboard::Down] && !inputs[Keyboard::Up])
	{
		direction.y = 1;
	}

	joueur->Move(direction);

	deplacementBackgroundX = -0.1*joueur->GetDeplacement();

	if (inputs[Keyboard::Space] && joueur->GetReadyToAttack())
	{
		direction.x = 1;
		direction.y = 0;
		joueur->Shoot();
		projectileManager->GenerateProjectile(laser, joueur->GetPosition(), direction, terran);
	}

	
	for (size_t i = 0; i < ennemis.size(); ++i)
	{
		if (ennemis[i]->GetState() == stateActeurALife)
		{
			for (size_t j = 0; j < MAX_TUILES; ++j)
			{
				if (grilleDeTuiles[j] != nullptr)
				{
					if (ennemis[i]->GetType() != acteurTypeTurret)
					{
						if (ennemis[i]->IsColliding(grilleDeTuiles[j]->getGlobalBounds()))
						{
							break;
						}
					}			
				}
			}
			ennemis[i]->Update(joueur->GetPosition());
		}
	}

	projectileManager->Update();

	//mouvement background
	deplacementBackgroundTotal += deplacementBackgroundX;
	currentBackground = (int)joueur->GetPosition().x/ LARGEUR_BACKGROUND;
	float positionJoueurCalculBackground;
	positionJoueurCalculBackground = joueur->GetPosition().x;
	
	//Réapparition Background
	if(positionJoueurCalculBackground>=(LARGEUR_BACKGROUND*currentBackground)+(1000+deplacementBackgroundTotal)  && currentBackground>=0 && currentBackground<=NB_ESPACE_BACKGROUND)
	{
		if(currentBackground%2==0)
		{
			backgrounds[(currentBackground % 2) + 1]->setPosition((limiteDroite / NB_ESPACE_BACKGROUND)*(currentBackground + 1)+deplacementBackgroundTotal, 0);
		}
		else if (currentBackground % 2 == 1)
		{
			backgrounds[(currentBackground % 2) - 1]->setPosition((limiteDroite / NB_ESPACE_BACKGROUND)*(currentBackground + 1)+deplacementBackgroundTotal, 0);
		}
	}
	else if(positionJoueurCalculBackground <= (LARGEUR_BACKGROUND*(currentBackground+2)) - (1000+deplacementBackgroundTotal) && currentBackground>=0 && currentBackground<=NB_ESPACE_BACKGROUND)
	{
		if (currentBackground % 2 == 0)
		{
			backgrounds[(currentBackground % 2) + 1]->setPosition((limiteDroite / NB_ESPACE_BACKGROUND)*(currentBackground - 1)+deplacementBackgroundTotal, 0);
		}
		else if (currentBackground % 2 == 1)
		{
			backgrounds[(currentBackground % 2) - 1]->setPosition((limiteDroite / NB_ESPACE_BACKGROUND)*(currentBackground - 1)+deplacementBackgroundTotal, 0);
		}
	}
	//déplacement background
	for (int i = 0; i<NB_BACKGROUND; i++)
	{
		backgrounds[i]->move(deplacementBackgroundX, 0);
	}
	//Vue
	if (joueur->GetPosition().x - view.getSize().x / 2 > limiteGauche && joueur->GetPosition().x + view.getSize().x / 2 < limiteDroite)
	{
		view.setCenter(joueur->GetPosition().x, view.getCenter().y);
	}
	if(joueur->GetPosition().y - view.getSize().y / 2 > limiteHaut && joueur->GetPosition().y + view.getSize().y / 2 < limiteBas)
	{
		view.setCenter(view.getCenter().x, joueur->GetPosition().y);
	}
	
	mainWin->setView(view);

	++timer;
}

void BoucleDeJeu::draw()
{
	//Toujours important d'effacer l'écran précédent
	mainWin->clear();
	for(int i = 0; i < 2; i++)
	{
		mainWin->draw(*backgrounds[i]);
	}

	for (size_t i = 0; i < MAX_TUILES; i++)
	{
		if (grilleDeTuiles[i] != nullptr)
		{
			mainWin->draw(*grilleDeTuiles[i]);
		}
		else
		{
			break;
		}
	}
	projectileManager->Drawn(*mainWin);
	joueur->Draw(*mainWin);
	for (size_t i = 0; i < ennemis.size(); i++)
	{
		ennemis[i]->Draw(*mainWin);
	}
	//mainWin->draw(pointage);
	mainWin->display();
}
