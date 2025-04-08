#include "Boss.h"
#include <iostream>

Boss::Boss(sf::Texture& texture, int health) : Enemy(health)
{
    this->health = health;
    this->bulletCount = 0;
    this->fireDelay = 1.0f;
    this->fireCooldown = 0.0f;
    this->moveSpeed = 100.f;
    this->direction = 1;

    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setScale(1.0f, 1.0f);

    healthBar.setSize(sf::Vector2f(100, 10));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setOrigin(healthBar.getSize().x / 2, sprite.getGlobalBounds().height / 2 + 15);
    healthBar.setPosition(100.0f, 80.f);

    leftLimit = 50; 
    rightLimit = 1600; 
}

void Boss::Update(float deltaTime)
{
    fireCooldown -= deltaTime;

    // Mouvement de gauche à droite
    sf::Vector2f position = sprite.getPosition();
    if (position.x <= leftLimit)
    {
        direction = 1; // Changer la direction vers la droite
    }
    else if (position.x >= rightLimit)
    {
        direction = -1; // Changer la direction vers la gauche
    }
    sprite.move(direction * moveSpeed * deltaTime, 0);

    // Mettre à jour les bullets
    for (int i = 0; i < bulletCount; ++i) {
        if (bullets[i] != nullptr) {
            bullets[i]->Update(deltaTime);
        }
    }

    // Supprimer les bullets hors écran
    for (int i = 0; i < bulletCount; ++i) {
        if (bullets[i]->isOffScreen()) {
            delete bullets[i];
            bullets[i] = nullptr;
            for (int j = i; j < bulletCount - 1; ++j) {
                bullets[j] = bullets[j + 1];
            }
            bullets[bulletCount - 1] = nullptr;
            --bulletCount;
            --i;
        }
    }

    if (fireCooldown <= 0.f) {
        Fire();
        fireCooldown = fireDelay;
    }

    healthBar.setPosition(sprite.getPosition().x - healthBar.getSize().x / 2,
        sprite.getPosition().y - sprite.getGlobalBounds().height / 2 - 15);
}

void Boss::Fire()
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

void Boss::TakeDamage(int damage)
{
    health -= damage;
    if (health <= 0) {
        health = 0;
    }

    healthBar.setSize(sf::Vector2f(100.f * (static_cast<float>(health) / 500.f), 10.f));
    if (health <= 0) {
        sprite.setColor(sf::Color::Transparent);
    }
}

void Boss::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(healthBar, states);

    for (int i = 0; i < bulletCount; ++i) {
        if (bullets[i] != nullptr) {
            target.draw(*bullets[i], states);
        }
    }
}
