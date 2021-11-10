#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;

class Entry
{
private:
	RenderWindow* window;

	RectangleShape frame;
	Texture frameTexture;
	Sprite frameSprite;

	Text text;
	Font* font;
	string str;
	size_t charlimit;


public:
	bool isActive; //การแสดงผลบนจอ
	bool isSelect; //โดนเลือก
	bool haslimit; //เช็คจำกัดตัวอักษร

	Entry();

	void setup(Vector2f Position, Vector2f Size, Font* font); //set ตัวแปร
	void setFontSize(int size);
	void setCharLimit(int limit);
	void update(Event ev);
	string getString();
	void render(RenderWindow& window);

};

