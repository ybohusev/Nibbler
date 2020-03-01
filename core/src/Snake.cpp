#include "Snake.h"

Snake::Snake()
{
	pos_x = 1000 / 2;
	pos_y = 1000 / 2;
	score = 0;
	dir = eDirection::STOP;
}

Snake::Snake(Snake const &obj)
{
	*this = obj;
}

Snake::Snake(int width, int height)
{
	pos_x = width / 2;
	pos_y = height / 2;
	score = 0;
	dir = eDirection::STOP;
}

void Snake::createSnake(int count)
{
	for (int i = 0, dist = 0; i < count; i++, dist += SNAKE_SIZE)
		cord.push_back(std::make_pair(pos_x + dist, pos_y));
}

void Snake::addToTail()
{
	size_t prev = 0;
	if (cord.size() < 2)
		prev = cord.size() - 1;
	else
		prev = cord.size() - 2;
	if (cord.at(prev).first > cord.back().first || (prev == 0 && dir == eDirection::RIGHT))
		cord.emplace_back(std::make_pair(cord.back().first - SNAKE_SIZE, cord.back().second));
	else if (cord.at(prev).first < cord.back().first || (prev == 0 && dir == eDirection::LEFT))
		cord.emplace_back(std::make_pair(cord.back().first + SNAKE_SIZE, cord.back().second));
	else if (cord.at(prev).second > cord.back().second || (prev == 0 && dir == eDirection::DOWN))
		cord.emplace_back(std::make_pair(cord.back().first, cord.back().second - SNAKE_SIZE));
	else if (cord.at(prev).second < cord.back().second || (prev == 0 && dir == eDirection::UP))
		cord.emplace_back(std::make_pair(cord.back().first, cord.back().second + SNAKE_SIZE));
	else
		std::cout << "Can't add to tail!\n";
}

void Snake::eraseTail(std::vector<std::pair<int, int>>::const_iterator &itert)
{
	cord.erase(itert, cord.end());
}

void Snake::choseDirectionP2(Keys key)
{
	switch (key)
	{
	    case Keys::LEFT:
            if (dir != eDirection::RIGHT)
                dir = eDirection::LEFT;
            break;
	    case Keys::UP:
            if (dir != eDirection::DOWN)
                dir = eDirection::UP;
            break;
	    case Keys::DOWN:
            if (dir != eDirection::UP)
                dir = eDirection::DOWN;
            break;
	    case Keys::RIGHT:
            if (dir != eDirection::LEFT)
                dir = eDirection::RIGHT;
            break;
	    default:
		    break;
	}
}

void Snake::choseDirectionP1(Keys key)
{
	switch (key)
	{
	    case Keys::A:
		    if (dir != eDirection::RIGHT)
		    	dir = eDirection::LEFT;
		    break;
	    case Keys::W:
		    if (dir != eDirection::DOWN)
		    	dir = eDirection::UP;
		    break;
	    case Keys::S:
            if (dir != eDirection::UP)
                dir = eDirection::DOWN;
            break;
	    case Keys::D:
            if (dir != eDirection::LEFT)
                dir = eDirection::RIGHT;
            break;
        default:
            break;
	}
}

void Snake::moveDirection()
{
	switch (dir)
	{
	case eDirection::LEFT:
		pos_x -= SNAKE_SIZE;
		break;
	case eDirection::RIGHT:
		pos_x += SNAKE_SIZE;
		break;
	case eDirection::UP:
		pos_y -= SNAKE_SIZE;
		break;
	case eDirection::DOWN:
		pos_y += SNAKE_SIZE;
		break;
	case eDirection::STOP:
		break;
	default:
		break;
	}
	if (dir != eDirection::STOP)
		move(pos_x, pos_y);
}

void Snake::move(int x, int y)
{
	std::vector<std::pair<int, int>> prev;
	prev = cord;
	cord[0] = std::make_pair(x, y);
	for (size_t i = 1, j = 0; i < cord.size(); i++, j++)
		cord[i] = prev[j];
}

const std::vector<std::pair<int, int>> &Snake::getCord() const
{
	return cord;
}

const int &Snake::getScore() const
{
	return score;
}

void Snake::setScore(int s)
{
	score = s;
}

const eDirection &Snake::getDirection() const
{
	return dir;
}

Snake::~Snake()
{
}

Snake& Snake::operator=(Snake const &obj)
{
	if (this == &obj)
		return *this;
	*this = obj;
	return *this;
}
