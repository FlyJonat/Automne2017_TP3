#include "HUD.h"
using namespace sideSpaceShooter;
HUD::HUD()
{

}
HUD::~HUD()
{

}
void HUD::init()
{
	//textPlayerLife.setFont();
	//textPlayerLife.setFillColor(/*Modele::TEXTE_COULEUR*/);
	//textPlayerLife.setStyle(/*Modele::TEXTE_STYLE*/);
	textPlayerLife.setCharacterSize(16);
	//player.setString(Modele::GetText(Modele::PointageJeu) + std::to_string(score));
}
void HUD::ShowPlayerLife(Joueur joueur)
{
	playerLife = joueur.GetLife();
	textPlayerLife.setString(playerLife);
}