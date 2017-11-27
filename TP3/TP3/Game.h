#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Joueur.h"

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
	void getInput();
	void update();
	void draw();

	//Statique pour �viter les erreurs, � revoir
	
	View view;
	Event event;
	//test 
	Sprite* background;
	Texture backgroundT;
	//Acteur
	Joueur joueur;
	//touches
	std::map<Keyboard::Key, bool> inputs;
};