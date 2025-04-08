#include "GameManager.h"
#include "Player.h"
#include "Enemy.h"


GameManager::GameManager()
{
    Menu.SetBackground("../../../res/menu.jpeg");
    Menu.AddOption("Play");
    Menu.AddOption("Quit");

    mainScene = new Scene();
    Player* player = new Player(100);
    mainScene->SetPlayer(player);
    player->setPosition(400, 300);

    mainScene->SetBackgroundGame("../../../res/map2.jpg", sf::Vector2f(0, 2));

    Enemy* enemy1 = new Enemy(50);

    sceneManager.AddScene("MainScene", mainScene);
    sceneManager.SetCurrentScene("MainScene");

    sf::Font font;

    button = new Button(sf::Vector2f(200, 50), font, "Quit", [&]()
        {
            isRunning = false;
        });
    button->setPosition(sf::Vector2f(20, 20));

}

GameManager::~GameManager()
{
    delete mainScene;
    delete button;
}

void GameManager::Run()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "ALBATAR", sf::Style::Fullscreen);
    sf::Clock clock;
    while (isRunning && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                isRunning = false;
            }

            if (isInMenu)
            {
                Menu.HandleInput(event, [&window, this](int selectedOption)
                    {
                        if (selectedOption == 0)
                        {
                            isInMenu = false;
                        }
                        else if (selectedOption == 2)
                        {
                            window.close();
                            isRunning = false;
                        }
                    });
            }
            else
            {
                button->handleEvent(event);
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    isRunning = false;
                }
            }
        }

        if (isInMenu)
        {
            Menu.Update();
            window.clear();
            window.draw(Menu);
            window.display();
        }
        else
        {
            float deltaTime = clock.restart().asSeconds();
            Scene* currentScene = sceneManager.GetCurrentScene();
            if (currentScene)
            {
                currentScene->Update(deltaTime);
                currentScene->SpawnEnemy(deltaTime);

                Player* player = static_cast<Player*>(currentScene->GetPlayer());
                if (player != nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    player->Fire();
                }
            }

            window.clear();
            if (currentScene)
            {
                window.draw(*currentScene);
            }
            window.display();
        }
    }
}
