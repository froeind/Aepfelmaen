
#include "Button.h"

myA::Button::Button() {}

myA::Button::Button(sf::RenderWindow& window, std::string name, sf::Font& font, float x, float y, float w, float h, const unsigned char r, const unsigned char g, const unsigned char b) : window_(&window), name_(name) {
    // Button-Optik
    button_.setPosition(x, y); 
	button_.setSize(sf::Vector2f(w, h));
    button_.setFillColor(sf::Color(r, g, b));
    // Button-Text
    text_.setFont(font);
    text_.setString(name);
    text_.setCharacterSize(14);
    text_.setFillColor(sf::Color::Black);
    // Zentrieren
    textRect_ = text_.getLocalBounds();
    text_.setOrigin(textRect_.left + textRect_.width / 2.0f, textRect_.top + textRect_.height / 2.0f);
    text_.setPosition(button_.getPosition().x + button_.getSize().x / 2.0f, button_.getPosition().y + button_.getSize().y / 2.0f);
    /*
    */
}

myA::Button::~Button() {}
