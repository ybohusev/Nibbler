#include <iostream>
#include <GUI.h>
#include "SDLLIB.h"

SDLLIB::SDLLIB()
{
    std::cout << "CONSTRUCT SDL" << std::endl;
	screenSize.first = 800;
	screenSize.second = 800;
}

SDLLIB::SDLLIB(SDLLIB const& obj)
{
	*this = obj;
}

SDLLIB& SDLLIB::operator=(SDLLIB const& obj)
{
	if (this == &obj)
		return *this;
	*this = obj;
	return *this;
}

void SDLLIB::init(int w, int h, int snakeSize)
{
    screenSize.first = w;
    screenSize.second = h;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;

    win = SDL_CreateWindow("Snake SDL", 100, 100, screenSize.first, screenSize.second, SDL_WINDOW_SHOWN);
    if (win == nullptr){
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return;
    }
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return;
    }

    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    m_BackgroundTexture = loadTexture("./resources/sdl/background.jpg");
    m_SnakeTexture = loadTexture("./resources/sdl/body1.jpg");
    m_Snake2Texture = loadTexture("./resources/sdl/body.jpg");
    m_SnakeHeadTextureLeft = loadTexture("./resources/sdl/head_left.png");
    m_SnakeHeadTextureRight = loadTexture("./resources/sdl/head_right.png");
    m_SnakeHeadTextureUp = loadTexture("./resources/sdl/head_up.png");
    m_SnakeHeadTextureDown = loadTexture("./resources/sdl/head_down.png");

//	if (!m_GameOverTexture.loadFromFile("./resources/sfml/background.jpg"))
//		std::cerr << "Error loading background.jpg" << std::endl;
//	m_GameOverSprite.setTexture(m_GameOverTexture);
//
//	if (!m_PauseTexture.loadFromFile("./resources/sfml/background.jpg"))
//		std::cerr << "Error loading background.jpg" << std::endl;
//	m_PauseSprite.setTexture(m_PauseTexture);
//
//	if (!m_MenuTexture.loadFromFile("./resources/sfml/background.jpg"))
//		std::cerr << "Error loading background.jpg" << std::endl;
//	m_MenuSprite.setTexture(m_MenuTexture);
//
//	if (!Font.loadFromFile("./resources/sfml/Pacifico.ttf"))
//		std::cerr << "Error loading Pacifico.ttf" << std::endl;
//

    m_StoneTexture = loadTexture("./resources/sfml/stone.png");
    m_FruitTexture = loadTexture("./resources/sdl/apple.png");

//	if (!eatBuffer.loadFromFile("sound.wav"))
//		std::cerr << "Error loading sound" << std::endl;
//	eatSound.setBuffer(eatBuffer);
//
//	if (!crashBuffer.loadFromFile("sound.wav"))
//		std::cerr << "Error loading sound" << std::endl;
//	eatSound.setBuffer(crashBuffer);
}

SDL_Texture *SDLLIB::loadTexture(std::string path)
{
    SDL_Texture* tmp = NULL;
    tmp = IMG_LoadTexture(ren, path.c_str());
    if (tmp == NULL){
        std::cerr << "IMG_LoadTexture Error: " << SDL_GetError() << std::endl;
        return NULL;
    }
    textureList.push_back(tmp);
    return tmp;
}

void SDLLIB::drawGameOver(State &state)
{
//	sf::Text GameOver;
//	sf::Text PressEsc;
//	sf::Text Score1;
//	sf::Text Score2;
//	sf::Text Winner;
//
//	GameOver.setFont(Font);
//	GameOver.setCharacterSize(60);
//	GameOver.setString("Game Over");
//	position.x = screenSize.first / 2 - 40 * 3;
//	position.y = screenSize.second / 2 - 120;
//	GameOver.setPosition(static_cast<sf::Vector2f>(position));
//
//	position.x = screenSize.first / 2 - 40 * 3;
//	position.y = screenSize.second / 2 - 120 + 120;
//	Score1.setFont(Font);
//	Score1.setCharacterSize(40);
//	Score1.setString("Score 1: " + std::to_string(state.snake1Score));
//	Score1.setPosition(static_cast<sf::Vector2f>(position));
//
//	position.x = screenSize.first / 2 - 40 * 3;
//	position.y = screenSize.second / 2 - 120 + 160;
//	Score2.setFont(Font);
//	Score2.setCharacterSize(40);
//	Score2.setString("Score 2: " + std::to_string(state.snake2Score));
//	Score2.setPosition(static_cast<sf::Vector2f>(position));
//
//	position.x = screenSize.first / 2 - 40 * 3;
//	position.y = screenSize.second / 2 - 120 + 240;
//	PressEsc.setFont(Font);
//	PressEsc.setCharacterSize(40);
//	PressEsc.setString("Press ESC to exit");
//	PressEsc.setPosition(static_cast<sf::Vector2f>(position));
//
//    m_Window.clear();
//
//    m_Window.draw(m_GameOverSprite);
//    GameOver.setFillColor(sf::Color(255, 0, 0, 255));
//    m_Window.draw(GameOver);
//    m_Window.draw(Score1);
//    if (state.multiPlayer)
//    {
//        m_Window.draw(Score2);
//        //m_Window.draw(Winner);
//    }
//    m_Window.draw(PressEsc);
//    m_Window.display();
}

void SDLLIB::drawPause(State &state)
{
//	sf::Text Play;
//	sf::Text Multiplayer;
//	sf::Text Exit;
//	sf::Text Continue;
//
//	position.x = screenSize.first / 2 - 40 * 3;
//	position.y = screenSize.second / 2 - 120;
//	Continue.setFont(Font);
//	Continue.setCharacterSize(40);
//	Continue.setString("Continue");
//	Continue.setPosition(static_cast<sf::Vector2f>(position));
//
//	position.x = screenSize.first / 2 - 40 * 3;
//	position.y = screenSize.second / 2 -120 + 60;
//	Exit.setFont(Font);
//	Exit.setCharacterSize(40);
//	Exit.setString("Exit");
//	Exit.setPosition(static_cast<sf::Vector2f>(position));
//
//    if (state.menuPos == 0)
//    {
//        Continue.setFillColor(sf::Color(255, 0, 0, 255));
//        Exit.setFillColor(sf::Color(255, 255, 255, 255));
//    }
//    else
//    {
//        Continue.setFillColor(sf::Color(255, 255, 255, 255));
//        Exit.setFillColor(sf::Color(255, 0, 0, 255));
//    }
//    m_Window.clear();
//
//    m_Window.draw(m_PauseSprite);
//    m_Window.draw(Continue);
//    m_Window.draw(Exit);
//    m_Window.display();
}

void SDLLIB::drawMenu(State &state)
{
//	sf::Text Play;
//	sf::Text Multiplayer;
//	sf::Text Exit;
//	sf::Text Continue;
//
//	position.x = screenSize.first / 2 - 40 * 3;
//	position.y = screenSize.second / 2 - 120;
//	Play.setFont(Font);
//	Play.setCharacterSize(40);
//	Play.setString("Play");
//	Play.setPosition(static_cast<sf::Vector2f>(position));
//
//	position.x = screenSize.first / 2 - 40 * 3;
//	position.y = screenSize.second / 2 - 120 + 60;
//	Multiplayer.setFont(Font);
//	Multiplayer.setCharacterSize(40);
//	Multiplayer.setString("Multiplayer");
//	Multiplayer.setPosition(static_cast<sf::Vector2f>(position));
//
//	position.x = screenSize.first / 2 - 40 * 3;
//	position.y = screenSize.second / 2 - 120 + 120;
//	Exit.setFont(Font);
//	Exit.setCharacterSize(40);
//	Exit.setString("Exit");
//	Exit.setPosition(static_cast<sf::Vector2f>(position));
//
//    if (state.menuPos == 0)
//    {
//        Play.setFillColor(sf::Color(255, 0, 0, 255));
//        Multiplayer.setFillColor(sf::Color(255, 255, 255, 255));
//        Exit.setFillColor(sf::Color(255, 255, 255, 255));
//    }
//    else if (state.menuPos == 1)
//    {
//        Play.setFillColor(sf::Color(255, 255, 255, 255));
//        Multiplayer.setFillColor(sf::Color(255, 0, 0, 255));
//        Exit.setFillColor(sf::Color(255, 255, 255, 255));
//    }
//    else
//    {
//        Play.setFillColor(sf::Color(255, 255, 255, 255));
//        Multiplayer.setFillColor(sf::Color(255, 255, 255, 255));
//        Exit.setFillColor(sf::Color(255, 0, 0, 255));
//    }
//
//    m_Window.clear();
//
//    m_Window.draw(m_MenuSprite);
//    m_Window.draw(Play);
//    m_Window.draw(Multiplayer);
//    m_Window.draw(Exit);
//    m_Window.display();
}

SDL_Texture *SDLLIB::drawHead(eDirection &dir)
{
	switch (dir)
	{
	case eDirection::LEFT:
		return m_SnakeHeadTextureLeft;
	case eDirection::RIGHT:
        return m_SnakeHeadTextureRight;
	case eDirection::UP:
        return m_SnakeHeadTextureUp;
	case eDirection::DOWN:
        return m_SnakeHeadTextureDown;
	default:
        return m_SnakeHeadTextureLeft;
	}
}

void SDLLIB::drawSnake(const std::vector<std::pair<int,int>> &snake, eDirection dir, int player, int snakeSize)
{
    SDL_Rect tmp = {snake.at(0).first, snake.at(0).second, snakeSize, snakeSize};
    SDL_RenderCopy(ren, drawHead(dir), NULL, &tmp);

    for (auto it = snake.begin() + 1; it != snake.end(); it++)
    {
        tmp.x = it->first;
        tmp.y = it->second;
       if (player == 1)
           SDL_RenderCopy(ren, m_SnakeTexture, NULL, &tmp);
       else
           SDL_RenderCopy(ren, m_Snake2Texture, NULL, &tmp);
    }
}

void SDLLIB::drawFruit(const std::pair<int, int> &fruit)
{
    SDL_Rect tmp = {fruit.first, fruit.second, 25, 25};
    SDL_RenderCopy(ren, m_FruitTexture, NULL, &tmp);
}

void SDLLIB::drawStone(const std::vector<std::pair<int, int>> &stone)
{
    SDL_Rect tmp = {0, 0, 25, 25};
	for (auto it = stone.begin(); it != stone.end(); it++)
	{
	    tmp.x = it->first;
	    tmp.y = it->second;
        SDL_RenderCopy(ren, m_StoneTexture, NULL, &tmp);
	}
}

void SDLLIB::draw(State &state)
{
   // std::cout << "draw" << std::endl;
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, m_BackgroundTexture, NULL, NULL);
	if (state.onMenu)
		drawMenu(state);
	else if (state.onPause)
		drawPause(state);
	else if (state.gameOver)
		drawGameOver(state);
	else
	{
		drawSnake(state.snake1Cord, state.snake1Dir, 1, state.snakeSize);
		if(state.multiPlayer)
			drawSnake(state.snake2Cord, state.snake2Dir, 2, state.snakeSize);
		drawFruit(state.fruit);
		drawStone(state.stone);
	}
    SDL_RenderPresent(ren);
}

Keys SDLLIB::input()
{
    Keys key = Keys::NONE;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            key =  Keys::ESC;
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_UP)
                key = Keys::UP;
            else if (event.key.keysym.sym == SDLK_DOWN)
                key = Keys::DOWN;
            else if (event.key.keysym.sym == SDLK_LEFT)
                key = Keys::LEFT;
            else if (event.key.keysym.sym == SDLK_RIGHT)
                key = Keys::RIGHT;
            else if (event.key.keysym.sym == SDLK_RETURN)
                key = Keys::ENTER;
            else if (event.key.keysym.sym == SDLK_w)
                key = Keys::W;
            else if (event.key.keysym.sym == SDLK_s)
                key = Keys::S;
            else if (event.key.keysym.sym == SDLK_a)
                key = Keys::A;
            else if (event.key.keysym.sym == SDLK_d)
                key = Keys::D;
            else if (event.key.keysym.sym == SDLK_p)
                key = Keys::P;
            else if (event.key.keysym.sym == SDLK_q)
                key = Keys::Q;
            else if (event.key.keysym.sym == SDLK_e)
                key = Keys::E;
            else if (event.key.keysym.sym == SDLK_1)
                key = Keys::KEY_1;
            else if (event.key.keysym.sym == SDLK_2)
                key = Keys::KEY_2;
            else if (event.key.keysym.sym == SDLK_3)
                key = Keys::KEY_3;
        }
    }
	return key;
}

void SDLLIB::wait(int speed)
{
    SDL_Delay(speed/1000);
    //std::cout << " wait" << speed << std::endl;
//    sf::Time wait = sf::microseconds(speed);
//    sf::sleep(wait);
}

SDLLIB::~SDLLIB()
{
    std::cout << "Call destructor SDL" << std::endl;
    for (auto it = textureList.begin() + 1; it != textureList.end(); it++)
        SDL_DestroyTexture(*it);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

SDLLIB *maker() {
    return new SDLLIB();
}
