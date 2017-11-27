#include "Game.h"


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
	if (!backgroundT.loadFromFile("Ressources\\Backgrounds\\background.png"))
	{
		return false;
	}
	joueur.init();
	//background = new Sprite(background);
	background = new Sprite(backgroundT);
	//"Ressources\\background.png"
	return true;
}

/*void Game::getInputs()
{
	//On passe l'�v�nement en r�f�rence et celui-ci est charg� du dernier �v�nement re�u!
	while (mainWin->pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed)
		{
			mainWin->close();
		}
	}
}*/
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
	joueur.velocity.x = 0;
	//D�placement
	if (inputs[Keyboard::Left] && !inputs[Keyboard::Right])
	{
		joueur.direction = Joueur::Direction::Gauche;
		joueur.velocity.x = -joueur.vitesse;
	}
	else if (inputs[Keyboard::Right] && !inputs[Keyboard::Left])
	{
		joueur.direction = Joueur::Direction::Droite;
		joueur.velocity.x = joueur.vitesse;
	}
	if (inputs[Keyboard::Space])
	{
		//joueur.Shoot();
	}
	//joueur.UpdateTexture(anime);
	joueur.move(joueur.velocity.x, joueur.velocity.y);
}

void Game::draw()
{
	//Toujours important d'effacer l'�cran pr�c�dent
	mainWin->clear();
	mainWin->draw(*background);
	mainWin->draw(joueur);
	mainWin->display();
}