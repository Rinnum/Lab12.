#pragma once
#include <SFML/Graphics.hpp>
#include"Scene.h"
#define Max_menu 5

using namespace sf;
using namespace std;
                                      
class Menu : public Scene 
{
public:
	Menu(float width, float height);
	void update(float deltaTime);
	void render();
	void moveUp();
	void moveDown();
	inline int MenuPressed()
	{
		return mainMenuSelected;
	}
	~Menu();
	inline void setWindow(RenderWindow* window) { this->window = window; }
	
	void pollEvent();
	void select();

private:
	RenderWindow* window;
	int mainMenuSelected;
	Font font;
	Text menu[Max_menu];

	RectangleShape bg;
	Texture bgTexture;
	Sprite bgSprite;
	Event ev;
};

