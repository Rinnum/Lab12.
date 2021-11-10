#pragma once
#include<iostream>
#include<vector>
#include <sstream>
#include"Player.h"
#include"Enemy.h"
#include "Bullet.h"
#include"Scene.h"
//#include"Entry.h"
#include<ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;
/*
	Class that acts the game engine
*/

class Game : public Scene
{
private:
	//Window
	RenderWindow* window;
	Texture bgTexture;
	Sprite bgSprite;
	Event ev;


	//Entry entry;
	Font font;

	//Hp
	Text HpText;

	stringstream ss;
	int score = 0;
	Text ScoreText;
	

	bool Showgameover;
	Text GameOverText;

	bool Showgamewon;
	Text GameWonText;

	bool Pausegame;
	Text PauseText;

	int total;


	//Bullet
	vector<Bullet> bullets;

	//Player
	Texture playerTexture;
	vector<Player> player;

	//Enemies
	float spawmTimer;
	float spawmTimerMax;
	int maxEnemies;


	vector<Enemy> enemies;
	Texture enemyTexture; 
	Texture bossTexture;
	Texture bulletTexture;

	

	int level;
	int count;



	//Private function
	void initVariables();
	void initWindow();

	void initPlayer();
	void initEnemies();

public:
	//Constructor/Destructors
	Game();
	virtual ~Game();
	inline void setWindow(RenderWindow* window) { this->window = window; }

	//Accessors
	const bool running() const;


	//Function 

	int randomIntRange(int a, int b);
	void ResetGame();
	void Pause();
	void Play();
	void GameOver();
	void Won();
	void pollEvents();
	void updateEnemies(int playerIndex);
	void updateCombat(int playerIndex, float deltaTime);
	void levelUp();
	void update(float deltaTime);
	void render();
};
