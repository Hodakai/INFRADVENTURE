#include "Header.h"
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
                window.clear();

                window.draw(sprite_tuto);
                btnQuit2.Draw(window);

                window.display();

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
        }   
}


void Game(RenderWindow& window, Font font) {
    Music theme;
    if (!theme.openFromFile("Avengers.ogg")) {
        cout << "Could not load music theme..." << endl; //Open le fichier du theme principal
    }
    theme.setVolume(1);

    SoundBuffer bufferPunch;
    if (!bufferPunch.loadFromFile("Hitmarker.ogg")) {
        cout << "Could not load Punch sound..." << endl; //Open le fichier du son d'attaque pour le mettre dans le buffer
    }

    Sound Hit;
    Hit.setBuffer(bufferPunch); //On utillise le son que l'on a mis dans le buffer pour l'attribuer à un élément de type sound pour pouvoir l'utiliser après
    Hit.setVolume(4);

    SoundBuffer Sunfire;
    if (!Sunfire.loadFromFile("Sunfire.ogg")) {
        cout << "Could not load pk fire sound..." << endl; //Open le fichier du son d'attaque pour le mettre dans le buffer
    }

    Sound pkfire;
    pkfire.setBuffer(Sunfire); //On utillise le son que l'on a mis dans le buffer pour l'attribuer à un élément de type sound pour pouvoir l'utiliser après
    pkfire.setVolume(15);

    SoundBuffer Heal;
    if (!Heal.loadFromFile("HealSound.ogg")) {
        cout << "Could not load pk fire sound..." << endl; //Open le fichier du son d'attaque pour le mettre dans le buffer
    }

    Sound heal;
    heal.setBuffer(Heal); //On utillise le son que l'on a mis dans le buffer pour l'attribuer à un élément de type sound pour pouvoir l'utiliser après
    heal.setVolume(10);

    SoundBuffer Fullcrit;
    if (!Fullcrit.loadFromFile("Fullcrit.ogg")) {
        cout << "Could not load pk fire sound..." << endl; //Open le fichier du son d'attaque pour le mettre dans le buffer
    }

    Sound fullcrit;
    fullcrit.setBuffer(Fullcrit); //On utillise le son que l'on a mis dans le buffer pour l'attribuer à un élément de type sound pour pouvoir l'utiliser après
    fullcrit.setVolume(3);

    Texture SunFireTexture;
    Sprite sprite_sunfire;
    if (!SunFireTexture.loadFromFile("Sun_Fire_Spell.png"))
    {
        std::cout << "Erreur de chargement du Tuto" << std::endl;
    }
    sprite_sunfire.setTexture(SunFireTexture);
    sprite_sunfire.setPosition(500, 0);


    Texture HealTexture;
    Sprite sprite_heal;
    if (!HealTexture.loadFromFile("Heal.png"))
    {
        std::cout << "Erreur de chargement du Heal.php" << std::endl;
    }
    sprite_heal.setTexture(HealTexture);
    sprite_heal.setPosition(275, 0);

    Texture FondFight;
    Sprite sprite_FondFight;

    if (!FondFight.loadFromFile("FondFight.png"))
    {
        std::cout << "Erreur de chargement du FondFight" << std::endl;
    }
    sprite_FondFight.setTexture(FondFight);

    /*Sprite HitSprite;
    Texture textureHit;

    if (!textureHit.loadFromFile("HitmarkerIMG.png")) { // L'img ici c'est la string du nom de l'image qui doit être dans ton dossier comme la font ;) 

        cout << "Texture : HitmarkerIMG.png, loading failed..." << endl; // Message d'erreur dans les logs si une texture ne load pas ^^
        system("pause");

    }
    HitSprite.setTexture(textureHit);
    HitSprite.scale(.1, .1);
    */
    Weapon* weapon = new Weapon(1, "Epee en carton", 125, .1, 1, 5);//            
    Player* player = new Player(100, 1, 1, 100, "Hodaka", weapon);//                                                       }---- Création des éléments principaux du jeu 
    Monster* monster = new Monster(1000, .5,"Meca-Bot", "Meca-Bot est l'un des sbires\ndu tristement célèbre Meca-\nDoom il faut le mettre hors\nservice afin de pouvoir\nesperer acceder à\nMeca-Doom", 1, .1); // }

    Spell* spellA = new Spell("SunFire", 0, 0, 0, 5, 0, 20, 100);
    Spell* spellZ = new Spell("Heal", 0, 0, 0, 5, 0, 30, 50);
    Spell* spellE = new Spell("Fullcrit", 0, 0, 5, 5, 0, 60, 100);
    Spell* spellR = new Spell("Ultimate", 0, 0, 0, 1, 5, 300, 1000);
    HUD* GUI = new HUD(player, monster, weapon, font);
    GameEvents* game = new GameEvents;

    Sprite bossSprite;
    string monsterImg = "1stBOSS.png";

    Button btnAmeliorationSpellA("SunFire[0]", { 200, 50 }, 20, Color::Red, Color::White);
    btnAmeliorationSpellA.setPosition({ 1620, 400 });
    btnAmeliorationSpellA.setFont(font);

    Button btnAmeliorationSpellZ("   Heal[0]", { 200, 50 }, 20, Color::Blue, Color::White);
    btnAmeliorationSpellZ.setPosition({ 1370, 400 });
    btnAmeliorationSpellZ.setFont(font);

    Button btnAmeliorationSpellE("FullCrit[0]", { 200, 50 }, 20, Color::Black, Color::White);
    btnAmeliorationSpellE.setPosition({ 1370, 500 });
    btnAmeliorationSpellE.setFont(font);

    Button btnAmeliorationSpellR("Ultimate[0]", { 200, 50 }, 20, Color::Magenta, Color::White);
    btnAmeliorationSpellR.setPosition({ 1620, 500 });
    btnAmeliorationSpellR.setFont(font);

   
    Color color = (Color(100, 65, 30));

    Button btnAmeliorationArme("Arme lvl : Bois / Click lvlUp++", { 450, 50 }, 20, Color(color), Color::White);
    btnAmeliorationArme.setPosition({ 1370, 600 });
    btnAmeliorationArme.setFont(font);
   
    game->Intro(font, window);
    
    int i = 0;
    int CountClickA = 20;
    int CountClickZ = 30;
    int CountClickE = 60;
    int CountClickR = 300;

    int nameX = 800.f;
    int nbMonsterDeafeated = 0; // Ici on initialise une variable qui va nous servir à savoir le nombre de boss batus au cours de la partie
    int bossX, bossY, bossSX, bossSY; // Variables pour la position de l'image du premier monstre pour pouvoir y acceder facilement
    bossX = 650;
    bossY = 200;
    bossSX = 3;
    bossSY = 3;
    theme.play();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            window.clear();

            window.draw(sprite_FondFight);

            btnAmeliorationSpellA.Draw(window);
            btnAmeliorationSpellZ.Draw(window);
            btnAmeliorationSpellE.Draw(window);
            btnAmeliorationSpellR.Draw(window);
            btnAmeliorationArme.Draw(window);

            GUI->InitHUD(window, nameX); // Lancement de la fonction qui va se charger d'afficher tout le menu dans le jeu

            Sprite MonsterBoss = monster->CreateSprite(window, font, monsterImg, bossX, bossY, bossSX, bossSY, bossSprite); // Création et affichage du sprite du monstre

            if (MonsterBoss.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && event.type == Event::MouseButtonPressed) // ici on check les bordures de l'image du boss et on vérifie si la souris est dedans
            {                                                                                             // si elle est dedans et que l'on clique sur la souris, alors -|  
                Hit.play(); //Son joué lors d'une attaque
                CountClickA++;
                CountClickZ++;
                CountClickE++;
                CountClickR++;
                monster->GettingDamaged(weapon, game, window, font);                                                                          
                player->GettingDamaged(monster, game, window, font); //Ici cette fonction représente l'attaque que le monstre peut réaliser envers le joueur, le joueur peut ne pas prendre de dégats lors de son attaque		    					 

                player->money++;                                              //Augmentation de l'argent du joueur pour améliorer le personnage
                CreateHitSprite(window, font); // Fonction pour créer un sprite pour chaque clic de souris du joueur afin qu'il soit sur la souris a chaque fois
                if (monster->health < 1)
                {
                    nbMonsterDeafeated++;
                    if (nbMonsterDeafeated == 1) {
                        game->WinFirstBoss(font, window);
                        monster->SetMonster(2, 250, "Infra-Knight", "Infra-Knight, le frère\nmaléfique de Meca-Doom\nveut protéger son\nfrère machiavélique !!!\n\nPoint faible :\nIl reste humain à\nl'interieur...", 5, .3);
                        monsterImg = "2ndBOSS.png";
                        nameX = 750.f;
                        bossX = 625;
                        bossY = 250;
                        bossSX = 1;
                        bossSY = 1;
                    }
                    else if (nbMonsterDeafeated == 2) {
                        game->WinSecondBoss(font, window);
                        monster->SetMonster(2, 250, "Infra-Doom", "Ce robot venant du futur\nest venu détruire le monde !!!\nSeul nous peuvent\nauver l'humanité !!!\n\nPoint faible :\nTROP FORT !!!", 10, .4);
                        monsterImg = "3rdBOSS.png";
                        bossX = 500;
                        bossY = 200;
                    }
                    else if (nbMonsterDeafeated == 3) {
                        game->WinThirdBoss(font, window);
                        monster->SetMonster(2, 250, "Ship of Infra-Doom", "Meca-Doom s'enfuit !!!\nIl est parti a bord de son\nvaisseau armageddon !\nIl faut le mettre hors d'état\nde nuire !!!\n\nPoint faible :\nVOUS !!!", 15, .5);
                        monsterImg = "4thBOSS.png";
                        nameX = 650.f;
                        bossX = 450;
                        bossY = 340;
                        bossSX = 2;
                        bossSY = 2;
                    }
                    else if (nbMonsterDeafeated == 4) {
                        game->Ending(font, window);
                        //free();
                        window.close();
                    }
                }
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::A && spellA->getlvl() > 0 && CountClickA >= spellA->cooldown) {
                    cout << "SunFire !!!!!" << endl;
                    CountClickA = 0;
                    window.draw(sprite_sunfire);
                    pkfire.play();
                    monster->GettingDamagedFromSpellA(spellA, game, window, font);
                    cout << "monster hp " << monster->health << endl;
                    if (monster->health < 1)
                    {
                        nbMonsterDeafeated++;
                        if (nbMonsterDeafeated == 1) {
                            game->WinFirstBoss(font, window);
                            monster->SetMonster(100, 5,"Infra-Knight", "Infra-Knight, le frère\nmaléfique de Meca-Doom\nveut protéger son\nfrère machiavélique !!!\n\nPoint faible :\nIl reste humain à\nl'interieur...", 5, .3);
                            monsterImg = "2ndBOSS.png";
                            nameX = 750.f;
                            bossX = 625;
                            bossY = 250;
                            bossSX = 1;
                            bossSY = 1;
                        }
                        else if (nbMonsterDeafeated == 2) {
                            game->WinSecondBoss(font, window);
                            monster->SetMonster(2, 5 ,"Infra-Doom", "Ce robot venant du futur\nest venu détruire le monde !!!\nSeul nous peuvent\nauver l'humanité !!!\n\nPoint faible :\nTROP FORT !!!", 10, .4);
                            monsterImg = "3rdBOSS.png";
                            bossX = 500;
                            bossY = 200;
                        }
                        else if (nbMonsterDeafeated == 3) {
                            game->WinThirdBoss(font, window);
                            monster->SetMonster(2, 5 ,"Ship of Infra-Doom", "Meca-Doom s'enfuit !!!\nIl est parti a bord de son\nvaisseau armageddon !\nIl faut le mettre hors d'état\nde nuire !!!\n\nPoint faible :\nVOUS !!!", 15, .5);
                            monsterImg = "4thBOSS.png";
                            nameX = 650.f;
                            bossX = 450;
                            bossY = 340;
                            bossSX = 2;
                            bossSY = 2;
                        }
                        else if (nbMonsterDeafeated == 4) {
                            game->Ending(font, window);
                            //free();
                            window.close();
                        }
                    }
                }
                if (event.key.code == Keyboard::Z && spellZ->getlvl() > 0 && CountClickZ >= spellZ->cooldown) {
                    cout << "Heal !!!!!" << endl;
                    CountClickZ = 0;
                    heal.play();
                    window.draw(sprite_heal);
                    player->heal();
                }
                if (event.key.code == Keyboard::E && spellE->getlvl() > 0 && CountClickE >= spellE->cooldown) {
                    CountClickE = 0;
                    int compteur = spellE->fullCritTime;
                    float oldWeaponcrit = weapon->crit;
                    cout << "old weapon crit : " << oldWeaponcrit << endl;
                    Display Fullcrit;

                    if (compteur == 10 || compteur == 15 || compteur == 20 || compteur == 25 || compteur == 30) {
                        fullcrit.play();
                    }
                    while (compteur != 0) {
                        while (window.pollEvent(event)) {

                            window.clear();

                            window.draw(sprite_FondFight);

                            btnAmeliorationSpellA.Draw(window);
                            btnAmeliorationSpellZ.Draw(window);
                            btnAmeliorationSpellE.Draw(window);
                            btnAmeliorationSpellR.Draw(window);
                            btnAmeliorationArme.Draw(window);

                            GUI->InitHUD(window, nameX); // Lancement de la fonction qui va se charger d'afficher tout le menu dans le jeu                           

                            Sprite MonsterBoss = monster->CreateSprite(window, font, monsterImg, bossX, bossY, bossSX, bossSY, bossSprite);

                            String textFullcrit = "FullCrit Time !!!! X" + to_string(compteur);
                            Fullcrit.Print(font, 50, window, textFullcrit, 725, 900, Color::Yellow);



                            if (event.type == Event::MouseButtonPressed && MonsterBoss.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                                Hit.play();

                                compteur--;
                                CountClickA++;
                                CountClickZ++;
                                CountClickR++;
                                weapon->crit = 1;

                                Sprite HitSprite;
                                Texture textureHit;
                                HitSprite.setTexture(textureHit);
                                Vector2f offset(-25.f, -25.f); //On crée un vector qui va corriger l'offset présent sur le png du kitmarker
                                HitSprite.setPosition(window.mapPixelToCoords(Mouse::getPosition(window)) + offset); //On rajoutte le vector que l'on a créé aux coordonées de la souris
                                player->money++; //Augmentation de l'argent du joueur pour acheter des items dans la boutique 
                                HitSprite.scale(.1, .1);
                                window.draw(HitSprite);

                                monster->GettingDamaged(weapon, game, window, font);
                                player->GettingDamaged(monster, game, window, font);

                                cout << "monster hp " << monster->health << endl;
                                if (monster->health < 1)
                                {
                                    nbMonsterDeafeated++;
                                    if (nbMonsterDeafeated == 1) {
                                        game->WinFirstBoss(font, window);
                                        monster->SetMonster(2, 250,"Infra-Knight", "Infra-Knight, le frère\nmaléfique de Meca-Doom\nveut protéger son\nfrère machiavélique !!!\n\nPoint faible :\nIl reste humain à\nl'interieur...", 5, .3);
                                        monsterImg = "2ndBOSS.png";
                                        nameX = 750.f;
                                        bossX = 625;
                                        bossY = 250;
                                        bossSX = 1;
                                        bossSY = 1;
                                    }
                                    else if (nbMonsterDeafeated == 2) {
                                        game->WinSecondBoss(font, window);
                                        monster->SetMonster(2, 250,"Infra-Doom", "Ce robot venant du futur\nest venu détruire le monde !!!\nSeul nous peuvent\nauver l'humanité !!!\n\nPoint faible :\nTROP FORT !!!", 10, .4);
                                        monsterImg = "3rdBOSS.png";
                                        bossX = 500;
                                        bossY = 200;
                                    }
                                    else if (nbMonsterDeafeated == 3) {
                                        game->WinThirdBoss(font, window);
                                        monster->SetMonster(2, 250,"Ship of Infra-Doom", "Meca-Doom s'enfuit !!!\nIl est parti a bord de son\nvaisseau armageddon !\nIl faut le mettre hors d'état\nde nuire !!!\n\nPoint faible :\nVOUS !!!", 15, .5);
                                        monsterImg = "4thBOSS.png";
                                        nameX = 650.f;
                                        bossX = 450;
                                        bossY = 340;
                                        bossSX = 2;
                                        bossSY = 2;
                                    }
                                    else if (nbMonsterDeafeated == 4) {
                                        game->Ending(font, window);
                                        //free();
                                        window.close();
                                    }
                                }

                            }
                            window.display();
                        }
                    }

                    cout << "\nEnd of FullCritTime !!!!! " << endl;
                    if (compteur < 1) {
                        fullcrit.stop();
                    }
                    weapon->crit = oldWeaponcrit;
                }

                if (event.key.code == Keyboard::R && spellA->getlvl() > 0)
                {
                    CountClickR = 0;
                    int compteur = spellR->UltimateTime;

                    Display Ultimate;

                    while (compteur != 0) {

                        while (window.pollEvent(event)) {
                            window.clear();

                            window.draw(sprite_FondFight);

                            btnAmeliorationSpellA.Draw(window);
                            btnAmeliorationSpellZ.Draw(window);
                            btnAmeliorationSpellE.Draw(window);
                            btnAmeliorationSpellR.Draw(window);
                            btnAmeliorationArme.Draw(window);

                            GUI->InitHUD(window, nameX);
                            // Lancement de la fonction qui va se charger d'afficher tout le menu dans le jeu

                            Sprite MonsterBoss = monster->CreateSprite(window, font, monsterImg, bossX, bossY, bossSX, bossSY, bossSprite);

                            String textUltimate = "Ultimate !!!! Sunfire illimited X" + to_string(compteur);
                            Ultimate.Print(font, 50, window, textUltimate, 725, 900, Color::Cyan);
                     
                            if (event.type == Event::KeyReleased) {
                                if (event.key.code == Keyboard::A && spellA->getlvl() > 0) {
                                    compteur--;

                                    window.draw(sprite_sunfire);
                                    pkfire.play();
                                    monster->GettingDamagedFromSpellA(spellA, game, window, font);

                                    if (monster->health < 1)
                                    {
                                        nbMonsterDeafeated++;
                                        if (nbMonsterDeafeated == 1) {
                                            game->WinFirstBoss(font, window);
                                            monster->SetMonster(2, 250,"Infra-Knight", "Infra-Knight, le frère\nmaléfique de Meca-Doom\nveut protéger son\nfrère machiavélique !!!\n\nPoint faible :\nIl reste humain à\nl'interieur...", 5, .3);
                                            monsterImg = "2ndBOSS.png";
                                            nameX = 750.f;
                                            bossX = 625;
                                            bossY = 250;
                                            bossSX = 1;
                                            bossSY = 1;
                                        }
                                        else if (nbMonsterDeafeated == 2) {
                                            game->WinSecondBoss(font, window);
                                            monster->SetMonster(2,250 ,"Infra-Doom", "Ce robot venant du futur\nest venu détruire le monde !!!\nSeul nous peuvent\nauver l'humanité !!!\n\nPoint faible :\nTROP FORT !!!", 10, .4);
                                            monsterImg = "3rdBOSS.png";
                                            bossX = 500;
                                            bossY = 200;
                                        }
                                        else if (nbMonsterDeafeated == 3) {
                                            game->WinThirdBoss(font, window);
                                            monster->SetMonster(2, 250,"Ship of Infra-Doom", "Meca-Doom s'enfuit !!!\nIl est parti a bord de son\nvaisseau armageddon !\nIl faut le mettre hors d'état\nde nuire !!!\n\nPoint faible :\nVOUS !!!", 15, .5);
                                            monsterImg = "4thBOSS.png";
                                            nameX = 650.f;
                                            bossX = 450;
                                            bossY = 340;
                                            bossSX = 2;
                                            bossSY = 2;
                                        }
                                        else if (nbMonsterDeafeated == 4) {
                                            game->Ending(font, window);
                                            //free();
                                            window.close();
                                        }
                                    }

                                }
                            }
                            window.display();
                        }
                    }
                }
            }

            if (event.type == Event::MouseMoved) {
                if (btnAmeliorationSpellA.isMouseHover(window))
                {
                    btnAmeliorationSpellA.setBackColor(Color(0, 139, 139));
                }
                else {
                    btnAmeliorationSpellA.setBackColor(Color::Red);
                }

                if (btnAmeliorationSpellZ.isMouseHover(window))
                {
                    btnAmeliorationSpellZ.setBackColor(Color(0, 139, 139));
                }
                else {
                    btnAmeliorationSpellZ.setBackColor(Color::Blue);
                }
                if (btnAmeliorationSpellE.isMouseHover(window))
                {
                    btnAmeliorationSpellE.setBackColor(Color(0, 139, 139));
                }
                else {
                    btnAmeliorationSpellE.setBackColor(Color::Magenta);
                }
                if (btnAmeliorationSpellR.isMouseHover(window))
                {
                    btnAmeliorationSpellR.setBackColor(Color(0, 139, 139));
                }
                else {
                    btnAmeliorationSpellR.setBackColor(Color::Black);
                }
                if (btnAmeliorationArme.isMouseHover(window))
                {
                    btnAmeliorationArme.setBackColor(Color(0, 139, 139));
                }
                else {
                    btnAmeliorationArme.setBackColor(Color(color));
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (btnAmeliorationSpellA.isMouseHover(window))
                {
                    spellA->LvlUpSpell(player->money);
                    if (spellA->verifAchat == 1) {
                        spellA->verifAchat = 0;
                        player->money -= spellA->cost;
                        spellA->cost += 40;
                        if (spellA->cost == 140) {
                            cout << "Changement de nom" << endl;
                            btnAmeliorationSpellA.setText("SunFire[1]");
                        }
                        if (spellA->cost == 180) {
                            btnAmeliorationSpellA.setText("SunFire[2]");
                        }
                        if (spellA->cost == 220) {
                            btnAmeliorationSpellA.setText("SunFire[3]");
                        }
                        if (spellA->cost == 260) {
                            btnAmeliorationSpellA.setText("SunFire[4]");
                        }
                        if (spellA->cost == 300) {
                            btnAmeliorationSpellA.setText("SunFire[5]");
                        }
                    }
                    else {
                        cout << "t'es pauvre" << endl;
                    }

                }
                if (btnAmeliorationSpellZ.isMouseHover(window))
                {
                    spellZ->LvlUpSpell(player->money);
                    if (spellZ->verifAchat == 1) {
                        spellZ->verifAchat = 0;
                        player->money -= spellZ->cost;
                        spellZ->cost += 25;
                        if (spellZ->cost == 75) {
                            cout << "Changement de nom" << endl;
                            btnAmeliorationSpellZ.setText("   Heal[1]");
                        }
                        if (spellZ->cost == 100) {
                            btnAmeliorationSpellZ.setText("   Heal[2]");
                        }
                        if (spellZ->cost == 125) {
                            btnAmeliorationSpellZ.setText("   Heal[3]");
                        }
                        if (spellZ->cost == 150) {
                            btnAmeliorationSpellZ.setText("   Heal[4]");
                        }
                        if (spellZ->cost == 175) {
                            btnAmeliorationSpellZ.setText("   Heal[5]");
                        }
                    }
                    else {
                        cout << "t'es pauvre" << endl;
                    }

                }
                if (btnAmeliorationSpellE.isMouseHover(window))
                {
                    spellE->LvlUpSpell(player->money);
                    if (spellE->verifAchat == 1) {
                        spellE->verifAchat = 0;
                        player->money -= spellE->cost;
                        spellE->cost += 100;
                        if (spellE->cost == 200) {

                            btnAmeliorationSpellE.setText("FullCrit[1]");
                        }
                        if (spellE->cost == 300) {
                            btnAmeliorationSpellE.setText("FullCrit[2]");
                        }
                        if (spellE->cost == 400) {
                            btnAmeliorationSpellE.setText("FullCrit[3]");
                        }
                        if (spellE->cost == 500) {
                            btnAmeliorationSpellE.setText("FullCrit[4]");
                        }
                        if (spellE->cost == 600) {
                            btnAmeliorationSpellE.setText("FullCrit[5]");
                        }
                    }
                    else {
                        cout << "t'es pauvre" << endl;
                    }
                }
                if (btnAmeliorationSpellR.isMouseHover(window))
                {
                    spellR->LvlUpSpell(player->money);

                    if (spellR->verifAchat == 1) {
                        spellR->verifAchat = 0;
                        player->money -= spellR->cost;
                        spellR->cost += 100;
                        if (spellR->cost == 1100) {

                            btnAmeliorationSpellR.setText("Ultimate[1]");
                        }

                    }
                    else
                    {
                        cout << "t'es pauvre" << endl;
                    }

                }

                if (btnAmeliorationArme.isMouseHover(window))
                {
                    weapon->lvlUpWeapon(player->money);
                    if (weapon->verifAchat == 1) {
                        weapon->verifAchat = 0;
                        player->money -= weapon->cost;
                        weapon->cost += 100;
                        if (weapon->cost == 225) {
                            color = (Color(48, 48, 48));
                            btnAmeliorationArme.setText("Arme lvl : Stone / Click lvlUp++");
                        }
                        if (weapon->cost == 325) {
                            color = (Color(150, 150, 150));
                            btnAmeliorationArme.setText("Arme lvl : Iron / Click lvlUp++");
                        }
                        if (weapon->cost == 425) {
                            color = (Color(255, 225, 0));
                            btnAmeliorationArme.setText("Arme lvl : Gold / Click lvlUp++");
                            btnAmeliorationArme.setTextColor(Color::Black);
                        }
                        if (weapon->cost == 525) {
                            btnAmeliorationArme.setText("Arme lvl : Diamond / Click lvlUp++");
                            color = (Color(0, 205, 255));
                        }
                    }
                    else if (weapon->verifAchat == 2) {
                        cout << "Lvl Max Déja Atteind" << endl;
                    }
                    else {
                        cout << "Pas assez d'argent" << endl;
                    }
                }
            }
            window.display();
        }
    }
}

void Menu(RenderWindow& window) {
    Texture MainMenu;
    Sprite sprite_MainMenu;

    if (!MainMenu.loadFromFile("InfradventureMainMenu.png"))
    {
        std::cout << "Erreur de chargement du Tuto" << std::endl;
    }

    sprite_MainMenu.setTexture(MainMenu);
    Font arial;
    arial.loadFromFile("arial.ttf");



    Button btnStart("Start Game", { 200, 50 }, 20, Color::Cyan, Color::Black);
    btnStart.setPosition({ 50, 100 });
    btnStart.setFont(arial);

    Button btnTuto("  Tutoriel", { 200,50 }, 20, Color::Cyan, Color::Black);
    btnTuto.setPosition({ 50, 200 });
    btnTuto.setFont(arial);

    Button btnQuit(" Quit Game", { 200, 50 }, 20, Color::Cyan, Color::Black);
    btnQuit.setPosition({ 1650, 100 });
    btnQuit.setFont(arial);

    Event event;
    int i = 0;

    while (i != 1)
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }

            window.clear();

            window.draw(sprite_MainMenu);

            btnStart.Draw(window);
            btnQuit.Draw(window);
            btnTuto.Draw(window);

            window.display();

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
                    btnStart.setBackColor(Color(200, 200, 200));
                    window.clear();
                    i++;
                }
                if (btnQuit.isMouseHover(window))
                {
                    btnQuit.setBackColor(Color(200, 200, 200));
                    window.close();
                }
                if (btnTuto.isMouseHover(window))
                {
                    btnStart.setBackColor(Color(200, 200, 200));
                    Tuto(window);
                }
            }


        }

    }

}

int main()
{
    RenderWindow window(VideoMode(1920, 1080), "Infradventure");
    Font font;
    font.loadFromFile("arial.ttf");

    Image Icon;
    if (!Icon.loadFromFile("Icon.png")) {
        cout << "Could not load Icon..." << endl;
    }

    window.setIcon(100, 100, Icon.getPixelsPtr());




    Menu(window);
    Game(window,font);

    

    }