#include "Player.h"
#include <SFML/Window.hpp>
#include<iostream>

Player::Player(int health) : Entity("../../../res/player.png")
{
    this->health = health;
    canFire = true;
    fireCooldown = 0.f;
    bulletCount = 0;

    getSprite().setOrigin(getSprite().getGlobalBounds().width / 2, getSprite().getGlobalBounds().height / 2);
    getSprite().setScale(0.3f, 0.3f); 

    Pvbar.setSize(sf::Vector2f(50.f, 5.f));
    Pvbar.setFillColor(sf::Color::Green);
    Pvbar.setPosition(-50.0f, 80.f);
    Pvbar.setScale(2, 2);

}



Player::~Player() 
{
    for (int i = 0; i < bulletCount; ++i)
    {
        delete bullets[i];
    }
}

void Player::Update(float deltaTime)
{
    // Déplacement du joueur avec la souris
    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    fireCooldown -= deltaTime;

    if (fireCooldown <= 0.f && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Fire(); 
        fireCooldown = 0.2f;  
    }

    // Mise à jour des projectiles
    for (int i = 0; i < bulletCount; ++i)
    {
        if (bullets[i] != nullptr)
        {
            bullets[i]->Update(deltaTime);

            // Vérifier si la balle est hors écran
            if (bullets[i]->isOffScreen())
            {
                delete bullets[i];
                bullets[i] = bullets[bulletCount - 1];
                bullets[bulletCount - 1] = nullptr;
                --bulletCount;
                --i;
            }
        }
    }
}


void Player::Fire() 
{
    if (bulletCount < MAX_BULLETS)  
    {
        sf::Vector2f position = sprite.getPosition();

        
        position.y -= sprite.getGlobalBounds().height / 2;

        // Direction vers le haut
        sf::Vector2f direction(0.f, -1.f);

        // Créez une balle avec la position correcte
        bullets[bulletCount] = new Bullet(position, direction, 500.f);

        ++bulletCount;  
    }
    else
    {
        std::cout << "Erreur : bulletCount depasse la capacite !" << std::endl;
    }
    std::cout << "Bullet count: " << bulletCount << std::endl;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    states.transform *= getTransform();
    target.draw(sprite, states);
    target.draw(Pvbar, states);

    for (int i = 0; i < bulletCount; ++i)
    {
        if (bullets[i] != nullptr) 
        { 
            target.draw(*bullets[i], states); 
        } 
    }
}


void Player::TakeDamage(int damage)
{
    health -= damage;
    if (health < 0) health = 0;

    // Mettre à jour la couleur de la barre de vie en fonction de la santé
    Pvbar.setSize(sf::Vector2f(50.f * (health / 100.f), 5.f));
    if (health <= 20) Pvbar.setFillColor(sf::Color::Red);  // La barre devient rouge si la vie est faible
}

Bullet* Player::getBullet(int index) const
{
    if (index >= 0 && index < bulletCount)
    {
        return bullets[index];  // Retourne le projectile à l'index spécifié
    }
    return nullptr;  // Retourne null si l'index est invalide
}

int Player::getBulletCount() const
{
    return bulletCount;  // Retourne le nombre de projectiles
}

