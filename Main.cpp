#include <iostream>
#include "Game.h"
#include"Player.h"
#include"Menu.h"
#include<time.h>

int sceneIndex = 0;
int main()
{
    RenderWindow window(VideoMode(1920,1080), "Don't Touch My Town", Style::Titlebar | Style::Close);
    window.setFramerateLimit(144);
   
    //Init srand
    std::cout << "Hello im running" << std::endl;
    srand(static_cast<unsigned>(time(NULL)));
    //Init Game Engine

     Game game;
     game.setWindow(&window);
     Menu menu(1920, 1080);
     menu.setWindow(&window);

     //เชื่อมเข้าด้วยกันใช้scene
     vector <Scene*> scenes;
     scenes.push_back(&menu);
     scenes.push_back(&game);


     float deltaTime;
     Clock clock;
    //Game loop
     while (game.running())
     {
         deltaTime = clock.restart().asSeconds();
         //Update
         scenes[sceneIndex]->update(deltaTime);
         //Render
         scenes[sceneIndex]->render();
         //menu.render();

     }
     //End of application
    return 0;
}