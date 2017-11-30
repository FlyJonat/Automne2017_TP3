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

	const float limiteGauche = 0;
	const float limiteDroite = 2294*2;
	const float limiteHaut = 0;
	const float limiteBas = 1200;

	bool init();
	void getInputs();
	void getInput();
	void update();
	void draw();
	
	View view;
	Event event;
	//Acteur
	Joueur joueur;
	//touches
	std::map<Keyboard::Key, bool> inputs;
	//background
	int nbBackground;
	float deplacementBackgroundX;
	float deplacementBackgroundY;
	Texture backgroundsT[2];
	Sprite* backgrounds[2];
};