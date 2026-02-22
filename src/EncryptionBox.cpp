#include "EncryptionBox.hpp"

EncryptionBox::EncryptionBox() : font("C:/Windows/Fonts/arial.ttf"), encryptText(font, "Encryption", 26)
{
	this->setSize({ 200.f, 60.f });
    this->setPosition({ 280.f, 240.f });
    this->setFillColor(sf::Color(60, 60, 60));
    this->setOutlineThickness(4.f);
    this->setOutlineColor(sf::Color(120, 120, 120));
    encryptText.setFillColor(sf::Color::White);
    encryptText.setPosition({ this->getPosition().x + 30.f, this->getPosition().y + 15.f });
}

void EncryptionBox::clicked()
{
    this->setFillColor(sf::Color(0, 120, 255));
    this->setOutlineColor(sf::Color(255, 255, 255));
}

void EncryptionBox::notClicked()
{
    this->setFillColor(sf::Color(60, 60, 60));
    this->setOutlineColor(sf::Color(120, 120, 120));
}
