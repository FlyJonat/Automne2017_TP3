#pragma once

#include <SFML/Graphics.hpp>
#include "Vue.h"

using namespace sf;
using namespace MVC;

/// <summary>
/// Classe abstraite avec aucune méthode concrétisée.  Un .h suffit donc.
/// </summary>
namespace sideSpaceShooter
{
	class Scene
	{
	public:
		//Quand vos ajouterez des scènes, ajouter un enum ici
		enum scenes {MENU, LOGIN, MEILLEURS_SCORES,GESTION, CREER, MODIFIER, EFFACER, BOUCLEDEJEU, SORTIE};

		virtual ~Scene() {}  //Pour que le destructeur de l'objet en mémoire soit apellé
		virtual scenes run() = 0;
		
		//La boucle de jeu est maintenant gérée par la scène
		virtual bool init(RenderWindow * const window) = 0;
		virtual void getInputs() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

	protected:
		RenderWindow *mainWin;
		Event event;
		Vue vue;
		
		/// <summary>
		/// À la fin de chaque scène, on indique à Game quelle nouvelle scène elle doit charger.
		/// </summary>
		Scene::scenes transitionVersScene;
		bool isRunning;
	};
}