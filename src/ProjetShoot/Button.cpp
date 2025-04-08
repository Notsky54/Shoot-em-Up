#include "Button.h"

Button::Button(const sf::Vector2f& size, const sf::Font& font, const std::string& text, const std::function<void()>& onClick) : onClick(onClick)
{
    buttonShape.setSize(size);
    buttonShape.setFillColor(sf::Color::Blue);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(buttonShape.getPosition().x + (size.x - buttonText.getGlobalBounds().width) / 2,
        buttonShape.getPosition().y + (size.y - buttonText.getGlobalBounds().height) / 2);
}

void Button::setPosition(const sf::Vector2f& position)
{
    buttonShape.setPosition(position);
    buttonText.setPosition(position.x + (buttonShape.getSize().x - buttonText.getGlobalBounds().width) / 2,
        position.y + (buttonShape.getSize().y - buttonText.getGlobalBounds().height) / 2);
}

void Button::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition())))
        {
            onClick();
        }
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(buttonShape, states);
    target.draw(buttonText, states);
}
