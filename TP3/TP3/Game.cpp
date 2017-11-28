#include "Game.h"


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
	/*for(int i=0;i<2;i++)
	{
		if (!backgroundsT[i].loadFromFile("Ressources\\Backgrounds\\background.png"))
		{
			return false;
		}
		backgrounds[i] = new Sprite(backgroundsT[i]);
		backgrounds[i]->setPosition(limiteDroite*i, 0);
	}*/
	if (!backgroundT.loadFromFile("Ressources\\Backgrounds\\background.png"))
	{
		return false;
	}
	joueur.init(limiteGauche,limiteDroite,limiteHaut, limiteBas);
	background = new Sprite(backgroundT);
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
	joueur.velocity.x = 0;
	joueur.velocity.y = 0;
	//Déplacement
	if (inputs[Keyboard::Left] && !inputs[Keyboard::Right])
	{
		joueur.velocity.x = -joueur.vitesse;
	}
	else if (inputs[Keyboard::Right] && !inputs[Keyboard::Left])
	{
		joueur.velocity.x = joueur.vitesse;
	}
	if (inputs[Keyboard::Up] && !inputs[Keyboard::Down])
	{
		joueur.velocity.y = -joueur.vitesse;
	}
	else if (inputs[Keyboard::Down] && !inputs[Keyboard::Up])
	{
		joueur.velocity.y = joueur.vitesse;
	}
	if (inputs[Keyboard::Space])
	{
		//joueur.Shoot();
	}
	//joueur.UpdateTexture(anime);
	joueur.move(joueur.velocity.x, joueur.velocity.y);

	//Vue
	if (joueur.getPosition().x - view.getSize().x / 2 > limiteGauche && joueur.getPosition().x + view.getSize().x / 2 < limiteDroite)
	{
		view.setCenter(joueur.getPosition().x, view.getCenter().y);
	}
	if(joueur.getPosition().y - view.getSize().y / 2 > limiteHaut && joueur.getPosition().y + view.getSize().y / 2 < limiteBas)
	{
		view.setCenter(view.getCenter().x, joueur.getPosition().y);
	}
	mainWin->setView(view);
}

void Game::draw()
{
	//Toujours important d'effacer l'écran précédent
	mainWin->clear();
	/*for(int i=0;i<2;i++)
	{
		mainWin->draw(*backgrounds[i]);
	}*/
	mainWin->draw(*background);
	mainWin->draw(joueur);
	mainWin->display();
}