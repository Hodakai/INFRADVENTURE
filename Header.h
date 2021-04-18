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

	if (!texture.loadFromFile("Infradventure.png")) { // L'img ici c'est la string du nom de l'image qui doit être dans ton dossier comme la font ;) 

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

void GameEvents::GameOver(Font font, RenderWindow& window) {

	window.clear();

	Display Loose;
	string PLoose = "Vous avez perdu !!!";
	Loose.Print(font, 50, window, PLoose, 800, 500, Color::White);

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
	int dmgEvryClic; // Le nombre de dégats infligés par clic
	int cost; // Le prix de l'arme en question
	string img;
	string name;
	float crit; // Variable qui va définir le pourcentage de coup critique infigés à l'ennemi (entre 0 et 1)

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

	if (!textureWeapon.loadFromFile(img)) { // L'img ici c'est la string du nom de l'image qui doit être dans ton dossier comme la font ;) 

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
	int healthMax; //Nombre de pv du monstre à la base sans qu'il ait subi d'attaque
	string name;
	char abilities;
	string image;
	string desc;

	//////////////////     Stats reliées à l'IA du monstre     //////////////////

	int atk; //Nombre de dégats que peut infliger l'ennemi au joueur
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
	int probaCrit = rand() % 100; // création de la probabilité d'infliger un coup critique
	if (this->health == 0) {
		Game->Win(font, window);
	}
	else if (weapon->GetWeaponCrit() * 100 > probaCrit) {
		this->health -= weapon->dmgEvryClic * 2; // si le pourcentage est en dessous de celui de l'arme alors les dégats infligés sont multipliés par 2
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

	if (!texture.loadFromFile(img)) { // L'img ici c'est la string du nom de l'image qui doit être dans ton dossier comme la font ;) 

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
	int probaDmg = rand() % 100; // création de la probabilité de recevoir un coup de la part du monstre
	int probaAffichageX = rand() % 1000 + 500;
	int probaAffichageY = rand() % 500 + 200;
	if (this->health == 0) {
		Game->GameOver(font, window);
	}
	else if (monster->GetAtkChance() * 100 > probaDmg) {
		this->health -= monster->GetAtk(); // si le pourcentage est en dessous de celui de l'arme alors les dégats infligés sont multipliés par 2
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
/// Sert à afficher toutes les informations à l'écran pour le joueur, c'est le HUD (Head Up Display)
/// </summary>

class HUD : public Display // Classe dérivée de Display qui permet d'afficher le HUD 
{
public:
	HUD(Player* player, Monster* monster, Weapon* weapon, Font font);

	void renderHpBarPlayer(RenderWindow& window);
	void renderHpBarMonster(RenderWindow& window);

	void InitHUD(RenderWindow& window);
	void PlayerHealth(RenderWindow& window);
	void PlayerGold(RenderWindow& window);
	void MonsterHealth(RenderWindow& window);
	void MonsterName(RenderWindow& window);
	void MonsterDescription(RenderWindow& window);
	void WeaponName(RenderWindow& window);
	

private:
	Player* player;
	Monster* monster;
	Weapon* weapon;
	Font font;

	RectangleShape hpBarBehindPlayer;
	RectangleShape hpBarInsidePlayer;

	RectangleShape hpBarBehindMonster;
	RectangleShape hpBarInsideMonster;

	void InitHpBarPlayer();
	void InitHpBarMonster();

};



void HUD::InitHpBarPlayer()
{
	float height = 20.f;
	float width = 300.f;
	float x = 20.f;
	float y = 20.f;

	this->hpBarBehindPlayer.setSize(Vector2f(width, height));
	this->hpBarBehindPlayer.setFillColor(Color::Red);
	this->hpBarBehindPlayer.setPosition(x, y);

	this->hpBarInsidePlayer.setSize(Vector2f(this->player->health * 3, height)); //On récupère la valeur des PV du joueur et on la multiplie par 3 pour avoir la largeur de la barre de PV
	this->hpBarInsidePlayer.setFillColor(Color::Green);
	this->hpBarInsidePlayer.setPosition(this->hpBarBehindPlayer.getPosition());
}

void HUD::InitHpBarMonster()
{
	float height = 20.f;
	float width = 500.f;
	float x = 705.f;
	float y = 170.f;

	this->hpBarBehindMonster.setSize(Vector2f(width, height));
	this->hpBarBehindMonster.setFillColor(Color::Red);
	this->hpBarBehindMonster.setPosition(x, y);

	this->hpBarInsideMonster.setSize(Vector2f(this->monster->health * 5, height)); //On récupère la valeur des PV du monstre et on la multiplie par 3 pour avoir la largeur de la barre de PV
	this->hpBarInsideMonster.setFillColor(Color::Cyan);
	this->hpBarInsideMonster.setPosition(this->hpBarBehindMonster.getPosition());
}

HUD::HUD(Player* player, Monster* monster, Weapon* weapon, Font font)
{
	this->player = player;
	this->monster = monster;
	this->weapon = weapon;
	this->font = font;
}

void HUD::renderHpBarPlayer(RenderWindow& window)
{
	window.draw(this->hpBarBehindPlayer);
	window.draw(this->hpBarInsidePlayer);
}

void HUD::renderHpBarMonster(RenderWindow& window)
{
	window.draw(this->hpBarBehindMonster);
	window.draw(this->hpBarInsideMonster);
}

void HUD::InitHUD(RenderWindow& window) {
	InitHpBarPlayer();
	renderHpBarPlayer(window);
	InitHpBarMonster();
	renderHpBarMonster(window);
	//PlayerHealth(player, window, font);
	PlayerGold(window);
	//MonsterHealth(window);
	MonsterName(window);
	WeaponName(window);
}

void HUD::PlayerHealth(RenderWindow& window) {
	Display HealthPlayer;

	string PvPlayer;
	PvPlayer = "Vie : " + to_string(this->player->health);
	HealthPlayer.Print(this->font, 30, window, PvPlayer, 20, 0, Color::Green);
}

void HUD::PlayerGold(RenderWindow& window) {
	Display GoldPlayer;

	string GPlayer;
	GPlayer = "Argent : " + to_string(this->player->money);
	GoldPlayer.Print(this->font, 30, window, GPlayer, 20, 40, Color::Yellow);
}

void HUD::MonsterHealth(RenderWindow& window) {
	Display HealthMonster;

	string PvMonster;
	PvMonster = to_string(this->monster->health);
	HealthMonster.Print(this->font, 75, window, PvMonster, 910, 100, Color::Red);
}

void HUD::MonsterName(RenderWindow& window) {
	Display NameMonster;

	string NMonster;
	NMonster = this->monster->name;
	NameMonster.Print(this->font, 75, window, NMonster, 650, 800, Color::Red);
}

void HUD::MonsterDescription(RenderWindow& window) {
	Display DescMonster;

	string DescripMonster;
	DescripMonster = this->monster->desc;
	DescMonster.Print(this->font, 75, window, DescripMonster, 0, 0, Color::White);
}

void HUD::WeaponName(RenderWindow& window) {
	Display NameMonster;

	string NWeapon;
	NWeapon = this->weapon->name;
	NameMonster.Print(this->font, 25, window, NWeapon, 1640, 990, Color::White);
}