#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Boss : public Enemy
{
private:
    sf::RectangleShape healthBar;
    static const int MAX_BULLETS = 100;
    Bullet* bullets[MAX_BULLETS];
    int bulletCount;
    float fireDelay;
    float fireCooldown;
    int health;
    float moveSpeed;       // Vitesse de déplacement du boss
    int direction;         // Direction du déplacement (1 pour droite, -1 pour gauche)
    float leftLimit;       // Limite gauche du mouvement
    float rightLimit;      // Limite droite du mouvement

public:
    Boss(sf::Texture& texture, int health);
    void Update(float deltaTime);
    void Fire();
    void TakeDamage(int damage);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::RectangleShape& getHealthBar() { return healthBar; }
};



