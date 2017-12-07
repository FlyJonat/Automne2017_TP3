#pragma once
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;
using namespace std;

enum StateProjectile { stateProjectileMoving, stateProjectileExploding, stateProjectileDead };
enum ProjectileType{laser, bouleDeFeu, missile};
//Laurent- 1562287

namespace sideSpaceShooter
{
	class Projectile : public Sprite
	{
	public:
		Projectile(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, int nbAnimation, Vector2f position, Vector2f direction);
		void setPosition(const Vector2f& position);
		virtual void Update();
		void Draw(RenderWindow& fenetre);
		const bool IsColliding(FloatRect objet);
		void Exploding();
		const FloatRect GetGlobalBounds();
		const StateProjectile GetState();

	protected:
		int GetRandomNum(int max);
		int nbFrameFromBeginAnimation = 0;
		int currentAnimationNumber = 0;	
		int nbFramePourUnCycle = 0;
		int nbAnimation = 0;
		int timeInFrameForEachAnimations = 6;
		float vitesseMax = 0;
		float accelerationParSeconde = 0;
		float rotation = 0;
	

		StateProjectile state = stateProjectileMoving; //Etat actuel du projectile.
		StateProjectile previousState = stateProjectileMoving; //Etat precedant du projectile.

		Vector2f direction;
		Vector2f velocity;
		Vector2f position;

		Animation * animationsProjectilesSprites[2];
		
	};
}
