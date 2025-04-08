#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Entity : public sf::Drawable, public sf::Transformable
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;
public:
    Entity();
    Entity(const std::string& textureFile);
    virtual ~Entity();
    sf::Sprite& getSprite();
    const sf::Sprite& getSprite() const { return sprite; }
    sf::Vector2f getPosition() const;
    virtual void Update(float deltaTime);
    bool isOffScreen() const;
    sf::FloatRect IdBox() const;
};

