#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
    : velocity(direction * speed), direction(direction), speed(speed)
{
    shape.setSize(sf::Vector2f(5.f, 5.f));
    shape.setFillColor(sf::Color::Yellow); 
    shape.setPosition(position); 
}

void Bullet::Update(float deltaTime)
{
    shape.move(direction * speed * deltaTime);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);
}

bool Bullet::isOffScreen() const
{
    return (position.y < 0 || position.y > 1080 || position.x < 0 || position.x > 1920);
}

void Bullet::destroy()
{

}

