#include "AnimationProjectileLaser.h"

using namespace sideSpaceShooter;

AnimationProjectileLaser::AnimationProjectileLaser()
{
	
}

AnimationProjectileLaser::~AnimationProjectileLaser()
{
	delete intRectsLaser;
}

bool AnimationProjectileLaser::init(const String texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}

	setTexture(texture);
	intRectsLaser = new IntRect[NBR_ANIMS_LASER];


	int largeur = texture.getSize().x / NBR_COLONES; //On calcule la largeur et la hauteur à partir de la taille de la texture
	int hauteur = texture.getSize().y / NBR_LIGNES; //et des nombres d'animations


	for (int i = 0; i < NBR_ANIMS_LASER; ++i)
	{
		intRectsLaser[i].left = largeur * NUM_POSITION_ANIM_LASER;
		intRectsLaser[i].top = hauteur * i;
		intRectsLaser[i].width = largeur;
		intRectsLaser[i].height = hauteur;
	}

	//Le rectangle d'animation initial
	setTextureRect(intRectsLaser[0]);
	setOrigin(intRectsLaser[0].height / 2, intRectsLaser[0].width / 2);
	return true;
}

void AnimationProjectileLaser::SetProjectileTextureRect(int textureRectNum)
{
	setTextureRect(intRectsLaser[textureRectNum]);
}

/// <summary>
/// Sets the position.
/// </summary>
/// <param name="position">The position.</param>
void AnimationProjectileLaser::setPosition(const Vector2f& position)
{
	Sprite::setPosition(position);
}