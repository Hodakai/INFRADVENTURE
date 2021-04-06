#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <algorithm>
#include <string>
#include "Monster.h"
#include "Player.h"
#include "Weapon.h"

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
