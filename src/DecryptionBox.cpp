#include "DecryptionBox.hpp"

DecryptionBox::DecryptionBox() : font("C:/Windows/Fonts/arial.ttf"), decryptText(font, "Decryption", 26)
{
    this->setSize({ 200.f, 60.f });
    this->setPosition({ 520.f, 240.f });
    this->setFillColor(sf::Color(60, 60, 60));
    this->setOutlineThickness(4.f);
    this->setOutlineColor(sf::Color(120, 120, 120)); // sf::Color(255, 255, 255)
    decryptText.setFillColor(sf::Color::White);
    decryptText.setPosition({ this->getPosition().x + 30.f, this->getPosition().y + 15.f });
}

void DecryptionBox::clicked()
{
    this->setFillColor(sf::Color(0, 120, 255));
    this->setOutlineColor(sf::Color(255, 255, 255));
}

void DecryptionBox::notClicked()
{
    this->setFillColor(sf::Color(60, 60, 60));
    this->setOutlineColor(sf::Color(120, 120, 120));
}
