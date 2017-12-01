#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

using namespace sf;

namespace sideSpaceShooter
{
	class Acteur : public Sprite
	{
		Texture acteurSpriteT;
		std::string texturePath;

	public:
		Acteur(std::string texturePath);
		~Acteur();

	//protected:
		enum Direction { Droite, Gauche, Haut, Bas, Immobile };
		Direction direction = Direction::Immobile;
		Vector2f velocity;
		float vitesse = 10;
		void move(const float offSetX, const float offSetY);
		bool init(float limiteGauche, float limiteDroite, float limiteHaut, float limiteBas);
		float limiteDroite;
		float limiteGauche;
		float limiteHaut;
		float limiteBas;

	};
}