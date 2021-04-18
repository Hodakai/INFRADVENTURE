#include "Header.h"

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "INFRADVENTURE", Style::Fullscreen);

	window.setVerticalSyncEnabled(true);

	SoundBuffer bufferIntro;
	if (!bufferIntro.loadFromFile("Intro.ogg")) {
		cout << "Could not load Punch sound..." << endl; //Open le fichier du son d'intro pour le mettre dans le buffer
	}

	Sound IntroSound;
	IntroSound.setBuffer(bufferIntro); //On utillise le son que l'on a mis dans le buffer pour l'attribuer à un élément de type sound pour pouvoir l'utiliser après
	IntroSound.setVolume(5);

	IntroSound.play();

	Music theme;
	if (!theme.openFromFile("Avengers.ogg")) {
		cout << "Could not load music theme..." << endl; //Open le fichier du theme principal
	}
	theme.setVolume(5);

	SoundBuffer bufferPunch;
	if (!bufferPunch.loadFromFile("Punch.ogg")) {
		cout << "Could not load Punch sound..." << endl; //Open le fichier du son d'attaque pour le mettre dans le buffer
	}

	Sound Punch;
	Punch.setBuffer(bufferPunch); //On utillise le son que l'on a mis dans le buffer pour l'attribuer à un élément de type sound pour pouvoir l'utiliser après
	Punch.setVolume(5);

	Weapon* weapon = new Weapon(1, "Epee en carton", 0, .1, "Epée en carton.png");//                                                                               }
	Player* player = new Player(100, 1, 1, 100, "Hodaka", weapon);//                                                                                               }---- Création des éléments principaux du jeu 
	Monster* monster = new Monster(100, "Camrond-America", 'A', "Captain America a mal vecu l'arrivee du nouveau captain, il est devenu enrager !!!", 1, .1); //   }---- avec des pointeurs en début du jeu
	
	Sprite bossSprite;
	Sprite weaponSprite;

	window.clear();

	Font font;
	font.loadFromFile("arial.ttf"); //Load de la font afin de pouvoir écrir du texte

	GameEvents* game = new GameEvents;
	game->Intro(font, window);

	Sleep(3500);

	theme.play(); //Lancement de la musique de fond

	while (window.isOpen()) {

		Event event;

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {

				window.close();

			}

			window.clear();

			weapon->CreateSprite(window, font, "Epée en carton.png", 1, 1350, 700, 0.75, 0.75, weaponSprite);

			HUD* GUI = new HUD(player, monster, weapon, font);
			GUI->InitHUD(window);

			Sprite boss = monster->CreateSprite(window, font, "1stBOSS.png", 675, 200, 1, 1, bossSprite); //L'appel de la fonction pour créer le sprite du boss 1 que l'on récupère pour la condition d'après

			if (boss.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && event.type == Event::MouseButtonPressed) // ici on check les bordures de l'image du boss et on vérifie si la souris est dedans
			{                                                                                             // si elle est dedans et que l'on clique sur la souris, alors -|                   
					monster->GettingDamaged(weapon, game, window, font); // <--------------------------------------------------------------------------------------------|
					player->money++; //Augmentation de l'argent du joueur pour acheter des items dans la boutique                                                                    
					player->GettingDamaged(monster, game, window, font); //Ici cette fonction représente l'attaque que le monstre peut réaliser envers le joueur, le joueur peut ne pas prendre de dégats lors de son attaque		    					 
					Punch.play(); //Son joué lors d'une attaque     
			}														
			window.display();
		}
	}
}
