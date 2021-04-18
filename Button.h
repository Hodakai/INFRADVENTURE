#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Button
{
public:

	Button(string txt, Vector2f size, int charSize, Color BackColor, Color textColor) {
		this->text.setString(txt);
		this->text.setFillColor(textColor);
		this->text.setCharacterSize(charSize);
		

		this->button.setSize(size);
		this->button.setFillColor(BackColor);
	}
	
	void setFont(Font &font) {
		this->text.setFont(font);
	}

	void setBackColor(Color color) {
		this->button.setFillColor(color);
	}
	
	void setTextColor(Color color) {
		this->text.setFillColor(color);
	}

	void setPosition(Vector2f pos) {
		this->button.setPosition(pos);

		float x = (pos.x + this->button.getLocalBounds().width / 4) - (this->text.getLocalBounds().width / 4 );
		float y = (pos.y + this->button.getLocalBounds().height / 4) - (this->text.getLocalBounds().height / 4);
		this->text.setPosition({ x, y });
	}

	void Draw(RenderWindow& window) {
		window.draw(button);
		window.draw(text);
	}

	bool isMouseHover(RenderWindow &window) {
		int mouseX = Mouse::getPosition(window).x;
		int mouseY = Mouse::getPosition(window).y;

		float btnPosX = this->button.getPosition().x;
		float btnPosY = this->button.getPosition().y;

		float btnxPosWidth = this->button.getPosition().x + this->button.getLocalBounds().width;
		float btnxPosHeight = this->button.getPosition().y + this->button.getLocalBounds().height;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnxPosHeight && mouseY > btnPosY)
		{
			return true;
		}
		return false;
	}
private:
	RectangleShape button;
	Text text;
	Font arial;
	
};

