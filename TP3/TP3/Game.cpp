#include "Game.h"
#include <fstream>
#include <sstream>

using namespace sideSpaceShooter;
using namespace std;

Game::Game()
{
	//On place dans le contructeur ce qui permet � la game elle-m�me de fonctionner

	mainWin->create(VideoMode(LARGEUR, HAUTEUR, 32), "Le titre de mon jeu");  // , Style::Titlebar); / , Style::FullScreen);
	view = mainWin->getDefaultView();

	//Synchonisation coordonn�e � l'�cran!  Normalement 60 frames par secondes. � faire absolument
	mainWin->setVerticalSyncEnabled(true);
	//mainWin.setFramerateLimit(60);  //�quivalent... normalement, mais pas toujours. � utiliser si la synchonisation de l'�cran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.0/window-window.php#controlling-the-framerate
}

Game::~Game()
{
	delete joueur;
	}
	for (size_t i = 0; i < NB_BACKGROUND; ++i)
	{
		delete backgrounds[i];
	}
	for (size_t i = 0; i < MAX_TUILES; ++i)
	{
		delete grilleDeTuiles[i];
	}
	for (size_t i = 0; i < projectiles.size(); ++i)
	{
		delete projectiles[i];
	}
	for (size_t i = 0; i < ennemis.size(); ++i)
	{
		delete ennemis[i];
	}
}
int Game::testTest()
{
	return 0;
}

int Game::run()
{
	if (!init())
	{
		return EXIT_FAILURE;
	}

	while (mainWin->isOpen())
	{
		getInputs();
		update();
		draw();
	}
	return EXIT_SUCCESS;
}

bool Game::init()
{
	deplacementBackgroundTotal = 0;

	{
		return false;
	}
	
	animations[animationEnnemiDeBase] = new Animation(NB_COLONES_ENNEMI_DE_BASE_ANIMATION, NB_LIGNES_ENNEMI_DE_BASE_ANIMATION, NB_ANIMES_ENNEMI_DE_BASE_ANIMATION);
	if (!animations[animationEnnemiDeBase]->init(textureEnnemiDeBasePath))
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
	srand(time(NULL));

	// On charge un niveau � partir d'un fichier .txt
	ifstream readLevel("Ressources\\Level\\level1.txt"); // Lecture d'un niveau par fichier texte
	string currentLine; // Ligne courante
	int levelLine = 0; // Indique � quel niveau du tableau on est rendu.
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
					joueur = new Joueur(animations[animationJoueur], animations[animationProjectileExplosion], position);
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
					
					ennemi = new EnnemiDeBase(animations[animationEnnemiDeBase], animations[animationProjectileExplosion], position);
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
	return true;
}

void Game::getInputs()
{
	//On passe l'�v�nement en r�f�rence et celui-ci est charg� du dernier �v�nement re�u!
	while (mainWin->pollEvent(event))
	{
		//x sur la fen�tre
		getInput();
		if (event.type == Event::Closed)
		{
			mainWin->close();
		}
	}
}
void Game::getInput()
{
	//x sur la fen�tre
	if (event.type == Event::Closed)
	{
		//Attention, ici simplement fermer la fen�tre ne mettrait pas n�cessairement 
		//fin � l'application
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
void Game::update()
{
	joueur->Update();
	//V�rification si le joueur a eu une collision avec un bloc
	for (size_t i = 0; i < MAX_TUILES; i++)
	{
		if (grilleDeTuiles[i] != nullptr)
		{
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
	//D�placement
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

	deplacementBackgroundX = -0.1*joueur->GetDeplacement();

	{
		joueur->Shoot();
		Vector2f directionProjectile;
		directionProjectile.x = 1;
		directionProjectile.y = 0;
		Vector2f positionProjectile;
		//Cr�ation du projectile
		Projectile* p = new ProjectileLaser(animations[animationLaser], animations[animationProjectileExplosion], 11,  positionProjectile, directionProjectile);
		projectiles.push_back(p);

		/*Projectile* a = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, positionProjectile, directionProjectile);
		projectiles.push_back(a);
		directionProjectile.y = 1;
		Projectile* b = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, positionProjectile, directionProjectile);
		projectiles.push_back(b);
		directionProjectile.y = -1;
		Projectile* c = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, positionProjectile, directionProjectile);		
		projectiles.push_back(c);*/

		/*Projectile* d = new ProjectileMissile(animations[animationMissile], animations[animationProjectileExplosion], 8, positionProjectile, directionProjectile);
		projectiles.push_back(d);*/

	}

	//V�rifie la collision entre un projectile et une tuile.
	for (size_t i = 0; i < ennemis.size(); ++i)
	{
		if (ennemis[i]->GetState() == stateActeurALife)
		{
			//for (size_t j = 0; j < MAX_TUILES; ++j)
			//{
			//	if (grilleDeTuiles[j] != nullptr)
			//	{
			//		//D�truit le projectile en cas de collision.
			//		if (ennemis[i]->IsColliding(grilleDeTuiles[j]->getGlobalBounds()))
			//		{
			//			break;
			//		}
			//	}
			//}
			ennemis[i]->Update(joueur->GetPosition());
			if (ennemis[i]->GetReadyToAttack() && ennemis[i]->GetWantToAttack())
			{
				Vector2f directionProjectile;
				directionProjectile.x = -1;
				directionProjectile.y = 0;
				Vector2f positionProjectile;
				positionProjectile.x = ennemis[i]->GetPosition().x;
				positionProjectile.y = ennemis[i]->GetPosition().y;
				Projectile* p = new ProjectileLaser(animations[animationLaser], animations[animationProjectileExplosion], 11, positionProjectile, directionProjectile);
				projectiles.push_back(p);
				ennemis[i]->Shoot();
			}
		}
	}

	//V�rifie la collision entre un projectile et une tuile.
	for (size_t i = 0; i < projectiles.size(); ++i)
	{
		projectiles[i]->Update();
		//V�rifie la collision entre le joueur et un projectile. Le joueur meurt en cas de collision.
		/*if (projectiles[i]->IsColliding(joueur->getPosition(), TAILLE_TUILES_X, TAILLE_TUILES_Y))
		{
			joueur->setStartDying();
		}*/
	}

	//mouvement background
	deplacementBackgroundTotal += deplacementBackgroundX;
	float positionJoueurCalculBackground;
	
	//R�apparition Background
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
	//d�placement background
	for (int i = 0; i<NB_BACKGROUND; i++)
	{
		backgrounds[i]->move(deplacementBackgroundX, 0);
	}
	//Vue
	{
	}
	{
	}
	
	mainWin->setView(view);

	++timer;
}

void Game::draw()
{
	//Toujours important d'effacer l'�cran pr�c�dent
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

	for (size_t i = 0; i < ennemis.size(); i++)
	{
		ennemis[i]->Draw(*mainWin);
	}
	for (size_t i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->Draw(*mainWin);
	}
	mainWin->display();
}

/// <summary>
/// Checks if is dead.
/// </summary>
void Game::checkIfIsDead()
{
	//V�rifie les projectiles morts
	for (size_t i = 0; i < projectiles.size(); i++)
	{
		{
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
		}
	}
}