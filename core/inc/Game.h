#ifndef GAME_H
#define GAME_H

#include <dlfcn.h>
#include "Snake.h"
#include "GUI.h"
//#include "SFML.h"

class GUI;

enum class eLibNum
{
    NONE = 0,
    SFML,
    SDL,
    GTK
};

class Game
{
private:
    eLibNum currLib;
	std::pair<int, int> fruit;
	std::pair<int, int> screen;
	std::vector<std::pair<int, int>> stone;
	std::unique_ptr<Snake> snake1;
	std::unique_ptr<Snake> snake2;
	GUI* gui;
	void* libHandle;
	bool multiPlayer;
	bool gameOver;
	bool exit;
	bool onMenu;
	bool onPause;
	bool eatSound;
	bool endSound;
	int speed;
	int menuPos;
	bool enterPress;

	State state;
	//void initState();
	void updateState();
	GUI* loadGuiLib(eLibNum num);

public:
	Game();
	Game(int w, int h);
	Game(Game const& obj);
	~Game();
	Game& operator=(Game const& obj);

	void init();
	void startGame();
	void input();
	void logic();
	void draw();
	void wait();
	void createStoneMap(int count);
	void createFruit();

	void setMultiPlayer(bool m);
	void setGameOver(bool g);
	void setExit(bool e);
	void setSpeed(int s);

	const Snake* getSnake1() const;
	const Snake* getSnake2() const;
	const bool &getExit() const;
	const bool &getGameOver() const;
	const bool &getMultiPlayer() const;
	const std::vector<std::pair<int, int>> &getStone() const;
	const std::pair<int, int> &getFruit() const;
	const std::pair<int, int> &getScreenSize()const ;

	void checkCordFruit(Snake* snake);
	void checkCordMap(const int& x, const int& y);
	void checkCordSnake(Snake* snake);
	void checkCordSnakeMulti();
	int checkCordStone(const std::pair<int, int> &cord);
	bool checkCordForPlace(const int& x, const int& y);
};
#endif // !GAME_H
