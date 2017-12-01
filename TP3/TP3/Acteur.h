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
		bool IsColliding(FloatRect objet);
		void ResetCantMove();

	//protected:
		enum Direction { Droite, Gauche, Haut, Bas, Immobile };
		Direction direction = Direction::Immobile;
		Vector2f velocity;
		float vitesseMax = 10;
		float accelerationParSeconde = 5;
		float autoDeccelerationParSeconde = 2.5;
		void move(const Vector2f direction);
		bool init(float limiteGauche, float limiteDroite, float limiteHaut, float limiteBas);
		float limiteDroite;
		float limiteGauche;
		float limiteHaut;
		float limiteBas;
		bool cantMoveLeft = false; //Indique si l'acteur ne peut pas se deplacer vers la gauche.
		bool cantMoveRight = false; //Indique si l'acteur ne peut pas se deplacer vers la droite.
		bool cantMoveTop = false; //Indique si l'acteur ne peut pas se deplacer vers le haut.
		bool cantMoveBot = false; //Indique si l'acteur ne peut pas se deplacer vers le bas.

	};
}