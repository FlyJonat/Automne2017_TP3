# include "Projectile.h"

//Laurent- 1562287

using namespace sideSpaceShooter;

Projectile::Projectile(Animation * animationProjectileSprite, Animation * animationProjectileExplodingSprite, int nbAnimation, Vector2f position, Vector2f direction) : nbAnimation(nbAnimation), position(position), direction(direction)
{
	this->animationsProjectilesSprites[stateProjectileMoving] = animationProjectileSprite;
	this->animationsProjectilesSprites[stateProjectileExploding] = animationProjectileExplodingSprite;
	nbFramePourUnCycle = (nbAnimation * timeInFrameForEachAnimations) -1;
	srand(time(NULL));
}


/// <summary>
/// Sets the position.
/// </summary>
/// <param name="position">The position.</param>
void Projectile::setPosition(const Vector2f& position)
{
	this->position = position;
}

/// <summary>
/// Updates this instance.
/// </summary>
void Projectile::Update()
{
	
}

/// <summary>
/// Draws the specified fenetre.
/// </summary>
/// <param name="fenetre">The fenetre.</param>
void Projectile::Draw(RenderWindow& fenetre)
{
	if (state != stateProjectileDead)
	{
		animationsProjectilesSprites[state]->setRotation(rotation);
		animationsProjectilesSprites[state]->setPosition(position);
		animationsProjectilesSprites[state]->SetProjectileTextureRect(currentAnimationNumber);

		fenetre.draw(*animationsProjectilesSprites[state]);
	}
}


const bool Projectile::IsColliding(FloatRect objet)
{

	animationsProjectilesSprites[state]->setPosition(position);
	if (animationsProjectilesSprites[state]->getGlobalBounds().intersects(objet))
	{
		return true;
	}
	return false;
}

const bool Projectile::IsCollidingPixelPerfect(const Animation *objet)
{
	FloatRect Intersection;

	if (animationsProjectilesSprites[state]->getGlobalBounds().intersects(objet->getGlobalBounds(), Intersection))
	{
		IntRect thisSubRect = animationsProjectilesSprites[state]->getTextureRect();
		IntRect autreSubRect = objet->getTextureRect();

		unsigned char* mask1 = bitmasks.getMask(animationsProjectilesSprites[state]->getTexture());
		unsigned char* mask2 = bitmasks.getMask(objet->getTexture());

		// Loop through our pixels
		for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++)
		{
			for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++)
			{

				Vector2f thisVector = animationsProjectilesSprites[state]->getInverseTransform().transformPoint(i, j);
				Vector2f autreVector = objet->getInverseTransform().transformPoint(i, j);

				// Make sure pixels fall within the sprite's subrect
				if (thisVector.x > 0 && thisVector.y > 0 && autreVector.x > 0 && autreVector.y > 0 &&
					thisVector.x < thisSubRect.width && thisVector.y < thisSubRect.height &&
					autreVector.x < autreSubRect.width && autreVector.y < autreSubRect.height)
				{
					if (bitmasks.getPixel(mask1, animationsProjectilesSprites[state]->getTexture(), (int)(thisVector.x) + thisSubRect.left, (int)(thisVector.y) + thisSubRect.top) > 0 &&
						bitmasks.getPixel(mask2, objet->getTexture(), (int)(autreVector.x) + autreSubRect.left, (int)(autreVector.y) + autreSubRect.top) > 0)
						return true;

				}
			}
		}
	}
	return false;
}

/// <summary>
/// Haves to die.
/// </summary>
void Projectile::Exploding()
{
	state = stateProjectileExploding;
	rotation = GetRandomNum(360);
}

const StateProjectile Projectile::GetState() const
{
	return state;
}

int Projectile::GetRandomNum(int max)
{
	int numRandom = 0;
	return numRandom = rand() % max;
}

const FloatRect Projectile::GetGlobalBounds() const
{
	animationsProjectilesSprites[state]->setPosition(position);
	return animationsProjectilesSprites[state]->getGlobalBounds();
}

const int Projectile::GetDammage() const
{
	return dammage;
}