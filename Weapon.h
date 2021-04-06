#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <algorithm>
#include <string>
#include "Fonctions.h"
#include "Player.h"
#include "Monster.h"

using namespace std;
using namespace sf;


class Weapon
{
public:
	int dmgEvryClic; // Le nombre de dégats infligés par clic
	string name;
	int cost; // Le prix de l'arme en question
	float crit; // Variable qui va définir le pourcentage de coup critique infigés à l'ennemi (entre 0 et 1)
	string img;

	Weapon(int dmg, string name, int cost, float crit, string img);
	void CreateSprite(RenderWindow& window, Font font, string img, int nbBoss, float x, float y, float Sx, float Sy, Sprite boss);
	void Atk(Monster* monster, RenderWindow& window, Font font);
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

void Weapon::Atk(Monster* monster, RenderWindow& window, Font font) {
	int probaCrit = rand() % 100; // création de la probabilité d'infliger un coup critique
	if (this->crit * 100 > probaCrit) {
		monster->health -= this->dmgEvryClic * 2; // si le pourcentage est en dessous de celui de l'arme alors les dégats infligés sont multipliés par 2
		Display Critical;
		string Crit;
		Crit = "Crit ! " + to_string(this->dmgEvryClic * 2);
		float probaAffichageX = rand() % 1000 + 500;
		float probaAffichageY = rand() % 500 + 200;
		Critical.Print(font, 45, window, Crit, probaAffichageX, probaAffichageY, Color::Red);
	}
	else {
		monster->health -= this->dmgEvryClic;
		Display Critical;
		string Crit;
		Crit = to_string(this->dmgEvryClic);
		float probaAffichageX = rand() % 1000 + 500;
		float probaAffichageY = rand() % 500 + 200;
		Critical.Print(font, 30, window, Crit, probaAffichageX, probaAffichageY, Color::Red);
	}
}

Weapon::~Weapon()
{

}