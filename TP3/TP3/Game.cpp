#include "Game.h"
#include <fstream>
#include <sstream>

using namespace sideSpaceShooter;
using namespace std;

//Laurent- 1562287

Game::Game()
{
	//On place dans le contructeur ce qui permet à la game elle-même de fonctionner

	mainWin->create(VideoMode(LARGEUR, HAUTEUR, 32), "Le titre de mon jeu");  // , Style::Titlebar); / , Style::FullScreen);
	view = mainWin->getDefaultView();

	//Synchonisation coordonnée à l'écran!  Normalement 60 frames par secondes. À faire absolument
	mainWin->setVerticalSyncEnabled(true);
	//mainWin.setFramerateLimit(60);  //Équivalent... normalement, mais pas toujours. À utiliser si la synchonisation de l'écran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/2.0/window-window.php#controlling-the-framerate
}

Game::~Game()
{
	delete joueur;
	
	for (size_t i = 0; i < NB_SPRITE_SHEET_ANIMATION; ++i)
	{
		delete animations[i];
	}
	for (size_t i = 0; i < NB_BACKGROUND; i++)
	{
		delete backgrounds[i];
	}
	for (size_t i = 0; i < MAX_TUILES; i++)
	{
		delete grilleDeTuiles[i];
	}
	for (int i = 0; i < projectiles.size(); i++)
	{
		delete projectiles[i];
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

	for (size_t i = 0; i < NB_SPRITE_SHEET_ANIMATION; ++i)
	{
		animations[i] = nullptr;
	}

	animations[animationJoueur] = new Animation(NB_COLONES_JOUEUR_ANIMATION, NB_LIGNES_JOUEUR_ANIMATION, NB_ANIMES_JOUEUR_ANIMATION);
	if (!animations[animationJoueur]->init(textureJoueurPath))
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
					joueur = new Joueur(animations[animationJoueur], animations[animationProjectileExplosion], acteurTypePlayer, position);
					break;
				case 50: // Sol
					numRandom = rand() % NB_TUILES_METALIQUE;
					grilleDeTuiles[numTuile] = new Sprite(tuilesMetaliquesT[numRandom]);
					grilleDeTuiles[numTuile]->setPosition(i * TAILLE_TUILES_X, levelLine* TAILLE_TUILES_Y);
					grilleDeTuiles[numTuile]->setOrigin(tuilesMetaliquesT[numRandom].getSize().x / 2, tuilesMetaliquesT[numRandom].getSize().y / 2);
					++numTuile;
					break;
				case 51: // Plateforme
					break;
				case 52: // Ennemi 0

					break;
				case 53: // Ennemi 1

					break;
				case 54: // Ennemi 2

					break;
				case 55: // Bouffe

					break;
				case 56: // SortieF

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
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		getInput();
		if (event.type == Event::Closed)
		{
			mainWin->close();
		}
	}
}
void Game::getInput()
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
void Game::update()
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
		joueur->Shoot();
		Vector2f directionProjectile;
		directionProjectile.x = 1;
		directionProjectile.y = 0;
		Vector2f positionProjectile;
		positionProjectile.x = joueur->GetPosition().x;
		positionProjectile.y = joueur->GetPosition().y;
		//Création du projectile
		//Projectile* p = new ProjectileLaser(animations[animationLaser], animations[animationProjectileExplosion], 11,  positionProjectile, directionProjectile);
		//projectiles.push_back(p);

		/*Projectile* a = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, positionProjectile, directionProjectile);
		projectiles.push_back(a);
		directionProjectile.y = 1;
		Projectile* b = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, positionProjectile, directionProjectile);
		projectiles.push_back(b);
		directionProjectile.y = -1;
		Projectile* c = new ProjectileBouleDeFeu(animations[animationBouleDeFeu], animations[animationProjectileExplosion], 6, positionProjectile, directionProjectile);		
		projectiles.push_back(c);*/

		Projectile* d = new ProjectileMissile(animations[animationMissile], animations[animationProjectileExplosion], 8, positionProjectile, directionProjectile);
		projectiles.push_back(d);

	}
	//Vérifie la collision entre un projectile et une tuile.
	for (size_t i = 0; i < projectiles.size(); ++i)
	{
		
		if (projectiles[i]->GetState() == stateProjectileMoving)
		{
			for (size_t j = 0; j < MAX_TUILES; ++j)
			{
				if (grilleDeTuiles[j] != nullptr)
				{
					//Détruit le projectile en cas de collision.
					if (projectiles[i]->IsColliding(grilleDeTuiles[j]->getGlobalBounds()))
					{
						projectiles[i]->Exploding();
						break;
					}
				}
			}
		}
		
		projectiles[i]->Update();
		//Vérifie la collision entre le joueur et un projectile. Le joueur meurt en cas de collision.
		/*if (projectiles[i]->IsColliding(joueur->getPosition(), TAILLE_TUILES_X, TAILLE_TUILES_Y))
		{
			joueur->setStartDying();
		}*/
	}

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

	checkIfIsDead();
	++timer;
}

void Game::draw()
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

	joueur->Draw(*mainWin);
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
	//Vérifie les projectiles morts
	for (size_t i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->GetState() == stateProjectileDead)
		{
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
		}
	}
}