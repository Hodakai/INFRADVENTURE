#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;
using namespace sf;

////////////////////////////////////////////////       CLASSE DISPLAY       ////////////////////////////////////////////////

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

////////////////////////////////////////////////       CLASSE GAME-EVENTS        ////////////////////////////////////////////////


class GameEvents
{
public:
	void Intro(Font font, RenderWindow& window);
	void Win(Font font, RenderWindow& window);
	void GameOver(Font font, RenderWindow& window);

private:

};

void GameEvents::Intro(Font font, RenderWindow& window) {

	Display Welcome;
	string PWelcome = "Welcome to...";
	Welcome.Print(font, 75, window, PWelcome, 700, 450, Color::White);

	window.display();

	Sleep(2000);

	window.clear();

	Sprite Infradventure;

	Texture texture;

	if (!texture.loadFromFile("Infradventure.png")) { // L'img ici c'est la string du nom de l'image qui doit �tre dans ton dossier comme la font ;) 

		cout << "Texture : Infradventure.png -> loading failed..." << endl; // Message d'erreur dans les logs si une texture ne load pas ^^
		system("pause");

	}

	Infradventure.setTexture(texture);
	window.draw(Infradventure);
	window.display();

}

void GameEvents::Win(Font font, RenderWindow& window) {

	window.clear();

	Display Win;
	string PWin = "Vous avez gagn� face au premier boss !!! Bravo !!!";
	Win.Print(font, 20, window, PWin, 800, 500, Color::White);

	window.display();

	Sleep(2000);

	window.clear();

	Display End;
	string PEnd = "Merci d'avoir jou� !!!";
	End.Print(font, 20, window, PEnd, 800, 500, Color::White);

	window.display();

	Sleep(5000);

	window.close();
}

void GameEvents::GameOver(Font font, RenderWindow& window) {

	window.clear();

	Display Loose;
	string PLoose = "Vous avez perdu !!!";
	Loose.Print(font, 50, window, PLoose, 800, 500, Color::White);

	window.display();

	Sleep(2000);

	window.clear();

	Display End;
	string PEnd = "Merci d'avoir jou� !!!";
	End.Print(font, 20, window, PEnd, 800, 500, Color::White);

	window.display();

	Sleep(5000);

	window.close();
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

////////////////////////////////////////////////       CLASSE WEAPON       ////////////////////////////////////////////////

class Weapon
{
public:
	int dmgEvryClic; // Le nombre de d�gats inflig�s par clic
	int cost; // Le prix de l'arme en question
	string img;
	string name;
	float crit; // Variable qui va d�finir le pourcentage de coup critique infig�s � l'ennemi (entre 0 et 1)

	Weapon(int dmg, string name, int cost, float crit, string img);
	void CreateSprite(RenderWindow& window, Font font, string img, int nbBoss, float x, float y, float Sx, float Sy, Sprite boss);
	string GetWeaponName();
	string GetWeaponImg();
	float GetWeaponCrit();

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

string Weapon::GetWeaponName() {
	return name;
}

string Weapon::GetWeaponImg() {
	return img;
}

float Weapon::GetWeaponCrit() {
	return crit;
}

void Weapon::CreateSprite(RenderWindow& window, Font font, string img, int nbWeapon, float x, float y, float Sx, float Sy, Sprite weaponSprite) {
	sf::Texture textureWeapon;

	if (!textureWeapon.loadFromFile(img)) { // L'img ici c'est la string du nom de l'image qui doit �tre dans ton dossier comme la font ;) 

		cout << "Texture : " << img << "loading failed..." << endl; // Message d'erreur dans les logs si une texture ne load pas ^^
		system("pause");

	}

	weaponSprite.setTexture(textureWeapon);
	weaponSprite.setPosition(x, y);
	weaponSprite.scale(Sx, Sy);

	window.draw(weaponSprite);
}

////////////////////////////////////////////////       CLASSE MONSTER       ////////////////////////////////////////////////

class Monster
{
public:

	int health;
	int healthMax; //Nombre de pv du monstre � la base sans qu'il ait subi d'attaque
	string name;
	char abilities;
	string image;
	string desc;

	//////////////////     Stats reli�es � l'IA du monstre     //////////////////

	int atk; //Nombre de d�gats que peut infliger l'ennemi au joueur
	float atkChance; //Pourcntage d'attaque du monstre

	Monster(int health, string name, char abilites, string desc, int atk, float atkChance);
	~Monster();
	Sprite CreateSprite(RenderWindow& window, Font font, string img, float x, float y, float Sx, float Sy, Sprite boss); // Comme la fonction print mais avec les sprites
	void GettingDamaged(Weapon* weapon, GameEvents* Game, RenderWindow& window, Font font);
	int GetAtk();
	float GetAtkChance();

private:

};

Monster::Monster(int health, string name, char abilities, string desc, int atk, float atkChance) {
	this->health = health;
	this->name = name;
	this->abilities = abilities;
	this->desc = desc;
	this->atk = atk;
	this->atkChance = atkChance;
	this->healthMax = health;
}

Monster::~Monster()
{

}

int Monster::GetAtk() {
	return this->atk;
}

float Monster::GetAtkChance() {
	return this->atkChance;
}

void Monster::GettingDamaged(Weapon* weapon, GameEvents* Game, RenderWindow& window, Font font) {
	int probaCrit = rand() % 100; // cr�ation de la probabilit� d'infliger un coup critique
	if (this->health == 0) {
		Game->Win(font, window);
	}
	else if (weapon->GetWeaponCrit() * 100 > probaCrit) {
		this->health -= weapon->dmgEvryClic * 2; // si le pourcentage est en dessous de celui de l'arme alors les d�gats inflig�s sont multipli�s par 2
		Display Critical;
		string Crit;
		Crit = "Critique ! " + to_string(weapon->dmgEvryClic * 2);
		int probaAffichageX = rand() % 1000 + 500;
		int probaAffichageY = rand() % 500 + 200;
		Critical.Print(font, 100, window, Crit, probaAffichageX, probaAffichageY, Color::Red);
	}
	else {
		this->health -= weapon->dmgEvryClic;
		Display Critical;
		string Crit;
		Crit = to_string(weapon->dmgEvryClic);
		int probaAffichageX = rand() % 1000 + 500;
		int probaAffichageY = rand() % 500 + 200;
		Critical.Print(font, 75, window, Crit, probaAffichageX, probaAffichageY, Color::Red);
	}
}


Sprite Monster::CreateSprite(RenderWindow& window, Font font, string img, float x, float y, float Sx, float Sy, Sprite boss) {
	sf::Texture texture;

	if (!texture.loadFromFile(img)) { // L'img ici c'est la string du nom de l'image qui doit �tre dans ton dossier comme la font ;) 

		cout << "Texture : " << img << "loading failed..." << endl; // Message d'erreur dans les logs si une texture ne load pas ^^
		system("pause");

	}

	boss.setTexture(texture);
	boss.setPosition(x, y);
	boss.scale(Sx, Sy);

	window.draw(boss);
	return boss;
}

////////////////////////////////////////////////       CLASSE PLAYER       ////////////////////////////////////////////////

class Player
{
public:
	int money;
	int health;
	int moneyPerSec; //Argent par seconde du joueur
	int multiplicateur; //Tout est dans le nom
	string name;
	Weapon* weapon;

	Player(int money, int moneyPS, int multiplicateur, int health, string name, Weapon* weapon);
	void GettingDamaged(Monster* monster, GameEvents* Game, RenderWindow& window, Font font);

private:


};

//Constructeur
Player::Player(int money, int moneyPS, int multiplicateur, int health, string name, Weapon* weapon) {
	this->money = money;
	this->moneyPerSec = moneyPS;
	this->multiplicateur = multiplicateur;
	this->health = health;
	this->name = name;
	this->weapon = weapon;
}

void Player::GettingDamaged(Monster* monster, GameEvents* Game, RenderWindow& window, Font font) {
	int probaDmg = rand() % 100; // cr�ation de la probabilit� de recevoir un coup de la part du monstre
	int probaAffichageX = rand() % 1000 + 500;
	int probaAffichageY = rand() % 500 + 200;
	if (this->health == 0) {
		Game->GameOver(font, window);
	}
	else if (monster->GetAtkChance() * 100 > probaDmg) {
		this->health -= monster->GetAtk(); // si le pourcentage est en dessous de celui de l'arme alors les d�gats inflig�s sont multipli�s par 2
		/*Display Critical;
		string Crit;
		Crit = "Critique ! " + to_string(weapon->dmgEvryClic * 2);
		int probaAffichageX = rand() % 1000 + 500;
		int probaAffichageY = rand() % 500 + 200;
		Critical.Print(font, 100, window, Crit, probaAffichageX, probaAffichageY, Color::Red);*/
	}
	else if (monster->GetAtkChance() * 100 + 25 > probaDmg && monster->health < .1 * monster->healthMax) {
		this->health -= monster->GetAtk() * 2.5;
		Display EnragedAktMonster;
		string EAMonster;
		EAMonster = "BOOOOM !!!";
		EnragedAktMonster.Print(font, 100, window, EAMonster, probaAffichageX, probaAffichageY, Color::Magenta);
	}
	else if (monster->GetAtkChance() * 100 + 10 > probaDmg && monster->health < .25 * monster->healthMax) {
		this->health -= monster->GetAtk() * 2;
		Display EnragedAktMonster;
		string EAMonster;
		EAMonster = "RAHHHH !!!";
		EnragedAktMonster.Print(font, 100, window, EAMonster, probaAffichageX, probaAffichageY, Color::Green);
	}
	else if (monster->GetAtkChance() * 100 + 5 > probaDmg && monster->health < .5 * monster->healthMax) {
		this->health -= monster->GetAtk() * 1.5;
		Display SuperAktMonster;
		string SAMonster;
		SAMonster = "Grrrrr !!!";
		SuperAktMonster.Print(font, 100, window, SAMonster, probaAffichageX, probaAffichageY, Color::Cyan);
	}
}

////////////////////////////////////////////////       CLASSE HUD        ////////////////////////////////////////////////

/// <summary>
/// Sert � afficher toutes les informations � l'�cran pour le joueur, c'est le HUD (Head Up Display)
/// </summary>

class HUD : public Display // Classe d�riv�e de Display qui permet d'afficher le HUD 
{
public:

	void InitHUD(Player* player, Monster* monster, Weapon* weapon, RenderWindow& window, Font font) {
		PlayerHealth(player, window, font);
		PlayerGold(player, window, font);
		MonsterHealth(monster, window, font);
		MonsterName(monster, window, font);
		WeaponName(weapon, window, font);
	}

	void PlayerHealth(Player* player, RenderWindow& window, Font font) {
		Display HealthPlayer;

		string PvPlayer;
		PvPlayer = "Vie : " + to_string(player->health);
		HealthPlayer.Print(font, 30, window, PvPlayer, 20, 0, Color::Green);
	}

	void PlayerGold(Player* player, RenderWindow& window, Font font) {
		Display GoldPlayer;

		string GPlayer;
		GPlayer = "Argent : " + to_string(player->money);
		GoldPlayer.Print(font, 30, window, GPlayer, 20, 40, Color::Yellow);
	}

	void MonsterHealth(Monster* monster, RenderWindow& window, Font font) {
		Display HealthMonster;

		string PvMonster;
		PvMonster = to_string(monster->health);
		HealthMonster.Print(font, 75, window, PvMonster, 910, 100, Color::Red);
	}

	void MonsterName(Monster* monster, RenderWindow& window, Font font) {
		Display NameMonster;

		string NMonster;
		NMonster = monster->name;
		NameMonster.Print(font, 75, window, NMonster, 650, 800, Color::Red);
	}

	void MonsterDescription(Monster* monster, RenderWindow& window, Font font) {
		Display DescMonster;

		string DescripMonster;
		DescripMonster = monster->desc;
		DescMonster.Print(font, 75, window, DescripMonster, 0, 0, Color::White);
	}

	void WeaponName(Weapon* weapon, RenderWindow& window, Font font) {
		Display NameMonster;

		string NWeapon;
		NWeapon = weapon->name;
		NameMonster.Print(font, 25, window, NWeapon, 1640, 990, Color::White);
	}

private:

};