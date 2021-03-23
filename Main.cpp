#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;
using namespace sf;

class Display
{
public:

	void Print(Font font, int size, RenderWindow& window, string str, float x, float y, Color color) {

		Text text;

		text.setFont(font);
		text.setCharacterSize(size);
		text.setStyle(Text::Regular);
		text.setFillColor(color);
		text.setString(str);
		text.setPosition(x, y);

		window.draw(text);
	}

	typedef struct DataPrint DataPrint;

private:
	string str;
};

class GameEvents : public Display
{
public:

	void Intro(Font font, RenderWindow& window) {

		Display Welcome;
		string PWelcome = "Welcome to...";
		Welcome.Print(font, 20, window, PWelcome, 800, 500, Color::White);

		window.display();

		Sleep(2000);

		window.clear();

		Display Title;
		string PTitle = "INFRADVENTURE";
		Title.Print(font, 30, window, PTitle, 800, 500, Color::White);

	}

	void Win(Font font, RenderWindow& window) {
		
		window.clear();

		Display Win;
		string PWin = "Vous avez gagné face au premier boss !!! Bravo !!!";
		Win.Print(font, 20, window, PWin, 800, 500, Color::White);

		window.display();

		Sleep(2000);

		window.clear();

		Display End;
		string PEnd = "Merci d'avoir joué !!!";
		End.Print(font, 20, window, PEnd, 800, 500, Color::White);

		window.display();

		Sleep(5000);

		window.close();
	}

private:

};

class Player : public GameEvents
{
public:
	int money;
	int health;
	string name;

	Player(int money, int health, string name);

private:
	

};

//Constructeur
Player::Player(int money, int health, string name) {
	this->money = money;
	this->health = health;
	this->name = name;
}

class Weapon
{
public:
	int dmgEvryClic; // Le nombre de dégats infligés par clic
	string name;
	int cost; // Le prix de l'arme en question
	float crit; // Variable qui va définir le pourcentage de coup critique infigés à l'ennemi (entre 0 et 1)
	string img;

	Weapon(int dmg, string name, int cost, float crit, string img);
	void CreateSprite(RenderWindow& window, Font font, string img, int nbBoss, Player player, float x, float y, float Sx, float Sy, Sprite boss);
	~Weapon();

private:
	

};

//Constructeur
Weapon::Weapon(int dmg, string name, int cost, float crit, string img) {
	this->dmgEvryClic = dmg;
	this->name = name;
	this->cost = cost;
	this->crit = crit;
	this->img = img;
}

void Weapon::CreateSprite(RenderWindow& window, Font font, string img, int nbWeapon, Player player, float x, float y, float Sx, float Sy, Sprite weaponSprite) {
	sf::Texture textureWeapon;

	if (!textureWeapon.loadFromFile(img)) { // L'img ici c'est la string du nom de l'image qui doit être dans ton dossier comme la font ;) 

		cout << "Texture : " << img << "loading failed..." << endl; // Message d'erreur dans les logs si une texture ne load pas ^^
		system("pause");

	}

	weaponSprite.setTexture(textureWeapon);
	weaponSprite.setPosition(x, y);
	weaponSprite.scale(Sx, Sy);

	window.draw(weaponSprite);
}

Weapon::~Weapon()
{
	
}

class Monster
{
public:

	int health;
	string name;
	char abilities;
	string image;

	Monster(int health, string name, char abilites);
	~Monster();
	void CreateSprite(RenderWindow& window, Font font, string img, int nbBoss, Player player, float x, float y, float Sx, float Sy, Sprite boss); // Comme la fonction print mais avec les sprites

private:

};

Monster::Monster(int health, string name, char abilities) {
	this->health = health;
	this->name = name;
	this->abilities = abilities;
}

Monster::~Monster()
{

}

// La fameuse fonction avec 100000000 d'arguments xD
void Monster::CreateSprite(RenderWindow& window, Font font, string img, int nbBoss, Player player, float x, float y, float Sx, float Sy, Sprite boss) {
	sf::Texture texture;

	if (!texture.loadFromFile(img)) { // L'img ici c'est la string du nom de l'image qui doit être dans ton dossier comme la font ;) 

		cout << "Texture : " << img << "loading failed..." << endl; // Message d'erreur dans les logs si une texture ne load pas ^^
		system("pause");

	}

	boss.setTexture(texture);
	boss.setPosition(x, y);
	boss.scale(Sx, Sy);

	window.draw(boss);
}

// J'ai fait une fonction pour le message de resize de la window ;) 
void resized(RenderWindow& window, Font font) {

	window.clear();
	Display warningResize;
	string WarnRstr = "Attention ! Vous avez redimentionne la fenetre, cela peut affecter l'affichage de certains elements !";
	warningResize.Print(font, 20, window, WarnRstr, 500, 500, Color::White);
	window.display();
	Sleep(3000);

}

	/// <summary>
	/// Sert à afficher toutes les informations à l'écran pour le joueur, c'est le HUD (Head Up Display)
	/// </summary>

class HUD : public Display // Classe dérivée de Display qui permet d'afficher le HUD 
{
public:

	void InitHUD(Player player, Monster monster, Weapon weapon, RenderWindow& window, Font font) {
		PlayerHealth(player, window, font);
		PlayerGold(player, window, font);
		MonsterHealth(monster, window, font);
		MonsterName(monster, window, font);
		WeaponName(weapon, window, font);
	}

	void PlayerHealth(Player player, RenderWindow& window, Font font) {
		Display HealthPlayer;

		string PvPlayer;
		PvPlayer = "Vie : " + to_string(player.health);
		HealthPlayer.Print(font, 30, window, PvPlayer, 20, 0, Color::Green);
	}

	void PlayerGold(Player player, RenderWindow& window, Font font) {
		Display GoldPlayer;

		string GPlayer;
		GPlayer = "Argent : " + to_string(player.health);
		GoldPlayer.Print(font, 30, window, GPlayer, 20, 40, Color::Yellow);
	}

	void MonsterHealth(Monster monster, RenderWindow& window, Font font) {
		Display HealthMonster;

		string PvMonster;
		PvMonster = to_string(monster.health);
		HealthMonster.Print(font, 75, window, PvMonster, 910, 100, Color::Red);
	}

	void MonsterName(Monster monster, RenderWindow& window, Font font) {
		Display NameMonster;

		string NMonster;
		NMonster = monster.name;
		NameMonster.Print(font, 75, window, NMonster, 800, 800, Color::Red);
	}

	void WeaponName(Weapon weapon, RenderWindow& window, Font font) {
		Display NameMonster;

		string NWeapon;
		NWeapon = weapon.name;
		NameMonster.Print(font, 25, window, NWeapon, 1640, 990, Color::White);
	}

private:

};

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "INFRADVENTURE");
		
	Player player(100, 100, "Hodaka");
	Weapon weapon(1, "Epee en carton", 0, 0, "Epée en carton.png");
	Monster monster(100, "Camrond", 'A');
	 
	Sprite bossSprite;
	Sprite weaponSprite;

	window.clear();

	Font font;
	font.loadFromFile("arial.ttf");

	player.Intro(font, window);

	window.display();

	Sleep(2000);

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

			weapon.CreateSprite(window, font, "Epée en carton.png", 1, player, 1350, 700, 0.75, 0.75, weaponSprite);
			
			HUD HUD;
			HUD.InitHUD(player, monster, weapon, window, font);

			monster.CreateSprite(window, font, "1stBOSS.png", 1, player, 675, 200, 2, 2, bossSprite); //L'appel de la fonction pour créer le sprite du boss 1

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
				monster.health -= weapon.dmgEvryClic;
				player.money++;
			}

			if (monster.health == 0) {
				player.Win(font, window);
			}

			window.display();
			
		}
	}
}
