#include "SFML.h"
#include <iostream>

SFML::SFML()
{
    std::cout << "CONSTRUCT SFML" << std::endl;
	screenSize.first = 800;
	screenSize.second = 800;
}

SFML::SFML(SFML const& obj)
{
	*this = obj;
}

SFML& SFML::operator=(SFML const& obj)
{
	if (this == &obj)
		return *this;
	*this = obj;
	return *this;
}

void SFML::init(int w, int h, int snakeSize)
{
    screenSize.first = w;
    screenSize.second = h;

	m_Window.create(sf::VideoMode(screenSize.first, screenSize.second), "Snake SFML", sf::Style::Titlebar|sf::Style::Close);
	position.x = 100;
	position.y = 100;
	m_Window.setPosition(position);
	m_Window.setFramerateLimit(60);

	if (!m_BackgroundTexture.loadFromFile("./resources/sfml/background.jpg"))
		std::cerr << "Error loading background.jpg" << std::endl;
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	if (!m_GameOverTexture.loadFromFile("./resources/sfml/background.jpg"))
		std::cerr << "Error loading background.jpg" << std::endl;
	m_GameOverSprite.setTexture(m_GameOverTexture);

	if (!m_PauseTexture.loadFromFile("./resources/sfml/background.jpg"))
		std::cerr << "Error loading background.jpg" << std::endl;
	m_PauseSprite.setTexture(m_PauseTexture);

	if (!m_MenuTexture.loadFromFile("./resources/sfml/background.jpg"))
		std::cerr << "Error loading background.jpg" << std::endl;
	m_MenuSprite.setTexture(m_MenuTexture);

	if (!Font.loadFromFile("./resources/sfml/SEASRN__.TTF"))
		std::cerr << "Error loading Pacifico.ttf" << std::endl;

	if (!m_SnakeTexture.loadFromFile("./resources/sfml/body1.jpg", sf::IntRect(0, 0, snakeSize, snakeSize)))
		std::cerr << "Error loading snake.jpg" << std::endl;
	m_SnakeSprite.setTexture(m_SnakeTexture);

	if (!m_SnakeHeadTexture.loadFromFile("./resources/sfml/head_left.png", sf::IntRect(0, 0, snakeSize, snakeSize)))
		std::cerr << "Error loading bar.jpg" << std::endl;
	m_SnakeHeadSprite.setTexture(m_SnakeHeadTexture);

	if (!m_Snake2Texture.loadFromFile("./resources/sfml/body.bmp", sf::IntRect(0, 0, snakeSize, snakeSize)))
		std::cerr << "Error loading snake.jpg" << std::endl;
	m_Snake2Sprite.setTexture(m_Snake2Texture);

	if (!m_Snake2HeadTexture.loadFromFile("./resources/sfml/head_left.png", sf::IntRect(0, 0, snakeSize, snakeSize)))
		std::cerr << "Error loading bar.jpg" << std::endl;
	m_Snake2HeadSprite.setTexture(m_Snake2HeadTexture);

	if (!m_StoneTexture.loadFromFile("./resources/sfml/stone.png", sf::IntRect(0, 0, snakeSize, snakeSize)))
		std::cerr << "Error loading stone.jpg" << std::endl;
	m_StoneSprite.setTexture(m_StoneTexture);

	if (!m_FruitTexture.loadFromFile("./resources/sfml/apple.png", sf::IntRect(0, 0, snakeSize, snakeSize)))
		std::cerr << "Error loading donut.png" << std::endl;
	m_FruitSprite.setTexture(m_FruitTexture);

	if (!eatBuffer.loadFromFile("./resources/sfml/apple.wav"))
		std::cerr << "Error loading apple.wav" << std::endl;
	eatSound.setBuffer(eatBuffer);

	if (!crashBuffer.loadFromFile("./resources/sfml/crash.wav"))
		std::cerr << "Error loading crash.wav" << std::endl;
	crashSound.setBuffer(crashBuffer);
}

void SFML::drawGameOver(State &state)
{
	sf::Text GameOver;
	sf::Text PressEsc;
	sf::Text Score1;
	sf::Text Score2;
	sf::Text Winner;

	GameOver.setFont(Font);
	GameOver.setCharacterSize(60);
	GameOver.setString("Game Over");
	position.x = screenSize.first / 2 - 40 * 3;
	position.y = screenSize.second / 2 - 120;
	GameOver.setPosition(static_cast<sf::Vector2f>(position));

	position.x = screenSize.first / 2 - 40 * 3;
	position.y = screenSize.second / 2 - 120 + 120;
	Score1.setFont(Font);
	Score1.setCharacterSize(40);
	Score1.setString("Score 1: " + std::to_string(state.snake1Score));
	Score1.setPosition(static_cast<sf::Vector2f>(position));

	position.x = screenSize.first / 2 - 40 * 3;
	position.y = screenSize.second / 2 - 120 + 160;
	Score2.setFont(Font);
	Score2.setCharacterSize(40);
	Score2.setString("Score 2: " + std::to_string(state.snake2Score));
	Score2.setPosition(static_cast<sf::Vector2f>(position));

	position.x = screenSize.first / 2 - 40 * 3;
	position.y = screenSize.second / 2 - 120 + 240;
	PressEsc.setFont(Font);
	PressEsc.setCharacterSize(40);
	PressEsc.setString("Press ESC to exit");
	PressEsc.setPosition(static_cast<sf::Vector2f>(position));

    m_Window.clear();

    m_Window.draw(m_GameOverSprite);
    GameOver.setFillColor(sf::Color(255, 0, 0, 255));
    m_Window.draw(GameOver);
    m_Window.draw(Score1);
    if (state.multiPlayer)
    {
        m_Window.draw(Score2);
        //m_Window.draw(Winner);
    }
    m_Window.draw(PressEsc);
    m_Window.display();
}

void SFML::drawPause(State &state)
{
	sf::Text Play;
	sf::Text Multiplayer;
	sf::Text Exit;
	sf::Text Continue;

	position.x = screenSize.first / 2 - 40 * 3;
	position.y = screenSize.second / 2 - 120;
	Continue.setFont(Font);
	Continue.setCharacterSize(40);
	Continue.setString("Continue");
	Continue.setPosition(static_cast<sf::Vector2f>(position));

	position.x = screenSize.first / 2 - 40 * 3;
	position.y = screenSize.second / 2 -120 + 60;
	Exit.setFont(Font);
	Exit.setCharacterSize(40);
	Exit.setString("Exit");
	Exit.setPosition(static_cast<sf::Vector2f>(position));

    if (state.menuPos == 0)
    {
        Continue.setFillColor(sf::Color(255, 0, 0, 255));
        Exit.setFillColor(sf::Color(255, 255, 255, 255));
    }
    else
    {
        Continue.setFillColor(sf::Color(255, 255, 255, 255));
        Exit.setFillColor(sf::Color(255, 0, 0, 255));
    }
    m_Window.clear();

    m_Window.draw(m_PauseSprite);
    m_Window.draw(Continue);
    m_Window.draw(Exit);
    m_Window.display();
}

void SFML::drawMenu(State &state)
{
	sf::Text Play;
	sf::Text Multiplayer;
	sf::Text Exit;
	sf::Text Continue;

	position.x = screenSize.first / 2 - 40 * 3;
	position.y = screenSize.second / 2 - 120;
	Play.setFont(Font);
	Play.setCharacterSize(40);
	Play.setString("Play");
	Play.setPosition(static_cast<sf::Vector2f>(position));

	position.x = screenSize.first / 2 - 40 * 3;
	position.y = screenSize.second / 2 - 120 + 60;
	Multiplayer.setFont(Font);
	Multiplayer.setCharacterSize(40);
	Multiplayer.setString("Multiplayer");
	Multiplayer.setPosition(static_cast<sf::Vector2f>(position));

	position.x = screenSize.first / 2 - 40 * 3;
	position.y = screenSize.second / 2 - 120 + 120;
	Exit.setFont(Font);
	Exit.setCharacterSize(40);
	Exit.setString("Exit");
	Exit.setPosition(static_cast<sf::Vector2f>(position));

    if (state.menuPos == 0)
    {
        Play.setFillColor(sf::Color(255, 0, 0, 255));
        Multiplayer.setFillColor(sf::Color(255, 255, 255, 255));
        Exit.setFillColor(sf::Color(255, 255, 255, 255));
    }
    else if (state.menuPos == 1)
    {
        Play.setFillColor(sf::Color(255, 255, 255, 255));
        Multiplayer.setFillColor(sf::Color(255, 0, 0, 255));
        Exit.setFillColor(sf::Color(255, 255, 255, 255));
    }
    else
    {
        Play.setFillColor(sf::Color(255, 255, 255, 255));
        Multiplayer.setFillColor(sf::Color(255, 255, 255, 255));
        Exit.setFillColor(sf::Color(255, 0, 0, 255));
    }

    m_Window.clear();

    m_Window.draw(m_MenuSprite);
    m_Window.draw(Play);
    m_Window.draw(Multiplayer);
    m_Window.draw(Exit);
    m_Window.display();
}

void SFML::drawHead(eDirection &dir, sf::Texture &texture, sf::Sprite &sprite, int snakeSize)
{
	switch (dir)
	{
	case eDirection::LEFT:
		if (!texture.loadFromFile("./resources/sfml/head_left.png", sf::IntRect(0, 0, snakeSize, snakeSize)))
			std::cerr << "Error loading image" << std::endl;
		break;
	case eDirection::RIGHT:
		if (!texture.loadFromFile("./resources/sfml/head_right.png", sf::IntRect(0, 0, snakeSize, snakeSize)))
			std::cerr << "Error loading image" << std::endl;
		break;
	case eDirection::UP:
		if (!texture.loadFromFile("./resources/sfml/head_up.png", sf::IntRect(0, 0, snakeSize, snakeSize)))
			std::cerr << "Error loading image" << std::endl;
		break;
	case eDirection::DOWN:
		if (!texture.loadFromFile("./resources/sfml/head_down.png", sf::IntRect(0, 0, snakeSize, snakeSize)))
			std::cerr << "Error loading image" << std::endl;
		break;
	default:
		break;
	}
	sprite.setTexture(texture);
}

void SFML::drawSnake(const std::vector<std::pair<int,int>> &snake, eDirection dir, int player, int snakeSize)
{
	if (player == 1)
	{
		drawHead(dir, m_SnakeHeadTexture, m_SnakeHeadSprite, snakeSize);
		m_SnakeHeadSprite.setPosition(static_cast<float>(snake.at(0).first), static_cast<float>(snake.at(0).second));
		m_Window.draw(m_SnakeHeadSprite);

		for (auto it = snake.begin() + 1; it != snake.end(); it++)
		{
			m_SnakeSprite.setPosition(static_cast<float>(it->first), static_cast<float>(it->second));
			m_Window.draw(m_SnakeSprite);
		}
	}
	else if (player == 2)
	{
		drawHead(dir, m_Snake2HeadTexture, m_Snake2HeadSprite, snakeSize);
		m_Snake2HeadSprite.setPosition(static_cast<float>(snake.at(0).first), static_cast<float>(snake.at(0).second));
		m_Window.draw(m_Snake2HeadSprite);

		for (auto it = snake.begin() + 1; it != snake.end(); it++)
		{
			m_Snake2Sprite.setPosition(static_cast<float>(it->first), static_cast<float>(it->second));
			m_Window.draw(m_Snake2Sprite);
		}
	}
}

void SFML::drawFruit(const std::pair<int, int> &fruit)
{
	m_FruitSprite.setPosition(static_cast<float>(fruit.first), static_cast<float>(fruit.second));
	m_Window.draw(m_FruitSprite);
}

void SFML::drawStone(const std::vector<std::pair<int, int>> &stone)
{
	for (auto it = stone.begin(); it != stone.end(); it++)
	{
		m_StoneSprite.setPosition(static_cast<float>(it->first), static_cast<float>(it->second));
		m_Window.draw(m_StoneSprite);
	}
}

void SFML::playSound(State &state)
{
//	if (state.endSound)
//	{
//		crashSound.play();
//		return;
//	}
	if (state.eatSound)
	{
		eatSound.play();
	}
}

void SFML::draw(State &state)
{
	playSound(state);
	if (state.onMenu)
		drawMenu(state);
	else if (state.gameOver)
		drawGameOver(state);
	else if (state.onPause)
		drawPause(state);
	else
	{
		m_Window.clear();
		m_Window.draw(m_BackgroundSprite);
		drawSnake(state.snake1Cord, state.snake1Dir, 1, state.snakeSize);
		if(state.multiPlayer)
			drawSnake(state.snake2Cord, state.snake2Dir, 2, state.snakeSize);
		drawFruit(state.fruit);
		drawStone(state.stone);
		m_Window.display();
	}
}

Keys SFML::input()
{
    Keys key = Keys::NONE;
    while (m_Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            key = Keys::ESC;
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)
                key = Keys::UP;
            else if (event.key.code == sf::Keyboard::Down)
                key = Keys::DOWN;
            else if (event.key.code == sf::Keyboard::Left)
                key = Keys::LEFT;
            else if (event.key.code == sf::Keyboard::Right)
                key = Keys::RIGHT;
            else if (event.key.code == sf::Keyboard::Return)
                key = Keys::ENTER;
            else if (event.key.code == sf::Keyboard::W)
                key = Keys::W;
            else if (event.key.code == sf::Keyboard::S)
                key = Keys::S;
            else if (event.key.code == sf::Keyboard::A)
                key = Keys::A;
            else if (event.key.code == sf::Keyboard::D)
                key = Keys::D;
            else if (event.key.code == sf::Keyboard::P)
                key = Keys::P;
            else if (event.key.code == sf::Keyboard::Q)
                key = Keys::Q;
            else if (event.key.code == sf::Keyboard::E)
                key = Keys::E;
            else if (event.key.code == sf::Keyboard::Num1)
                key = Keys::KEY_1;
            else if (event.key.code == sf::Keyboard::Num2)
                key = Keys::KEY_2;
            else if (event.key.code == sf::Keyboard::Num3)
                key = Keys::KEY_3;
        }
    }
	return key;
}

void SFML::wait(int speed)
{
    //std::cout << " wait" << speed << std::endl;
    sf::Time wait = sf::microseconds(speed);
    sf::sleep(wait);
}

SFML::~SFML()
{
	m_Window.clear();
	m_Window.close();
	std::cout << "Call destructor SFML" << std::endl;
}

SFML *maker()
{
	return new SFML();
}
