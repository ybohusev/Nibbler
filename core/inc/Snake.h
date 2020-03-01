#ifndef SNAKE_H
# define SNAKE_H
#include <iostream>
#include <vector>
#include "GUI.h"

#define SNAKE_SIZE 25

class Snake
{
private:
	int pos_x;
	int pos_y;
	int score;

	eDirection dir;
	std::vector<std::pair<int, int>> cord;
public:
	Snake();
	Snake(int width, int height);
	Snake(Snake const &obj);
	~Snake();
	Snake& operator = (Snake const &obj);

	void createSnake(int count);
	void addToTail();
	void eraseTail(std::vector<std::pair<int, int>>::const_iterator& itert);
	void moveDirection();
	void choseDirectionP1(Keys key);
	void choseDirectionP2(Keys key);
	void move(int x, int y);

	void setScore(int s);
	const std::vector<std::pair<int, int>> &getCord() const;
	const int &getScore() const;
	const eDirection &getDirection() const;
};

#endif // SNAKE_H
