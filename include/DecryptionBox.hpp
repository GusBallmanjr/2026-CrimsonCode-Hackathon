#pragma once
#include "Hackathon.hpp"

class DecryptionBox : public sf::RectangleShape
{
public:
	sf::Text decryptText;
	DecryptionBox();

	void clicked();
	void notClicked();
private:
	sf::Font font;
};