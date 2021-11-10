#include "Entry.h"

Entry::Entry()
{
	setup(Vector2f(700, 800), Vector2f(100, 100), nullptr);
}

void Entry::setup(Vector2f Position, Vector2f Size, Font* font)
{
	frameTexture.loadFromFile("name.png");
	this->frameSprite.setTexture(frameTexture);
	this->frameSprite.setPosition(Position);
	this->frameSprite.setScale(0.5f, 0.5f);

	this->font = font;
	text.setFont(*font);
	text.setPosition(720, 550);
	text.setCharacterSize(30);
	text.setFillColor(Color::Black);
	charlimit = 10;
	isActive = false;
	isSelect = false;
	haslimit = false;

}

void Entry::setFontSize(int size)
{
	text.setCharacterSize(size);
}

void Entry::setCharLimit(int limit)
{
	charlimit = limit;
}


void Entry::update(Event ev)
{
	if (ev.type != Event::TextEntered || !isActive || !isSelect || (haslimit && str.length() >= charlimit && ev.text.unicode != 8))
	{
		return;
	}
	switch (ev.text.unicode)
	{
	case 8: //ปุ่มลบ
		if (str.length() > 0)
		{
			str = str.substr(0, str.length() - 1); //ลบ
		}
		break;
	default:
		str += (char)ev.text.unicode; //พิมพ์ลงไป
		break;
	}
}

string Entry::getString()
{
	return str;
}

void Entry::render(RenderWindow& window)
{
	if (!isActive)
	{
		return;
	}
	this->window->draw(frameSprite);

	if (isSelect)
	{
		this->text.setString(str + "_");
	}
	else
	{
		this->text.setString(str);
	}
	this->window->draw(text);

}
