#include "Header.h"

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "INFRADVENTURE");

	Image Icon;
	if (!Icon.loadFromFile("Icon.png")) {
		cout << "Could not load Icon..." << endl;
	}

	window.setIcon(100, 100, Icon.getPixelsPtr());

	window.setVerticalSyncEnabled(true);

	Font font;
	font.loadFromFile("arial.ttf"); //Load de la font afin de pouvoir �crir du texte

	Music theme;
	if (!theme.openFromFile("Avengers.ogg")) {
		cout << "Could not load music theme..." << endl; //Open le fichier du theme principal
	}
	theme.setVolume(5);

	SoundBuffer bufferPunch;
	if (!bufferPunch.loadFromFile("Hitmarker.ogg")) {
		cout << "Could not load Punch sound..." << endl; //Open le fichier du son d'attaque pour le mettre dans le buffer
	}

	Sound Hit;
	Hit.setBuffer(bufferPunch); //On utillise le son que l'on a mis dans le buffer pour l'attribuer � un �l�ment de type sound pour pouvoir l'utiliser apr�s
	Hit.setVolume(15);

	Weapon* weapon = new Weapon(1, "Epee en carton", 0, .1, "Ep�e en carton.png");//                                       }
	Player* player = new Player(100, 1, 1, 100, "Hodaka", weapon);//                                                       }---- Cr�ation des �l�ments principaux du jeu 
	Monster* monster = new Monster(100, "Meca-Bot", "Meca-Bot est l'un des sbires\ndu tristement c�l�bre Meca-\nDoom il faut le mettre hors\nservice afin de pouvoir\nesperer acceder �\nMeca-Doom", 1, .1); // }
	HUD* GUI = new HUD(player, monster, weapon, font);
	GameEvents* game = new GameEvents;
	
	Sprite bossSprite;
	Sprite caveSprite;

	//theme.play(); //Lancement de la musique de fond

	string monsterImg = "1stBOSS.png"; // D�finition de l'image du premier monstre dans un �l�ment string pour pouvoir le changer facilement par la suite

	int nameX = 800.f;
	int nbMonsterDeafeated = 0; // Ici on initialise une variable qui va nous servir � savoir le nombre de boss batus au cours de la partie
	int bossX, bossY, bossSX, bossSY; // Variables pour la position de l'image du premier monstre pour pouvoir y acceder facilement
	bossX = 650;
	bossY = 200;
	bossSX = 3;
	bossSY = 3;

	game->Intro(font, window);

	while (window.isOpen()) { // Tous les �l�ments pr�sents dans cette boucle vont s'afficher en temps r�el dans la fen�tre SFML

		Event event;

		while (window.pollEvent(event)) { // Tous les �l�ments pr�sents dans cette boucle vont s'afficher en boucle d�s que l'un �v�nement se produit (c'est ici que l'on va avoir tous les �v�nements)

			if (event.type == Event::Closed) {

				window.close();

			}

			window.clear();
			GUI->InitHUD(window, nameX); // Lancement de la fonction qui va se charger d'afficher tout le menu dans le jeu

			Sprite MonsterBoss = monster->CreateSprite(window, font, monsterImg, bossX, bossY, bossSX, bossSY, bossSprite); // Cr�ation et affichage du sprite du monstre
			//          ^--------------- On retourne le sprite cr�� et affich� pour pouvoir l'utiliser dans la condition en dessous -----v
			if (MonsterBoss.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && event.type == Event::MouseButtonPressed) // ici on check les bordures de l'image du boss et on v�rifie si la souris est dedans
			{                                                                                             // si elle est dedans et que l'on clique sur la souris, alors -|                   
				Hit.play(); //Son jou� lors d'une attaque <--------------------------------------------------------------------------------------------------------------|
				player->GettingDamaged(monster, game, window, font); //Ici cette fonction repr�sente l'attaque que le monstre peut r�aliser envers le joueur, le joueur peut ne pas prendre de d�gats lors de son attaque		    					 
				player->money++; //Augmentation de l'argent du joueur pour acheter des items dans la boutique    
				monster->GettingDamaged(weapon, game, window, font);

				CreateHitSprite(window, font); // Fonction pour cr�er un sprite pour chaque clic de souris du joueur afin qu'il soit sur la souris a chaque fois

				if (monster->health < 1) // Condition pour 
				{
					nbMonsterDeafeated++;
					if (nbMonsterDeafeated == 1) {
						window.clear();
						game->WinFirstBoss(font, window);
						monster->SetMonster(100, "Infra-Knight", "Infra-Knight, le fr�re\nmal�fique de Meca-Doom\nveut prot�ger son\nfr�re machiav�lique !!!\n\nPoint faible :\nIl reste humain �\nl'interieur...", 5, .3);
						monsterImg = "2ndBOSS.png";
						nameX = 750.f;
						bossX = 625;
						bossY = 250;
						bossSX = 1;
						bossSY = 1;
					}
					else if (nbMonsterDeafeated == 2) {
						monster->SetMonster(100, "Infra-Doom", "Ce robot venant du futur\nest venu d�truire le monde !!!\nSeul nous peuvent\nauver l'humanit� !!!\n\nPoint faible :\nTROP FORT !!!", 10, .4);
						monsterImg = "3rdBOSS.png";
						bossX = 500;
						bossY = 200;
					}
					else if (nbMonsterDeafeated == 3) {
						monster->SetMonster(100, "Ship of Infra-Doom", "Meca-Doom s'enfuit !!!\nIl est parti a bord de son\nvaisseau armageddon !\nIl faut le mettre hors d'�tat\nde nuire !!!\n\nPoint faible :\nVOUS !!!", 15, .5);
						monsterImg = "4thBOSS.png";
						nameX = 650.f;
						bossX = 450;
						bossY = 340;
						bossSX = 2;
						bossSY = 2;
					}
				}
			}
			window.display();
		}
	}
}
