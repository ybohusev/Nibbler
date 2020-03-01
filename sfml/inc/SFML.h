#ifndef _SFML_H_
# define _SFML_H_
#include "GUI.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SFML : public GUI
{
private:
	//bool f_playing;
	//bool f_pause;
	//bool f_gameOver;
	//bool f_multiplayer;
	
	std::pair<int, int> screenSize;
	sf::Vector2i position;

	sf::RenderWindow m_Window;
    sf::Event event;

	sf::Sprite m_BackgroundSprite;
	sf::Texture m_BackgroundTexture;

	sf::Sprite m_SnakeSprite;
	sf::Texture m_SnakeTexture;

	sf::Sprite m_SnakeHeadSprite;
	sf::Texture m_SnakeHeadTexture;

	sf::Sprite m_Snake2Sprite;
	sf::Texture m_Snake2Texture;

	sf::Sprite m_Snake2HeadSprite;
	sf::Texture m_Snake2HeadTexture;

	sf::Sprite m_FruitSprite;
	sf::Texture m_FruitTexture;	
	
	sf::Sprite m_MenuSprite;
	sf::Texture m_MenuTexture;	
	
	sf::Sprite m_GameOverSprite;
	sf::Texture m_GameOverTexture;	
	
	sf::Sprite m_PauseSprite;
	sf::Texture m_PauseTexture;

	sf::Sprite m_StoneSprite;
	sf::Texture m_StoneTexture;

	sf::Font Font;

	//sf::SoundBuffer eatBuffer;
	//sf::Sound eatSound;

	//sf::SoundBuffer crashBuffer;
	//sf::Sound crashSound;
public:
	SFML();
	SFML(SFML const &obj);
	~SFML() override;
	SFML &operator=(SFML const &obj);

	void draw(State &state) override;
    Keys input() override;
	void init(int w, int h, int snakeSize) override;
    void wait(int speed) override;

private:
	void drawSnake(std::vector<std::pair<int, int>> const &snake, eDirection dir, int player, int snakeSize);
	void drawHead(eDirection& dir, sf::Texture& texture, sf::Sprite& sprite, int snakeSize);
	void drawFruit(const std::pair<int, int>& fruit);
	void drawStone(const std::vector<std::pair<int, int>>& stone);
	void drawMenu(State &state);
	void drawGameOver(State &state);
	void drawPause(State &state);
};

extern "C"
{
    SFML *maker();
}
#endif // !_SFML_H_
