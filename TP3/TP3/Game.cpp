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
	delete joueur;
	return EXIT_SUCCESS;
}

bool Game::init()
{
	for(int i=0;i<nbBackground;i++)
	{
		if (!backgroundsT[i].loadFromFile("Ressources\\Backgrounds\\background.png"))
		{
			return false;
		}
		backgrounds[i] = new Sprite(backgroundsT[i]);
		backgrounds[i]->setPosition((limiteDroite/nbEspaceBackground)*i, 0);
	}
	joueur = new Joueur();
	joueur->init(limiteGauche,limiteDroite,limiteHaut, limiteBas);
	currentBackground = 0;
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
	joueur->velocity.x = 0;
	joueur->velocity.y = 0;
	deplacementBackgroundX = 0;
	//D�placement
	if (inputs[Keyboard::Left] && !inputs[Keyboard::Right])
	{
		joueur->velocity.x = -joueur->vitesse;
		deplacementBackgroundX = 1;
	}
	else if (inputs[Keyboard::Right] && !inputs[Keyboard::Left])
	{
		joueur->velocity.x = joueur->vitesse;
		deplacementBackgroundX = -1;
	}
	if (inputs[Keyboard::Up] && !inputs[Keyboard::Down])
	{
		joueur->velocity.y = -joueur->vitesse;
	}
	else if (inputs[Keyboard::Down] && !inputs[Keyboard::Up])
	{
		joueur->velocity.y = joueur->vitesse;
	}
	if (inputs[Keyboard::Space])
	{
		//joueur->Shoot();
	}
	//joueur->UpdateTexture(anime);
	joueur->move(joueur->velocity.x, joueur->velocity.y);
	//mouvement background
	currentBackground = (int)joueur->getPosition().x/LARGEURBACKGROUND;
	//test
	float test;
	test = joueur->getPosition().x;
	/*if (currentBackground == 1)
	{
		test = joueur->getPosition().x;
	}*/
	if(test>=(LARGEURBACKGROUND*currentBackground)+50  && currentBackground>0 && currentBackground<4)
	{
		backgrounds[currentBackground%2]->setPosition(LARGEURBACKGROUND*currentBackground+LARGEURBACKGROUND*2,0);
	}
	/*for (int i = 0; i<nbBackground; i++)
	{
		backgrounds[i]->move(deplacementBackgroundX, 0);
	}*/
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
}

void Game::draw()
{
	//Toujours important d'effacer l'�cran pr�c�dent
	mainWin->clear();
	for(int i=0;i<2;i++)
	{
		mainWin->draw(*backgrounds[i]);
	}
	mainWin->draw(*joueur);
	mainWin->display();
}