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
	textPlayerLife.setFillColor(/*Modele::TEXTE_COULEUR*/Color::White);
	textPlayerLife.setStyle(/*Modele::TEXTE_STYLE*/Text::Style::Regular);
	textPlayerLife.setCharacterSize(16);
	//playerLife.setString("");
}
void HUD::ShowPlayerLife(Joueur joueur)
{
	playerLife = joueur.GetLifeInfo();
	textPlayerLife.setString(playerLife);
}
Text HUD::GetText()
{
	return textPlayerLife;
}