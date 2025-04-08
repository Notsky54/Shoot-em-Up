#pragma once
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Boss.h"
#include "ScrollingMap.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#define SCENE_H

class Scene : public sf::Drawable
{
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Entity* entities[100];
    int entityCount;
    Player* player;
    ScrollingMap* scrollingBackground;
    Boss* boss; // Ajouter le boss
    int bulletCount;
    float elapsedTime; // Ajouter un chronomètre

public:
    Scene();
    ~Scene();
    void SetBackgroundGame(const std::string& textureFile, const sf::Vector2f& speed);
    void AddEntity(Entity* entity);
    void SetPlayer(Player* player);
    Player* GetPlayer() const;
    void Update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void SpawnEnemy(float deltaTime);
    bool isGameOver() const;
};
