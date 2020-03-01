#ifndef NIBLER_NCULIB_HPP
#define NIBLER_NCULIB_HPP

#include <ncurses.h>
#include <iostream>
#include "GUI.h"

class NCUL : public GUI
{
private:
    std::pair<int, int> screenSize;
    WINDOW *gameField;
public:
    NCUL();
    NCUL(NCUL const &obj);
    ~NCUL() override;
    NCUL &operator=(NCUL const &obj);

    void draw(State &state) override;
    Keys input() override;
    void init(int w, int h, int snakeSize) override;
    void wait(int speed) override;

private:
    void drawSnake(std::vector<std::pair<int, int>> const &snake, eDirection dir, int player, int snakeSize);
    void drawStone(const std::vector<std::pair<int, int>>& stone);
    void drawFruit(const std::pair<int, int>& fruit);
};

extern "C"
{
NCUL *maker();
}

#endif //NIBLER_NCULIB_HPP