#include "EnnemiDeBase.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

EnnemiDeBase::EnnemiDeBase(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, Vector2f position) : Ennemi(animationProjectileSprite, animationProjectileExplodingSprite, position)
{
	scoreValue = 10;
	acteurType = acteurTypeEnnemiDeBase;
	vitesseMax = 6;
	accelerationParSeconde = 6;
	tempsEnFrameEntreDeuxTires = 60;
}

EnnemiDeBase::~EnnemiDeBase()
{

}

void EnnemiDeBase::Update(Vector2f playerPosition)
{
	Acteur::Update();
	if (Ennemi::LookForPlayer(playerPosition))
	{
		wantToAttack = true;
	}
	else
	{
		wantToAttack = false;
	}
}
