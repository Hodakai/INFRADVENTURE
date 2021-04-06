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
#include "Monster.h"
#include "Weapon.h"

using namespace std;
using namespace sf;


class Player : public Weapon
{
public:
	int money;
	int health;
	string name;
	Weapon* weapon;

	Player(int money, int health, string name, Weapon* weapon);

private:


};

//Constructeur
Player::Player(int money, int health, string name, Weapon* weapon) {
	this->money = money;
	this->health = health;
	this->name = name;
	this->weapon = weapon;
}
