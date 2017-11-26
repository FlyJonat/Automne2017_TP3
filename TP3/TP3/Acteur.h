#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
using namespace sf;
class Acteur : public Sprite
{
	Texture acteurSpriteT;
public:
	Acteur(/*std::string texturePath*/);
	~Acteur();
	Sprite* acteurSprite;
	
};