#include "Header.h"

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "INFRADVENTURE");

	Music theme;
	if (!theme.openFromFile("Avengers.ogg")) {
		cout << "Could not load music theme..." << endl; //Open le fichier du theme principal
	}
	theme.setVolume(5);

	SoundBuffer buffer;
	if (!buffer.loadFromFile("Punch.ogg")) {
		cout << "Could not load Punch sound..." << endl; //Open le fichier du son d'attaque pour le mettre dans le buffer
	}

	Sound Punch;
	Punch.setBuffer(buffer); //On utillise le son que l'on a mis dans le buffer pour l'attribuer à un élément de type sound pour pouvoir l'utiliser après
	Punch.setVolume(5);

	Weapon* weapon = new Weapon(1, "Epee en carton", 0, .1, "Epée en carton.png");//    }
	Player* player = new Player(100, 100, "Hodaka", weapon);//                          }---- Création des éléments principaux du jeu avec des pointeurs en début du jeu
	Monster* monster = new Monster(100, "Camrond", 'A');//                              }
	
	Sprite bossSprite;
	Sprite weaponSprite;

	window.clear();

	Font font;
	font.loadFromFile("arial.ttf"); //Load de la font afin de pouvoir écrir du texte

	GameEvents game;
	game.Intro(font, window);

	window.display();

	Sleep(2000);

	theme.play(); //Lancement de la musique de fond

	while (window.isOpen()) {

		Event event;

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {

				window.close();

			}

			if (event.type == Event::Resized) {

				resized(window, font);

			}

			window.clear();

			weapon->CreateSprite(window, font, "Epée en carton.png", 1, 1350, 700, 0.75, 0.75, weaponSprite);
			
			HUD HUD;
			HUD.InitHUD(player, monster, weapon, window, font);

			monster->CreateSprite(window, font, "1stBOSS.png", 1, 675, 200, 2, 2, bossSprite); //L'appel de la fonction pour créer le sprite du boss 1

			/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (boss.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) // ici on check la taille de l'image du boss et on vérifie si la souris est dedans
				{                                                                                             // si elle est dedans et que l'on clique sur la souris, alors -|
					if (event.type == Event::MouseButtonPressed) {                                            //                                                             |
						monster1.health -= weaponLvl1.dmgEvryClic;//     <---------------------------------------------------------------------------------------------------|
						player.money++;
					}                                                                                         // mais ça marche pas encore, je pense qu'il faudrait checker si la souris se trouve
				}																							  // dans un rectangle que l'on aurait fait au préalable, comme un cadre autour de l'image
			}*/

			if (event.type == Event::MouseButtonPressed) {
				monster->GettingDamaged(weapon, window, font);
				Punch.play();
			}

			window.display();
			
		}
	}
}
