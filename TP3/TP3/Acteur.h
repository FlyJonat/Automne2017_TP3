#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>
#include <math.h>

using namespace sf;

//Jonathan 1535076 sauf pour IsColliding, Update, Shoot, GetIsCanShoot, variables de temps et d'accélération

namespace sideSpaceShooter
{
	class Acteur : public Sprite
	{
		Texture acteurSpriteT;
		std::string texturePath;

	public:
		Acteur(std::string texturePath);
		~Acteur();
		bool init(float limiteGauche, float limiteDroite, float limiteHaut, float limiteBas);
		bool IsColliding(FloatRect objet);
		void Move(const Vector2f direction);

		void Update();
		void Shoot();
		const bool GetIsCanShoot();

	protected:
		bool isCanShoot = true;
		
		int tempsEnFrameEntreDeuxTires = 15;
		int tempsDeRecharge = 0;

		float vitesseMax = 10;
		float accelerationParSeconde = 5;
		float autoDeccelerationParSeconde = 1.0;		
		float limiteDroite;
		float limiteGauche;
		float limiteHaut;
		float limiteBas;

		Vector2f velocity;

	};
}