#include "EnnemiDeBase.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

EnnemiDeBase::EnnemiDeBase(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, const int SCORE_VALUE, ActeurType ACTEUR_TYPE, Vector2f position) : Ennemi(animationProjectileSprite, animationProjectileExplodingSprite, SCORE_VALUE, ACTEUR_TYPE, position)
{
	vitesseMax = 6;
	accelerationParSeconde = 6;
	tempsEnFrameEntreDeuxTires = 60;
}

EnnemiDeBase::~EnnemiDeBase()
{

}

void EnnemiDeBase::Update()
{
	

}

