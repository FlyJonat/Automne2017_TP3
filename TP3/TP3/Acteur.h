#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
using namespace sf;
	class Acteur : public Sprite
	{
		Texture acteurSpriteT;
		std::string texturePath;
	public:
		Acteur(std::string texturePath);
		~Acteur();
		enum Direction { Droite, Gauche, Haut, Bas, Immobile };
		Direction direction = Direction::Immobile;
		Vector2f velocity;
		float vitesse = 5;
		virtual void move(const float offSetX, const float offSetY);
		bool init();
	};