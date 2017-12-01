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
		float vitesse = 20;
		void move(const float offSetX, const float offSetY);
		bool init(float limiteGauche,float limiteDroite, float limiteHaut, float limiteBas);
		float limiteDroite;
		float limiteGauche;
		float limiteHaut;
		float limiteBas;
	};