#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "Bullet.h"
#include "Enemy.h"
#include <vector>

#define PLAYER_H


class Player : public Entity
{
private:
    int health;
    sf::RectangleShape Pvbar;
    static const int MAX_BULLETS = 10000000;
    Bullet* bullets[MAX_BULLETS];;
    int bulletCount;
    bool canFire;
    float fireDelay;
    float fireCooldown;

public:
    Player(int health);
    ~Player();
    void Update(float deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void Fire();
    void TakeDamage(int damage);

    Bullet*getBullet(int index) const;
    int getBulletCount() const;
};