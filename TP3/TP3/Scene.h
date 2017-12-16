#pragma once

#include <SFML/Graphics.hpp>
#include "Vue.h"

using namespace sf;
using namespace MVC;

/// <summary>
/// Classe abstraite avec aucune m�thode concr�tis�e.  Un .h suffit donc.
/// </summary>
namespace sideSpaceShooter
{
	class Scene
	{
	public:
		//Quand vos ajouterez des sc�nes, ajouter un enum ici
		enum scenes {MENU, LOGIN, MEILLEURS_SCORES,GESTION, CREER, MODIFIER, EFFACER, BOUCLEDEJEU, SORTIE};

		virtual ~Scene() {}  //Pour que le destructeur de l'objet en m�moire soit apell�
		virtual scenes run() = 0;
		
		//La boucle de jeu est maintenant g�r�e par la sc�ne
		virtual bool init(RenderWindow * const window) = 0;
		virtual void getInputs() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

	protected:
		RenderWindow *mainWin;
		Event event;
		Vue vue;
		
		/// <summary>
		/// � la fin de chaque sc�ne, on indique � Game quelle nouvelle sc�ne elle doit charger.
		/// </summary>
		Scene::scenes transitionVersScene;
		bool isRunning;
	};
}