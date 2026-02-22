#pragma once
#include "Hackathon.hpp"
#include "HashFunction.hpp"


class Password : public sf::RectangleShape
{
public:
	sf::Text passwordLabel;
    Password();

	bool getPasswordActive() const;
	std::string getPasswordText() const;

	void setPasswordActive(bool const active);
	void setPasswordText(std::string const newText);

	void clicked();

private:
	bool passwordActive = false;
	std::string passwordText = "";
	sf::Font font;
};