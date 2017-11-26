#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Acteur.h"

using namespace sf;

class Game
{
public:
	Game();
	int run();
	int testTest();
	RenderWindow *mainWin = new RenderWindow;
private:
	const int LARGEUR = 1280;
	const int HAUTEUR = 720;

	bool init();
	void getInputs();
	void update();
	void draw();

	//Statique pour éviter les erreurs, à revoir
	
	View view;
	Event event;
	//test 
	Sprite* background;
	Texture backgroundT;
	//Acteur
	Acteur joueur;
};