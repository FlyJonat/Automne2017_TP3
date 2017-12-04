#pragma once
#include <stdexcept>
#include <string>
#include <math.h>
#include "Animation.h"

enum StateActeur{ stateActeurALife, stateActeurExploding, stateActeurDead };
enum ActeurType { acteurTypeOther, acteurTypeRandom, acteurTypePlayer, acteurTypeEnnemiDeBase, acteurTypeKamikaze, acteurTypeTurret, acteurTypeLanceurMissile, acteurTypeCarrier, acteurTypeBoss };
using namespace sf;

//Laurent- 1562287
//Jonathan 1535076 sauf pour IsColliding, Update, Shoot, GetIsCanShoot, variables de temps et d'accélération

namespace sideSpaceShooter
{
	class Acteur
	{

	public:
		Acteur(Animation * animationActeurSprite, Animation * animationActeurExplodingSprite, ActeurType ACTEUR_TYPE, Vector2f position);
		~Acteur();

		void Update();
		void UpdateAnimation();
		void Draw(RenderWindow& fenetre);
		void Move(const Vector2f direction);
		bool IsColliding(FloatRect objet);
		const StateActeur GetState();
		void Shoot();
		const bool GetReadyToAttack() const;
		const Vector2f GetPosition();
	protected:
		bool readyToAttack = true;
		
		int tempsEnFrameEntreDeuxTires = 0;
		int tempsDeRecharge = 0;

		int nbFrameFromBeginAnimation = 0;
		int currentAnimationNumber = 0;
		int timeInFrameForEachAnimations = 3;
		int nbAnimationExplosion = 12;
		int nbFramePourUnCycle = (timeInFrameForEachAnimations * nbAnimationExplosion)-1;

		float vitesseMax = 0;
		float accelerationParSeconde = 0;
		float autoDeccelerationParSeconde = 1.0;		
		float rotation = 0;

		const ActeurType ACTEUR_TYPE;

		StateActeur state = stateActeurALife; //Etat actuel de l'ennemi.
		StateActeur previousState = stateActeurALife; //Etat precedant de l'ennemi.

		Vector2f direction;
		Vector2f velocity;
		Vector2f position;

		Animation * animationsActeurSprites[2];

	};
}