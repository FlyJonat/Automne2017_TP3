#pragma once
#include "Acteur.h"
class Joueur:public Acteur
{
public:
	Joueur();
	~Joueur();
	void move(const float offSetX, const float offSetY);
};