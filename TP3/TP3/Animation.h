#pragma once
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;

//Laurent- 1562287

enum ActeurType { animationLaser, animationMissile, animationBouleDeFeu, animationProjectileExplosion, animationActeurExplosion, animationBosseExplosion};

namespace sideSpaceShooter
{
	class Animation : public Sprite
	{
	public:
		Animation(const int nbColones, const int nbLignes, const int nbAnimes);
		~Animation();
		bool init(const String texturePath);
		void SetProjectileTextureRect(int textureRectNum);
		

	private :
		int nbColones = 0;  //Total de colones dans la spriteSheet
		int nbLignes = 0;  //Total de lignes dans la spriteSheet
		int nbAnimes = 0;  //Nombre de frames d'animation pour la marche dans la spriteSheet.

		Texture texture;

		IntRect* intRectsAnimation; //Tableau dynamique à deux dimensions pour des rectangles de découpage, pour les animations. 
	};
}
