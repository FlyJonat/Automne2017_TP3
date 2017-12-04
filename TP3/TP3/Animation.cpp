#include "Animation.h"

using namespace sideSpaceShooter;

Animation::Animation(const int nbColones, const int nbLignes, const int nbAnimes): nbColones(nbColones), nbLignes(nbLignes), nbAnimes(nbAnimes)
{
	
}

Animation::~Animation()
{
	delete intRectsAnimation;
}

bool Animation::init(const String texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}

	setTexture(texture);
	intRectsAnimation = new IntRect[nbAnimes];


	int largeur = texture.getSize().x / nbColones; //On calcule la largeur et la hauteur à partir de la taille de la texture
	int hauteur = texture.getSize().y / nbLignes; //et des nombres d'animations

	int x = 0; 
	for (size_t i = 0; i < nbLignes; i++)
	{
		for (size_t j = 0; j < nbColones; ++j)
		{
			if (nbAnimes >= i*j)
			{
				intRectsAnimation[x].left = largeur * j;
				intRectsAnimation[x].top = hauteur * i;
				intRectsAnimation[x].width = largeur;
				intRectsAnimation[x].height = hauteur;
				++x;
			}
			else
			{
				break;
			}
		}
	}
	

	//Le rectangle d'animation initial
	setTextureRect(intRectsAnimation[0]);
	setOrigin(intRectsAnimation[0].height / 2, intRectsAnimation[0].width / 2);
	return true;
}

void Animation::SetProjectileTextureRect(int textureRectNum)
{
	setTextureRect(intRectsAnimation[textureRectNum]);
}
