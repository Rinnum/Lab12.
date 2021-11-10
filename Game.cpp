#include "Game.h"

//Private function
void Game::initVariables()
{
	this->window = nullptr;
	this->level = 4;
	this->count = 0;

}

void Game::initWindow() //ย้ายไปmain
{
	this->bgTexture.loadFromFile("character/bg.png");
	this->bgSprite.setTexture(bgTexture);
}

void Game::initPlayer()
{
	this->playerTexture.loadFromFile("character/player1.png");
	this->bulletTexture.loadFromFile("character/bullet.png");
	this->player.push_back(Player(&this->playerTexture, &this->bulletTexture));
}

void Game::initEnemies()
{
	this->enemyTexture.loadFromFile("character/enemy1.png");
	this->bossTexture.loadFromFile("character/boss.png");
	this->spawmTimerMax = 50.f;
	this->spawmTimer = this->spawmTimerMax;
	this->maxEnemies = 20;
	total = maxEnemies - count;
}

//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initEnemies();
	this->font.loadFromFile("Fonts/Cheeky_Rabbit.ttf");

	//HpText
	//this->HpText.setFont(font);
	//this->HpText.setString("0");
	//this->HpText.setCharacterSize(40);
	//this->HpText.setPosition(100, 100);
	//this->ss << score;
	//this->HpText.setString(ss.str().c_str());


	//ScoreText
	this->ScoreText.setFont(font);
	this->ScoreText.setCharacterSize(50);
	this->ScoreText.setPosition(10, 60);
	//for (size_t i = 0; i < this->player.size(); i++)
	//{
	//this->ss = "Score " + this->player[i].getPoint();
	//this->ScoreText.setString(this->player[i].getPoint().str());
	//}
	

	//Entername
	//this->entry.setup(Vector2f(650, 450), Vector2f(200, 200), &font);
	//this->entry.setFontSize(30);
	//this->entry.isActive = true;
	//this->entry.isSelect = true;
	//this->entry.haslimit = true;

	//Pause
	this->Pausegame = false;
	this->PauseText.setFont(font);
	this->PauseText.setFillColor(Color::White);
	this->PauseText.setString("Pause");
	this->PauseText.setCharacterSize(150);
	this->PauseText.setPosition(750, 200);

	//GameOver
	this->Showgameover = false;
	this->GameOverText.setFont(font);
	this->GameOverText.setFillColor(Color::White);
	this->GameOverText.setString("Game Over");
	this->GameOverText.setCharacterSize(150);
	this->GameOverText.setPosition(625, 200);

	//GameWon
	this->Showgamewon = false;
	this->GameWonText.setFont(font);
	this->GameWonText.setFillColor(Color::Blue);
	this->GameWonText.setString("Winner");
	this->GameWonText.setCharacterSize(150);
	this->GameWonText.setPosition(750, 200);
}

Game::~Game()
{

}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}


//Function


void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		if (ev.Event::type == Event::Closed)
			this->window->close();
		if (ev.Event::KeyPressed && ev.Event::key.code == Keyboard::Escape)
			this->window->close();
		if (ev.Event::KeyPressed && ev.Event::key.code == Keyboard::P)
			Pause();
		if (ev.Event::KeyPressed && ev.Event::key.code == Keyboard::Space)
			Play();
		if (Showgameover)
		{
			if (ev.type == Event::TextEntered)
			{
				//this->entry.update(ev);
			}
		}
	}
}

int Game::randomIntRange(int a, int b) {

	return rand() % (b + 1 - a) + a;
}


void Game::ResetGame()
{
	this->level = 1;
	for (size_t i = 0; i < this->player.size(); i++)
	{
		this->player[i].getPoint(0);
	}
}

void Game::Pause()
{
	player.clear();
	this->Pausegame = true;
}

void Game::Play()
{
	
	this->Pausegame = false;
}






void Game::updateEnemies(int playerIndex)
{
	if (this->spawmTimer >= this->spawmTimerMax)
	{
		if (level == 1 || level == 2)
		{
			//enemy เกิด

			this->enemies.push_back(Enemy(this->randomIntRange(200, this->window->getSize().x - 200), -200.f, &this->enemyTexture, 0));
		}
		if (level == 3)
		{
			//สุ่มเกิดสลับ boss
			int enemyrandom = rand() % 5;
			if (enemyrandom < 3) this->enemies.push_back(Enemy(this->randomIntRange(150, this->window->getSize().x - 200), -200.f, &this->enemyTexture, 0));
			else this->enemies.push_back(Enemy(this->randomIntRange(150, this->window->getSize().x - 200), -200.f, &this->bossTexture, 1));
		}
		if (level == 4)
		{
			//สุ่มเกิดสลับ boss
			int enemyrandom = rand() % 2;
			if (enemyrandom == 0) this->enemies.push_back(Enemy(this->randomIntRange(150, this->window->getSize().x - 200), -200.f, &this->enemyTexture, 0));
			if (enemyrandom == 1) this->enemies.push_back(Enemy(this->randomIntRange(150, this->window->getSize().x - 200), -200.f, &this->bossTexture, 1));
		}

		this->spawmTimer = 0.f;
	}
	else
	{
		this->spawmTimer += 0.5f;
	}
	for (int x = 0; x < this->enemies.size(); x++)
	{
		this->enemies[x].update();

		if (enemies[x].getGlobalBounds().intersects(player[playerIndex].getGlobalBounds()))
		{
			
			int damage = enemies[x].getDamage(); //damage enemy
			int pointattrack = enemies[x].getDamage(); //-point player
			player[playerIndex].takeDamage(damage, pointattrack); //ส่งค่าคืนplayer
			
			int damageEnemy = player[playerIndex].getDamageEnemy(); //รับค่าdamage ที่ตีได้
			enemies[x].takeDamageEnemy(damageEnemy); //ส่งให้enemy ลด hp

			this->enemies.erase(this->enemies.begin() + x);
			break;
		}
		//Remove enemy at bottom of screen
		if (this->enemies[x].getPos().y > this->window->getSize().y)
		{
			//GameOver();
			this->enemies.erase(this->enemies.begin() + x);
			break;
		}
	}
}

void Game::updateCombat(int playerIndex, float deltaTime)
{
	//ยิงหาย
	for (size_t k = 0; k < player[playerIndex].getBullets().size(); k++)
	{
		player[playerIndex].getBullets()[k].update(deltaTime);
		for (int j = 0; j < enemies.size(); j++)
		{
			if (player[playerIndex].getBullets()[k].getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
			{
				
				int pointkill = enemies[j].takePoint(); //+point player
				player[playerIndex].getPoint(pointkill);
				
				enemies[j].takeDamageEnemy(1);
				if (enemies[j].IsDead())
				{
					enemies.erase(enemies.begin() + j);
					count++;
				}
				player[playerIndex].getBullets().erase(player[playerIndex].getBullets().begin() + k);
				break;
			}
		}
	}

}

void Game::levelUp()
{
	this->level++;
	//this->maxEnemies = maxEnemies*level;
	for (int h = 0; h < player.size(); h++)
	{
		if (this->player[h].getHp() > 0)
		{
			player[h].setHp();

			cout << "Hp " << player[h].getHp() << endl;
		}
		else if (this->player[h].getHp() <= 0)
		{
			window->close();
		}
	}
	if (level == 2)
	{
		this->maxEnemies = 50;
		this->bgTexture.loadFromFile("character/bg1.png");
		this->bgSprite.setTexture(bgTexture);
	}
	else if (level == 3)
	{

		this->maxEnemies = 90;
		this->enemyTexture.loadFromFile("character/enemy3.png");
		this->bgTexture.loadFromFile("character/bg2.png");
		this->bgSprite.setTexture(bgTexture);
	}
	else if (level == 4)
	{
		this->maxEnemies = 140;
		this->enemyTexture.loadFromFile("character/enemy2.png");
		this->bgTexture.loadFromFile("character/bg3.png");
		this->bgSprite.setTexture(bgTexture);
	}
	else if (level == 5)
	{
		Won();
	}
}

void Game::Won()
{
	player.clear();
	this->Showgamewon = true;
	this->bgTexture.loadFromFile("character/end.png");
	this->bgSprite.setTexture(bgTexture);
}

void Game::GameOver()
{
	player.clear();
	this->Showgameover = true;
	this->bgTexture.loadFromFile("character/bg4.png");
	this->bgSprite.setTexture(bgTexture);
}

void Game::update(float deltaTime)
{
	this->pollEvents();

	if (count == this->maxEnemies)
	{
		levelUp();
	}

	for (size_t i = 0; i < this->player.size(); i++)
	{
		this->player[i].update(deltaTime);
		this->updateCombat(i, deltaTime);
		this->updateEnemies(i);

		cout << "Point " << player[i].getPoint() << endl;
		//score = player[i].getPoint();

		if (player[i].getHp() <= 0)
		{
			GameOver();
		}
	}


}




void Game::render()
{
	/*
	   @return void

		-clear old frame
		-Render new object
		-display frame in Wiondow
		Render the game objects.
	*/

	this->window->clear();

	//Draw Game Objects
	this->window->draw(this->bgSprite);

	window->draw(this->ScoreText);

	window->draw(this->HpText);

	for (size_t i = 0; i < this->player.size(); i++)
	{
		this->player[i].render(*this->window);
	}
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].render(*this->window);
	}

	for (size_t i = 0; i < this->enemies.size(); i++) {
		this->enemies.at(i).render(this->window);
	}

	if (Pausegame)
	{
		window->draw(this->PauseText);
	}

	if (Showgameover)
	{
		window->draw(this->GameOverText);
		//this->entry.render(*window);
	}

	if (Showgamewon)
	{
		window->draw(this->GameWonText);
	}

	this->window->display();
}


