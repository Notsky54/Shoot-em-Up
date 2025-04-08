#pragma once
#include "SceneManager.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include"Button.h"
#include "ScrollingMap.h"


#define GAMEMANAGER_H

class GameManager
{
private:
    sf::RenderWindow window;
    SceneManager sceneManager;
    Menu Menu;
    bool isRunning = true;
    bool isInMenu = true;
    Scene* mainScene;
    Button* button;
   

public:
    GameManager();
    ~GameManager();
    void Run();
};
