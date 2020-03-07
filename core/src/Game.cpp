#include "Game.h"

Game::Game()
{
	screen = std::make_pair(500, 500);
	init();
}

Game::Game(Game const& obj)
{
	*this = obj;
}

Game& Game::operator=(Game const& obj)
{
	if (this == &obj)
		return *this;
	*this = obj;
	return *this;
}

Game::~Game()
{
//	delete snake1;
//	delete snake2;
}

Game::Game(int w, int h)
{
    libHandle = NULL;
	screen = std::make_pair(w, h);
	currLib = eLibNum::NONE;
	init();
}

void Game::init()
{
	snake1 = std::make_unique<Snake>(screen.first, screen.second);
	snake2 = std::make_unique<Snake>(screen.first, screen.second + SNAKE_SIZE * 4);
	snake1->createSnake(4);
	snake2->createSnake(4);
	srand(static_cast<unsigned int>(time(NULL)));
	createStoneMap(20);
	createFruit();

	gameOver = false;
	multiPlayer = false;
	exit = false;
	speed = 100000;
	onMenu = true;
	onPause = false;
	menuPos = 0;
	enterPress = false;
	eatSound = false;
	endSound = false;
	updateState();
    std::cout << "TEST2" << std::endl;
}

void Game::updateState()
{
    state.snakeSize = SNAKE_SIZE;
    state.snake1Cord = snake1->getCord();
    state.snake2Cord = snake2->getCord();
    state.snake1Score = snake1->getScore();
    state.snake2Score = snake2->getScore();

    state.snake1Dir = snake1->getDirection();
    state.snake2Dir = snake2->getDirection();

    state.fruit = fruit;
    state.stone = stone;
    state.multiPlayer = multiPlayer;
    state.gameOver = gameOver;
    state.exit = exit;
    state.onMenu = onMenu;
    state.onPause = onPause;
    state.speed = speed;
    state.menuPos = menuPos;
    state.eatSound = eatSound;
    state.endSound = endSound;
}

void Game::input()
{
	Keys key = gui->input();
    if (key == Keys::ESC)
        exit = true;

    if (key == Keys::KEY_1)
           gui = loadGuiLib(eLibNum::SFML);
    else if (key == Keys::KEY_2)
            gui = loadGuiLib(eLibNum::SDL);
    else if (key == Keys::KEY_3)
            gui = loadGuiLib(eLibNum::NCUL);

    if (key == Keys::P)
        onPause = !onPause;

    if (onMenu)
    {
        if (key == Keys::UP && menuPos > 0)
            menuPos--;
        else if (key == Keys::DOWN && menuPos < 3)
            menuPos++;
        else if (key == Keys::ENTER)
            enterPress = true;

    }
    else if (onPause)
    {
        if (key == Keys::UP && menuPos > 0)
            menuPos--;
        else if (key == Keys::DOWN && menuPos < 2)
            menuPos++;
        else if (key == Keys::ENTER)
            enterPress = true;

    }
    else
    {
        if (key == Keys::E) {
            speed -= 10000;
            if (speed < 0)
                speed = 0;
        } else if (key == Keys::Q) {
            speed += 10000;
            if (speed > 1000000)
                speed = 100000;
        }
        else
        {
            snake1->choseDirectionP1(key);
            snake1->moveDirection();
            if (multiPlayer) {
                snake2->choseDirectionP2(key);
                snake2->moveDirection();
            }
        }
    }
}

void Game::checkCordFruit(Snake* snake)
{
	if (snake->getCord().at(0).first == fruit.first && snake->getCord().at(0).second == fruit.second)
	{
		eatSound = true;
		snake->setScore(snake->getScore() + 10);
		createFruit();
		snake->addToTail();
	}
}

void Game::checkCordMap(const int& x, const int& y)
{
	if (x >= screen.first || x < 0
		|| y >= screen.second || y < 0)
	{
		gameOver = true;
		endSound = true;
	}
}

void Game::checkCordSnake(Snake* snake)
{
	auto head = snake->getCord().at(0);
	for (auto it = snake->getCord().begin() + 1; it != snake->getCord().end(); it++)
		if (head.first == it->first && head.second == it->second)
		{
			gameOver = true;
			endSound = true;
		}
}

void Game::checkCordSnakeMulti()
{
	auto head = snake1->getCord().at(0);
	for (auto it = snake2->getCord().begin() + 1; it != snake2->getCord().end(); it++)
	{
		if (head.first == it->first
			&& head.second == it->second)
		{				
			snake2->eraseTail(it);
			break;
		}
	}	

	head = snake2->getCord().at(0);
	for (auto it = snake1->getCord().begin() + 1; it != snake1->getCord().end(); it++)
	{
		if (head.first == it->first
			&& head.second == it->second)
		{				
			snake1->eraseTail(it);
			break;
		}
	}
}

int Game::checkCordStone(const std::pair<int, int> &cord)
{
	for (auto it = stone.begin(); it != stone.end(); it++)
	{
		if (cord.first == it->first
			&& cord.second == it->second)
			return 1;
	}
	return 0;
}

void Game::logic()
{
//	std::cout << "FruitX = " << fruit.first << ": fruitY = " << fruit.second << std::endl;
//	std::cout << "Snake x = " << snake1->getCord().at(0).first << ": Snake y = " << snake1->getCord().at(0).second << std::endl;
//	std::cout << "Snake x = " << snake2->getCord().at(0).first << ": Snake y = " << snake2->getCord().at(0).second << std::endl;

	eatSound = false;
	endSound = false;
    if (onMenu && enterPress)
    {
        if (menuPos == 0)
            onMenu = false;
        else if (menuPos == 1)
        {
            multiPlayer = true;
            onMenu = false;
        }
        else if (menuPos == 2)
            exit = true;
        menuPos = 0;
        enterPress = false;
    }
    if (onPause && enterPress)
    {
        if (menuPos == 0)
            onPause = !onPause;
        else if (menuPos == 1)
            exit = true;
        menuPos = 0;
        enterPress = false;
    }
    else
    {
        checkCordFruit(snake1.get());
        checkCordMap(snake1->getCord().at(0).first, snake1->getCord().at(0).second);
        checkCordSnake(snake1.get());
        if (checkCordStone(snake1->getCord().at(0)))
		{
			gameOver = true;
			endSound = true;
		}
        if (multiPlayer) {
            checkCordFruit(snake2.get());
            checkCordMap(snake2->getCord().at(0).first, snake2->getCord().at(0).second);
            checkCordSnake(snake2.get());
            checkCordSnakeMulti();
            if (checkCordStone(snake2->getCord().at(0)))
			{
				gameOver = true;
				endSound = true;
			}

            if (snake1->getCord().at(0) == snake2->getCord().at(0))
			{
				gameOver = true;
				endSound = true;
			}
        }
    }
}

bool Game::checkCordForPlace(const int& x, const int& y)
{
	if (x > screen.first - SNAKE_SIZE || y > screen.second - SNAKE_SIZE)
		return false;
	for (auto it = stone.begin(); it != stone.end(); it++)
	{
		if (it->first == x && it->second == y)
			return false;
	}
	for (auto it = snake1->getCord().begin(); it != snake1->getCord().end(); it++)
	{
		if (it->first == x && it->second == y)
			return false;
	}
	if (multiPlayer)
	{
		for (auto it = snake2->getCord().begin(); it != snake2->getCord().end(); it++)
		{
			if (it->first == x && it->second == y)
				return false;
		}
	}
	return true;
}

void Game::createFruit()
{
	while (1)
	{
		int x = rand() % screen.first;
		int y = rand() % screen.second;

		if (x % SNAKE_SIZE != 0)
			x = x - (x % SNAKE_SIZE);
		if (y % SNAKE_SIZE != 0)
			y = y - (y % SNAKE_SIZE);
		if (checkCordForPlace(x, y))
		{
			fruit = std::make_pair(x, y);
			break;
		}
	}
}

void Game::createStoneMap(int count)
{
	int x = SNAKE_SIZE * 3;
	int y = screen.second - SNAKE_SIZE * 4;
	int i_x = 0;
	int i_y = 0;
	for (int i = 0; i < count; i++)
	{
		if (i < count / 2)
		{
			stone.push_back(std::make_pair(x + i_x, y));
			i_x += SNAKE_SIZE;
		}
		else
		{
			stone.push_back(std::make_pair(x, y - i_y));
			i_y += SNAKE_SIZE;
		}
		//std::cout << "first = " << stone.at(i).first << ": second = " << stone.at(i).second << std::endl;
	}

	x = screen.first - SNAKE_SIZE * 4;
	y = SNAKE_SIZE * 3;
	i_x = 0;
	i_y = 0;
	for (int i = 0; i < count; i++)
	{
		if (i < count / 2)
		{
			stone.push_back(std::make_pair(x - i_x, y));
			i_x += SNAKE_SIZE;
		}
		else
		{
			stone.push_back(std::make_pair(x, y + i_y));
			i_y += SNAKE_SIZE;
		}
		//std::cout << "first = " << stone.at(i).first << ": second = " << stone.at(i).second << std::endl;
	}

	x = screen.first - SNAKE_SIZE * 4;
	y = screen.second - SNAKE_SIZE * 4;
	i_x = 0;
	i_y = 0;
	for (int i = 0; i < count; i++)
	{
		if (i < count / 2)
		{
			stone.push_back(std::make_pair(x - i_x, y));
			i_x += SNAKE_SIZE;
		}
		else
		{
			stone.push_back(std::make_pair(x, y - i_y));
			i_y += SNAKE_SIZE;
		}
		//std::cout << "first = " << stone.at(i).first << ": second = " << stone.at(i).second << std::endl;
	}

	x = SNAKE_SIZE * 3;
	y = SNAKE_SIZE * 3;
	i_x = 0;
	i_y = 0;
	for (int i = 0; i < count; i++)
	{
		if (i < count / 2)
		{
			stone.push_back(std::make_pair(x + i_x, y));
			i_x += SNAKE_SIZE;
		}
		else
		{
			stone.push_back(std::make_pair(x, y + i_y));
			i_y += SNAKE_SIZE;
		}
		//std::cout << "first = " << stone.at(i).first << ": second = " << stone.at(i).second << std::endl;
	}
}

void Game::draw()
{
	gui->draw(state);
}

void Game::wait()
{
    gui->wait(speed);
}

void Game::startGame()
{
	gui = loadGuiLib(eLibNum::SFML);
	while (!exit)
    {
        //std::cout << "TEST" << std::endl;
		input();
		logic();
		updateState();
		draw();
        wait();
	}

	delete gui;
}

const Snake* Game::getSnake1() const
{
	return snake1.get();
}

const Snake* Game::getSnake2() const
{
	return snake2.get();
}

const std::pair<int, int> &Game::getFruit() const
{
	return fruit;
}

const std::pair<int, int>& Game::getScreenSize() const
{
	return screen;
}

void Game::setExit(bool e)
{
	exit = e;
}

void Game::setMultiPlayer(bool m)
{
	multiPlayer = m;
}

void Game::setGameOver(bool g)
{
	gameOver = g;
}

const bool &Game::getExit() const
{
	return exit;
}

const bool &Game::getMultiPlayer() const
{
	return multiPlayer;
}

const bool &Game::getGameOver() const
{
	return gameOver;
}

const std::vector<std::pair<int, int>> &Game::getStone() const
{
	return stone;
}

GUI* Game::loadGuiLib(eLibNum num)
{
    std::string libPath;
    if (num == currLib)
    {
        return gui;
    }
	switch (num)
    {
        case eLibNum::SFML:
            libPath = "./sfmllib.so";
            break;
        case eLibNum::NCUL:
            libPath = "./nculib.so";
            break;
        case eLibNum::SDL:
            libPath = "./sdllib.so";
            break;
        case eLibNum::NONE:
            libPath = "./sfmllib.so";
            break;
    }
    if (libHandle)
    {
        delete gui;
        if (dlclose(libHandle))
        {
            std::cerr << dlerror() << std::endl;
        }
    }
	libHandle = dlopen(libPath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
	fprintf(stderr,"dlopen() error: %s\n", dlerror());
	void *mkr = dlsym(libHandle, "maker");
    typedef GUI *(*fptr)();
    fptr func = reinterpret_cast<fptr>(reinterpret_cast<long>(mkr));
	GUI *tmp = func();
    currLib = num;
    std::cout << "TEST8" << std::endl;
    tmp->init(screen.first, screen.second, state.snakeSize);
    std::cout << "TEST9" << std::endl;
    return tmp;
}
