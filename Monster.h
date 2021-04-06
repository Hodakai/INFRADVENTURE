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
#include "Weapon.h"

using namespace std;
using namespace sf;

class Monster
{
public:

	int health;
	string name;
	char abilities;
	string image;

	Monster(int health, string name, char abilites);
	~Monster();
	void CreateSprite(RenderWindow& window, Font font, string img, int nbBoss, float x, float y, float Sx, float Sy, Sprite boss); // Comme la fonction print mais avec les sprites
	void GettingDamaged();

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

void Monster::GettingDamaged() {
	//this->health -= ;
}

// La fameuse fonction avec 100000000 d'arguments xD
void Monster::CreateSprite(RenderWindow& window, Font font, string img, int nbBoss, float x, float y, float Sx, float Sy, Sprite boss) {
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