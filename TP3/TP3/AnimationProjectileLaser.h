#pragma once
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;

namespace sideSpaceShooter
{
	class AnimationProjectileLaser : public Sprite
	{
	public:
		AnimationProjectileLaser();
		~AnimationProjectileLaser();
		bool init(const String texturePath);
		void SetProjectileTextureRect(int textureRectNum);
		void setPosition(const Vector2f& position);

	private :
		const int NBR_COLONES = 1;  //Total de colones dans la spriteSheet
		const int NBR_LIGNES = 11;  //Total de lignes dans la spriteSheet
		const int NUM_POSITION_ANIM_LASER = 0;
		const int NBR_ANIMS_LASER = 11;  //Nombre de frames d'animation pour la marche dans la spriteSheet.

		Texture texture;

		IntRect* intRectsLaser; //Tableau dynamique à deux dimensions pour des rectangles de découpage, pour les animations. 
	};
}
