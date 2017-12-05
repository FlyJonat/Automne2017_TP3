#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

//Laurent- 1562287

namespace sideSpaceShooter
{
	class Projectile : public Sprite
	{
	public:
		Projectile(int nbAnimation, float vitesseMax, float accelerationParSeconde, Vector2f position, Vector2f direction);
		void setPosition(const Vector2f& position);
		virtual void Update();
		virtual void Draw(RenderWindow& fenetre);
		bool IsColliding(const Vector2f& positionObjet, const int largeurObjet, const int hauteurObjet);
		void HaveToDie();
		bool GetHaveToDie();

	protected:
		int nbFrameFromBeginAnimation = 0;
		int currentAnimationNumber = 0;
		int nbAnimation = 0;
		float vitesseMax = 0;
		float accelerationParSeconde = 0;
		bool haveToDie = false;

		Vector2f direction;
		Vector2f velocity;
		Vector2f position;

		
	};
}
