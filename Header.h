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
	void Win(Font font, RenderWindow& window);
	void GameOver(Font font, RenderWindow& window);

private:

};


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

	Sleep(2000);

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


////////////////////////////////////////////////       CLASS SPELL      ////////////////////////////////////////////////

class Spell
{
public:
	Spell(string nameOfSpell, int damage, int levelOfSpell, int FullCritDuration, int maxLvlofSpell, int ultimateDuration, int CooldownSpell, int costOfSpell)
	{
		this->name = nameOfSpell;
		this->dmg = damage;
		this->lvl = levelOfSpell;
		
		this->fullCritTime = FullCritDuration;
		this->maxLvl = maxLvlofSpell;
		this->UltimateTime = ultimateDuration;
		this->cooldown = CooldownSpell;
		this->cost = costOfSpell;
	}

	
	
	void LvlUpSpell(int money);
	int SpellAdmg();
	int getlvl();
	int getCost();
	

	int cost;
	int verifAchat = 0;
	int cooldown;
	string name;
	int fullCritTime;
	int UltimateTime;
	
private:
	
	int dmg;
	int lvl;

	
	int maxLvl;
	
};

int Spell::SpellAdmg() {
	return this->dmg;
}

int Spell::getlvl() {
	return this->lvl;
}

int Spell::getCost() {
	return this->cost;
}

void  Spell::LvlUpSpell(int money) {
	cout << "name : " << this->name << "\nlvl : " << this->lvl << "Cost : " << this->cost << endl;
	if (this->name == "SunFire" && money >= this->cost && this->lvl < this->maxLvl) {
		this->dmg += 50;
		this->lvl++;	
		this->verifAchat = 1;
		cout << " Sunfire lvl up, now lvl : " << this->lvl <<" \nand deal : "<< this->dmg <<" damage" <<endl;
	}
	else if (this->name == "Heal" && money >= this->cost && this->lvl < this->maxLvl) {
		this->cooldown -= 5;
		this->lvl++;
		this->verifAchat = 1;

	}

	else if (this->name == "Fullcrit" && money >= this->cost && this->lvl < this->maxLvl) {
		this->fullCritTime += 5;
		this->lvl++;
		this->verifAchat = 1;
	
	}
	else if (this->name == "Ultimate" && money >= this->cost && this->lvl < this->maxLvl)
	{
		this->lvl++;
		this->UltimateTime += 5;	
		this->verifAchat = 1;
	}
	else {
		cout << "Error evolution, vous ne pouvez plus evoluer ce sort !" << endl;
	}		
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
	int lvl;
	int verifAchat;
	int MaxLvl;
	int idname = 1;

	Weapon(int dmg, string name, int cost, float crit, int Level,int maxLevel) { //Constructeur
		this->dmgEvryClic = dmg;
		this->name = name;
		this->cost = cost;
		this->crit = crit;
		this->lvl = Level;
		this->MaxLvl = maxLevel;
	}

	void lvlUpWeapon(int money);
private:

};

void Weapon::lvlUpWeapon(int money) {
	if (money >= this->cost && this->lvl < this->MaxLvl) {
		this->lvl++;
		this->idname++;
		this->crit += .1;
		this->dmgEvryClic += 4;
		this->verifAchat = 1;
		cout << "name : " << this->name << "\nlvl : " << this->lvl << "\nDamage : " << this->dmgEvryClic << "Crit arme :" << this->crit <<endl;
	}
	else {
		cout << "Error evolution :\n\n" << endl;
		this->verifAchat = 2;
	}
	if (idname == 2) {
		this->name = "Epee en Pierre";
	}
	else if (idname == 3) {
		this->name = "Epee en Fer";
	}
	else if (idname == 4) {
		this->name = "Epee en Or";
	}
	else if (idname == 5) {
		this->name = "Epee en Diamant";
	}
	
}





////////////////////////////////////////////////       CLASSE MONSTER       ////////////////////////////////////////////////

class Monster
{
public:

	int health;
	int healthMax; //Nombre de pv du monstre à la base sans qu'il ait subi d'attaque
	string name;
	string image;
	string desc;
	float ResizeBarNb;

	//////////////////     Stats reliées à l'IA du monstre     //////////////////

	int atk; //Nombre de dégats que peut infliger l'ennemi au joueur
	float atkChance; //Pourcntage d'attaque du monstre

	Monster(int health, float NbResizeHpbarMonster, string name, string desc, int atk, float atkChance);
	Sprite CreateSprite(RenderWindow& window, Font font, string img, float x, float y, float Sx, float Sy, Sprite boss); // Comme la fonction print mais avec les sprites
	void GettingDamaged(Weapon* weapon, GameEvents* Game, RenderWindow& window, Font font);
	void GettingDamagedFromSpellA(Spell* spell, GameEvents* Game, RenderWindow& window, Font font);
	int GetAtk();
	float GetAtkChance();

private:

};

Monster::Monster(int health,float NbResizeHpbarMonster ,string name, string desc, int atk, float atkChance) {
	this->health = health;
	this->name = name;
	this->desc = desc;
	this->atk = atk;
	this->atkChance = atkChance;
	this->healthMax = health;
	this->ResizeBarNb = NbResizeHpbarMonster;
}

int Monster::GetAtk() {
	return this->atk;
}

float Monster::GetAtkChance() {
	return this->atkChance;
}

void Monster::GettingDamaged(Weapon* weapon, GameEvents* Game, RenderWindow& window, Font font) {
	int probaCrit = rand() % 100; // création de la probabilité d'infliger un coup critique
	if (this->health < 1) {
		Game->Win(font, window);

	}
	else if (weapon->crit * 100 > probaCrit) {
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

void Monster::GettingDamagedFromSpellA(Spell* spell, GameEvents* Game, RenderWindow& window, Font font) {
	this->health -= spell->SpellAdmg();

	if (this->health < 1) {
		Game->Win(font, window);
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
	int moneyPerSec; //Argent par click du joueur
	int multiplicateur; //Tout est dans le nom
	string name;
	Weapon* weapon;


	Player(int money, int moneyPS, int multiplicateur, int health, string name, Weapon* weapon);
	void GettingDamaged(Monster* monster, GameEvents* Game, RenderWindow& window, Font font);
	void heal();

private:


};

void Player::heal() {
	this->health += 10;
	if (this->health > 100)
	{
		this->health = 100;
	}
}

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
	if (this->health < 1) {
		Game->GameOver(font, window);
	}
	else if (monster->GetAtkChance() * 100 > probaDmg) {
		this->health -= monster->GetAtk(); // si le pourcentage est en dessous de celui de l'arme alors les dégats infligés sont multipliés par 2		
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
	void PlayerGold(RenderWindow& window);

	void MonsterDescription(RenderWindow& window);

	void MonsterName(RenderWindow& window) {
		Display NameMonster;

		string NMonster;
		NMonster = this->monster->name;
		NameMonster.Print(this->font, 75, window, NMonster, 650, 800, Color::Red);
	}


private:
	Player* player;
	Monster* monster;
	Weapon* weapon;
	Font font;

	RectangleShape hpBarBehindPlayer;
	RectangleShape hpBarInsidePlayer;

	RectangleShape hpBarBehindMonster;
	RectangleShape hpBarInsideMonster;


};





HUD::HUD(Player* player, Monster* monster, Weapon* weapon, Font font)
{
	this->player = player;
	this->monster = monster;
	this->weapon = weapon;
	this->font = font;
}

void HUD::renderHpBarPlayer(RenderWindow& window)
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
	window.draw(this->hpBarBehindPlayer);
	window.draw(this->hpBarInsidePlayer);
}

void HUD::renderHpBarMonster(RenderWindow& window)
{
	float height = 20.f;
	float width = 500.f;
	float x = 705.f;
	float y = 170.f;

	this->hpBarBehindMonster.setSize(Vector2f(width, height));
	this->hpBarBehindMonster.setFillColor(Color::White);
	this->hpBarBehindMonster.setPosition(x, y);

	this->hpBarInsideMonster.setSize(Vector2f(this->monster->health * this->monster->ResizeBarNb, height)); //On récupère la valeur des PV du monstre et on la multiplie par 3 pour avoir la largeur de la barre de PV
	this->hpBarInsideMonster.setFillColor(Color::Red);
	this->hpBarInsideMonster.setPosition(this->hpBarBehindMonster.getPosition());
	window.draw(this->hpBarBehindMonster);
	window.draw(this->hpBarInsideMonster);
}

void HUD::InitHUD(RenderWindow& window) {
	//InitHpBarPlayer();
	renderHpBarPlayer(window);
	//InitHpBarMonster();
	renderHpBarMonster(window);
	PlayerGold(window);
	
}


void HUD::PlayerGold(RenderWindow& window) {
	Display GoldPlayer;

	string GPlayer;
	GPlayer = "Argent : " + to_string(this->player->money);
	GoldPlayer.Print(this->font, 30, window, GPlayer, 20, 40, Color::Yellow);
}


void HUD::MonsterDescription(RenderWindow& window) {
	Display DescMonster;

	string DescripMonster;
	DescripMonster = this->monster->desc;
	DescMonster.Print(this->font, 20, window, DescripMonster, 1400, 400, Color::White);
}