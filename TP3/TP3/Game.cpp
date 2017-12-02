#include "Game.h"
#include <fstream>
#include <sstream>

using namespace sideSpaceShooter;
using namespace std;

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
	delete animationProjectileLaser;

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
	joueur = new Joueur();
	joueur->init(limiteGauche, limiteDroite, limiteHaut, limiteBas);
<<<<<<< HEAD

	animationProjectileLaser = new AnimationProjectileLaser();
	if (!animationProjectileLaser->init(textureLaserPath))
	{
		return false;
	}
	
=======
	deplacementBackgroundTotal = 0;
>>>>>>> 5f6de0807e64caa002bbcbc0fa481285b9e48636

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
					joueur->setPosition((i * TAILLE_TUILES_X), (levelLine * TAILLE_TUILES_Y));
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

/*void Game::getInputs()
{
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			mainWin->close();
		}
	}
}*/
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
		deplacementBackgroundX = 1;
	}
	else if (inputs[Keyboard::Right] && !inputs[Keyboard::Left])
	{
		direction.x = 1;
		deplacementBackgroundX = -1;
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

	if (inputs[Keyboard::Space] && joueur->GetIsCanShoot())
	{
		joueur->Shoot();
		Vector2f directionProjectile;
		directionProjectile.x = 1;
		directionProjectile.y = 0;
		Vector2f positionProjectile;
		positionProjectile.x = joueur->getPosition().x;
		positionProjectile.y = joueur->getPosition().y + (joueur->getOrigin().y  * joueur->GetNextShotOffset());
		//Création du projectile
		Projectile* p = new ProjectileLaser(animationProjectileLaser, 11, 60.0f, 60.0f, positionProjectile, directionProjectile);
		projectiles.push_back(p);
	}
	//Vérifie la collision entre un projectile et une tuile.
	for (size_t i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->Update();

		//for (size_t j = 0; i < MAX_TUILES; ++j)
		//{
		//	if (grilleDeTuiles[j] != nullptr)
		//	{
		//		//Détruit le projectile en cas de collision.
		//		if (projectiles[i]->IsColliding(grilleDeTuiles[j]->getPosition(), TAILLE_TUILES_X, TAILLE_TUILES_Y))
		//		{
		//			projectiles[i]->HaveToDie();
		//		}
		//	}
		//}	
		//Vérifie la collision entre le joueur et un projectile. Le joueur meurt en cas de collision.
		/*if (projectiles[i]->IsColliding(joueur->getPosition(), TAILLE_TUILES_X, TAILLE_TUILES_Y))
		{
			joueur->setStartDying();
		}*/
	}

	//mouvement background
	deplacementBackgroundTotal += deplacementBackgroundX;
	currentBackground = (int)joueur->getPosition().x/ LARGEUR_BACKGROUND;
	//test
	float test;
	test = joueur->getPosition().x;
	//test
	/*if (currentBackground == 2)
	{
		test = joueur->getPosition().x;
	}*/
	//Réapparition Background
	if(test>=(LARGEUR_BACKGROUND*currentBackground)+(1000+deplacementBackgroundTotal)  && currentBackground>=0 && currentBackground<=NB_ESPACE_BACKGROUND)
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
	else if(test <= (LARGEUR_BACKGROUND*(currentBackground+2)) - (1000+deplacementBackgroundTotal) && currentBackground>=0 && currentBackground<=NB_ESPACE_BACKGROUND)
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
	if (joueur->getPosition().x - view.getSize().x / 2 > limiteGauche && joueur->getPosition().x + view.getSize().x / 2 < limiteDroite)
	{
		view.setCenter(joueur->getPosition().x, view.getCenter().y);
	}
	if(joueur->getPosition().y - view.getSize().y / 2 > limiteHaut && joueur->getPosition().y + view.getSize().y / 2 < limiteBas)
	{
		view.setCenter(view.getCenter().x, joueur->getPosition().y);
	}
	
	mainWin->setView(view);

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

	mainWin->draw(*joueur);
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
		if (projectiles[i]->GetHaveToDie())
		{
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
		}
	}
}