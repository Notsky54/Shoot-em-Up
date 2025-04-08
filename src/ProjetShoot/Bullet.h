#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable
{
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f direction;
    sf::Vector2f position;
    float speed;
    int damage;

public:
    Bullet(const sf::Vector2f& position, const sf::Vector2f& direction, float speed);
    void Update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool isOffScreen() const;
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    void destroy();
};