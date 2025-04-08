#include "Scene.h"
#include <cstdlib>

Scene::Scene() : entityCount(0), player(nullptr), scrollingBackground(nullptr), boss(nullptr), elapsedTime(0.f)
{
    for (int i = 0; i < 100; ++i)
    {
        entities[i] = nullptr;
    }
}

Scene::~Scene()
{
    for (int i = 0; i < entityCount; ++i)
    {
        delete entities[i];
    }
    delete scrollingBackground;
    delete boss;
}

void Scene::SetBackgroundGame(const std::string& textureFile, const sf::Vector2f& speed)
{
    if (backgroundTexture.loadFromFile(textureFile))
    {
        backgroundSprite.setTexture(backgroundTexture);
    }
}

void Scene::AddEntity(Entity* entity)
{
    if (entityCount < 100)
    {
        entities[entityCount++] = entity;
    }
}

void Scene::SetPlayer(Player* player)
{
    this->player = player;
    AddEntity(player);
}

Player* Scene::GetPlayer() const
{
    return player;
}

void Scene::Update(float deltaTime)
{
    elapsedTime += deltaTime;

    if (player != nullptr)
    {
        player->Update(deltaTime);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            player->Fire();
        }

        // Mise à jour des entités
        for (int i = 0; i < entityCount; ++i)
        {
            if (entities[i] != nullptr)
            {
                entities[i]->Update(deltaTime);
            }
        }

        // Mise à jour spécifique des ennemis
        for (int i = 0; i < entityCount; ++i)
        {
            Enemy* enemy = dynamic_cast<Enemy*>(entities[i]);
            if (enemy != nullptr)
            {
                enemy->Update(deltaTime);
            }
        }
    }

    SpawnEnemy(deltaTime); 

    // Vérifier si le boss doit apparaître 
    if (elapsedTime >= 25.0f && boss == nullptr)
    {
        // Chargement de la texture du boss une seule fois
        static sf::Texture bossTexture;  
        if (bossTexture.getSize().x == 0)  
        {
            if (!bossTexture.loadFromFile("../../../res/boss.png"))
            {
                std::cout << "Failed to load boss texture" << std::endl;
                throw std::runtime_error("Failed to load boss texture");
            }
            else
            {
                std::cout << "Boss texture loaded successfully!" << std::endl;
            }
        }

        // Créer et ajouter le boss à la scène
        if (boss == nullptr)
        {
            boss = new Boss(bossTexture, 500);
            boss->setPosition(0, 100); 
            AddEntity(boss);  
        }
    }
    if (boss != nullptr)
    {
        boss->Update(deltaTime);
    }
}


void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backgroundSprite, states);
    if (player != nullptr)
    {
        target.draw(*player, states);
    }
    for (int i = 0; i < entityCount; ++i)
    {
        if (entities[i] != nullptr)
        {
            target.draw(*entities[i], states);
        }
    }
    if (boss != nullptr)
    {
        target.draw(*boss, states);
    }
}

void Scene::SpawnEnemy(float deltaTime)
{
    static float timer = 0.0f;
    static bool startedSpawning = false;

    timer += deltaTime;

    if (!startedSpawning && timer >= 10.0f)
    {
        startedSpawning = true;
        timer = 0.0f;
    }

    if (startedSpawning)
    {
        // Vérifiez s'il y a encore des ennemis
        bool allEnemiesDead = true;
        for (int i = 0; i < entityCount; ++i)
        {
            if (entities[i] != nullptr && dynamic_cast<Enemy*>(entities[i]) != nullptr)
            {
                allEnemiesDead = false;
                break;
            }
        }
        if (timer >= 2.0f)  // Créer un ennemi tous les 2 secondes
        {
            int type = rand() % 2;
            Enemy* enemy;
            enemy = new Enemy(50);  

            float x = static_cast<float>(rand() % 1900);
            enemy->setPosition(x, -50);
            AddEntity(enemy);
            timer = 0.0f;
        }
    }
}

