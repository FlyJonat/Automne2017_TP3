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
	//background
	int nbBackground=2;
	int nbEspaceBackground = 5;
	float deplacementBackgroundX;
	int currentBackground;
	Texture backgroundsT[2];
	Sprite* backgrounds[2];
	const int LARGEUR = 1280;
	const int HAUTEUR = 720;
	const int LARGEURBACKGROUND = 2294;

	const float limiteGauche = 0;
	const float limiteDroite = LARGEURBACKGROUND*nbEspaceBackground;
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
	Joueur* joueur;
	//touches
	std::map<Keyboard::Key, bool> inputs;
	
};