#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include "Button.h"

using namespace std;
using namespace sf;

void Tuto(RenderWindow& window) {

    Texture tuto;
    Sprite sprite_tuto;
   

    if (!tuto.loadFromFile("InfradventureEZ.png"))
    {
        std::cout << "Erreur de chargement du Tuto" << std::endl;
    }
    sprite_tuto.setTexture(tuto);

    Font arial;
    arial.loadFromFile("arial.ttf");
    Button btnQuit2("      Quit", { 200, 50 }, 20, Color::Cyan, Color::Black);
    btnQuit2.setPosition({ 20, 900 });
    btnQuit2.setFont(arial);
    

    int i = 0;
    while (i != 1) {
        
            Event event;
            while (window.pollEvent(event))
            {
               
                if (event.type == Event::MouseMoved) {

                    if (btnQuit2.isMouseHover(window))
                    {
                        btnQuit2.setBackColor(Color(0, 139, 139));
                    }
                    else {
                        btnQuit2.setBackColor(Color::Cyan);
                    }
                }
                if (event.type == Event::MouseButtonPressed)
                {
                    if (btnQuit2.isMouseHover(window))
                    {
                        cout << "log : Quit Tuto" << endl;
                        btnQuit2.setBackColor(Color(200, 200, 200));
                        i++;
                    }
                }
            }

            window.clear(Color(128, 128, 128));
            window.draw(sprite_tuto);
            btnQuit2.Draw(window);           
            window.display();
        }
    
}

int main()
{
    RenderWindow window(VideoMode(1920, 1080), "Infradventure", Style::Fullscreen);
    Font arial;
    arial.loadFromFile("arial.ttf");

    Button btnStart("Start Game", {200, 50}, 20, Color::Cyan, Color::Black);
    btnStart.setPosition({50, 100});
    btnStart.setFont(arial);

    Button btnTuto("  Tutoriel", { 200,50 }, 20, Color::Cyan, Color::Black);
    btnTuto.setPosition({ 50, 200 });
    btnTuto.setFont(arial);

    Button btnQuit(" Quit Game", {200, 50}, 20, Color::Cyan, Color::Black);
    btnQuit.setPosition({1650, 100});
    btnQuit.setFont(arial);

    Texture MainMenu;
    Sprite sprite_MainMenu;

    if (!MainMenu.loadFromFile("InfradventureMainMenu.png"))
    {
        std::cout << "Erreur de chargement du Tuto" << std::endl;
    }
    sprite_MainMenu.setTexture(MainMenu);



    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseMoved) {
                if (btnStart.isMouseHover(window))
                {
                    btnStart.setBackColor(Color(0, 139, 139));
                }
                else {
                    btnStart.setBackColor(Color::Cyan);
                }

                if (btnQuit.isMouseHover(window))
                {
                    btnQuit.setBackColor(Color(0, 139, 139));
                }
                else {
                    btnQuit.setBackColor(Color::Cyan);
                }
                if (btnTuto.isMouseHover(window))
                {
                    btnTuto.setBackColor(Color(0, 139, 139));
                }
                else {
                    btnTuto.setBackColor(Color::Cyan);
                }
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (btnStart.isMouseHover(window))
                {
                    btnStart.setBackColor(Color(200,200,200));
                }
                if (btnQuit.isMouseHover(window))
                {
                    cout << "log : Au revoir" << endl;
                    btnQuit.setBackColor(Color(200, 200, 200));
                    window.close();
                }
                if (btnTuto.isMouseHover(window))
                {
                    btnStart.setBackColor(Color(200, 200, 200));
                    Tuto(window);
                }
            }
            window.clear(Color(128, 128, 128));
            window.draw(sprite_MainMenu);
            btnStart.Draw(window);
            btnQuit.Draw(window);
            btnTuto.Draw(window);

            window.display();
            
        }
    }
}
