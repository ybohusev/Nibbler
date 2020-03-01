#ifndef _SDLLIB_H_
# define _SDLLIB_H_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GUI.h"

class SDLLIB : public GUI
{
private:
    SDL_Event event;
	std::vector<SDL_Texture*> textureList;
	
	std::pair<int, int> screenSize;

    SDL_Window *win;
    SDL_Renderer *ren;

    SDL_Texture *m_BackgroundTexture;
    SDL_Texture *m_SnakeTexture;
    SDL_Texture *m_SnakeHeadTextureLeft;
    SDL_Texture *m_SnakeHeadTextureRight;
    SDL_Texture *m_SnakeHeadTextureUp;
    SDL_Texture *m_SnakeHeadTextureDown;
    SDL_Texture *m_Snake2Texture;
    SDL_Texture *m_FruitTexture;
//
//	sf::Sprite m_MenuSprite;
//	sf::Texture m_MenuTexture;
//
//	sf::Sprite m_GameOverSprite;
//	sf::Texture m_GameOverTexture;
//
//	sf::Sprite m_PauseSprite;
//	sf::Texture m_PauseTexture;
    SDL_Texture *m_StoneTexture;
//
//	sf::Font Font;

	//sf::SoundBuffer eatBuffer;
	//sf::Sound eatSound;

	//sf::SoundBuffer crashBuffer;
	//sf::Sound crashSound;
public:
	SDLLIB();
	SDLLIB(SDLLIB const &obj);
	~SDLLIB() override;
	SDLLIB &operator=(SDLLIB const &obj);

	void draw(State &state) override;
    Keys input() override;
	void init(int w, int h, int snakeSize) override;
    void wait(int speed) override;

private:
    SDL_Texture *loadTexture(std::string path);
	void drawSnake(std::vector<std::pair<int, int>> const &snake, eDirection dir, int player, int snakeSize);
    SDL_Texture *drawHead(eDirection& dir);
	void drawFruit(const std::pair<int, int>& fruit);
	void drawStone(const std::vector<std::pair<int, int>>& stone);
	void drawMenu(State &state);
	void drawGameOver(State &state);
	void drawPause(State &state);
};

extern "C"
{
    SDLLIB *maker();
}
#endif // !_SDL_H_
