#include "Password.hpp"

Password::Password() : font("C:/Windows/Fonts/arial.ttf"), passwordLabel(font, passwordText, 26)
{
    passwordActive = false;
    passwordText = "Enter Password";
    this->setSize({ 350.f, 60.f });
    this->setPosition({ 325.f, 150.f });
    this->setFillColor(sf::Color(40, 40, 40));
    this->setOutlineThickness(4.f);
    this->setOutlineColor(sf::Color(150, 150, 150));

    passwordLabel.setFillColor(sf::Color(200, 200, 200));
    passwordLabel.setPosition({ 340.f, 168.f });
}

bool Password::getPasswordActive() const
{
    return passwordActive;
}

std::string Password::getPasswordText() const
{
    return passwordText;
}

void Password::setPasswordActive(bool const newActive)
{
    passwordActive = newActive;
}

void Password::setPasswordText(std::string const newText)
{
    passwordText = newText;
}

void Password::clicked()
{
    char current = '\0';
    this->setOutlineColor(sf::Color(180, 180, 255));

    // Password Typing
    while (passwordActive && current != '\n')
    {
        std::cin >> current;
        passwordText += current;

        if (current == '\n')
        {
            passwordActive = false;
            passwordText.pop_back(); // remove newline
        }
    }

    passwordActive = false;
    this->setOutlineColor(sf::Color(150, 150, 150));

    if (passwordText.empty())
    {
        passwordLabel.setFillColor(sf::Color(200, 200, 200));
        passwordText = "Enter Password";
    }
}
