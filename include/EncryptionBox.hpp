#pragma once
#include "Hackathon.hpp"

class EncryptionBox : public sf::RectangleShape
{
public:
	sf::Text encryptText;
	EncryptionBox();

	void clicked();
	void notClicked();
private:
    sf::Font font;
};