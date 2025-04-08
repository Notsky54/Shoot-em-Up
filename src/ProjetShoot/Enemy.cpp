#include "Enemy.h"
#include<cmath>
#include <iostream>

Enemy::Enemy(int health) : Entity("../../../res/enemy2.png") 
{
    health = 20;
    damage = 20;
    fireDelay = 2.0f;
    fireCooldown = 0.f; 
    bulletCount = 0;

    getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
    getSprite().setScale(0.3f, 0.3f);  

    healthBar.setSize(sf::Vector2f(50.f, 8.f));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setOrigin(healthBar.getSize().x / 2, getSprite().getGlobalBounds().height / 2 + 10);

    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        bullets[i] = nullptr;
    }
}

Enemy::~Enemy()
{
    for (int i = 0; i < bulletCount; ++i)
    {
        delete bullets[i];
    }
}

void Enemy::TakeDamage(int damage)
{
    health -= damage;
    if (health <= 0)
    {
        health = 0;
        getSprite().setColor(sf::Color::Transparent); // L'ennemi disparaît lorsqu'il meurt
    }

    healthBar.setSize(sf::Vector2f(50.f * (static_cast<float>(health) / 100.f), 5.f));
}

void Enemy::Fire()
{
    if (bulletCount < MAX_BULLETS)
    {
        bullets[bulletCount] = new Bullet(sprite.getPosition(), sf::Vector2f(0, 1), 300.0f); // Direction vers le bas
        ++bulletCount;
    }
    else
    {
        std::cerr << "Erreur : Tentative de tir alors que le tableau de balles est plein !" << std::endl;
    }
}

void Enemy::Update(float deltaTime)
{
    fireCooldown -= deltaTime;

    getSprite().move(0.f, 100.f * deltaTime); 

    healthBar.setPosition(getSprite().getPosition().x, getSprite().getPosition().y - getSprite().getGlobalBounds().height / 2 - 10);

    // Balles tirées par l'ennemi
    for (int i = 0; i < bulletCount; ++i)
    {
        if (bullets[i] != nullptr)
        {
            bullets[i]->Update(deltaTime);
        }
    }

    // Supprimer les balles hors écran
    for (int i = 0; i < bulletCount; ++i)
    {
        if (bullets[i]->isOffScreen())
        {
            delete bullets[i];
            bullets[i] = nullptr;
            // Décalage des balles restantes
            for (int j = i; j < bulletCount - 1; ++j)
            {
                bullets[j] = bullets[j + 1];
            }
            bullets[bulletCount - 1] = nullptr;
            --bulletCount;
            --i;
        }
    }
    if (fireCooldown <= 0.f)
    {
        Fire();
        fireCooldown = fireDelay;
    }

}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(healthBar, states);

    for (int i = 0; i < bulletCount; ++i)
    {
        if (bullets[i] != nullptr)
        {
            target.draw(*bullets[i], states);
        }
    }
}



sf::FloatRect Enemy::getGlobalBounds() const
{
    return sprite.getGlobalBounds();  
}

int Enemy::getHealth() const
{
    return health;
}

Bullet* Enemy::getBullet(int index) const
{
    if (index >= 0 && index < bulletCount)
    {
        return bullets[index];  
    }
    return nullptr;  
}

int Enemy::getBulletCount() const
{
    return bulletCount;  
}