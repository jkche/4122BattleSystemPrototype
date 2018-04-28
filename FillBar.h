#include <SFML/Graphics.hpp>

class FillBar {
public:
	int x;
	int y;
	int w;
	int h;
	float amount;
	sf::Color fgColor;
	sf::Color bgColor;
	int alignment; // 0 for left, 1 for right

	sf::RectangleShape background;
	sf::RectangleShape foreground;

	FillBar(int posX, int posY, int width, int height, sf::Color foregroundColor, sf::Color backgroundColor, int leftOrRight) {
		x = posX;
		y = posY;
		amount = 1.0f;
		alignment = leftOrRight;
		fgColor = foregroundColor;
		bgColor = backgroundColor;
		foreground = new RectangleShape(sf::Vector2(w, h));
		background = new RectangleShape(sf::Vector2(w, h));
		foreground.setPosition(x, y);
		background.setPosition(x, y);
		foreground.setFillColor(foregroundColor);
		background.setFillColor(backgroundColor);

	}

	FillBar(int x, int y, int width, int height, sf::Color foregroundColor, sf::Color backgroundColor) {
		FillBar(x, y, width, height, foregroundColor, backgroundColor, 0);
	}
	void update() {
		background.setPosition(x, y);
		if (alignment == 0) {
			foreground.setPosition(x, y);
		}
		foreground.setScale(amount, 1.0f);
	}
};