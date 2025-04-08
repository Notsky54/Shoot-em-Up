#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button 
{
private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    std::function<void()> onClick;

public:
    Button(const sf::Vector2f& size, const sf::Font& font, const std::string& text, const std::function<void()>& onClick);
    void setPosition(const sf::Vector2f& position);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


