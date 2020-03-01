#include "NCULIB.hpp"
#include <unistd.h>

NCUL::NCUL()
{
    std::cout << "CONSTRUCT NCURSES" << std::endl;
}

NCUL::NCUL(NCUL const& obj)
{
    *this = obj;
}

NCUL& NCUL::operator=(NCUL const& obj)
{
    if (this == &obj)
        return *this;
    *this = obj;
    return *this;
}

int c;

void NCUL::init(int w, int h, int snakeSize)
{
    screenSize.first = h / snakeSize;
    screenSize.second = 2 * w / snakeSize;

    initscr();
    clear();
    noecho();
    cbreak();
    gameField = newwin(screenSize.first, screenSize.second, 0, 0);
    keypad(gameField, TRUE);
    nodelay(gameField, TRUE);
    curs_set(0);
    start_color();
    init_color(COLOR_MAGENTA, 500, 500, 500);
    init_pair(1, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_CYAN, COLOR_CYAN);
    init_pair(5, COLOR_RED, COLOR_RED);
    init_pair(6, COLOR_WHITE, COLOR_WHITE);
    init_pair(7, COLOR_BLACK, COLOR_BLUE);
    init_pair(8, COLOR_BLACK, COLOR_RED);
    init_pair(9, COLOR_BLACK, COLOR_CYAN);
    init_pair(11, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(10, COLOR_MAGENTA, COLOR_BLACK);
    wbkgd(gameField, COLOR_PAIR(1));

}

void NCUL::drawStone(const std::vector<std::pair<int, int>>& stone)
{
    wattron(gameField, COLOR_PAIR(2));
    for (auto it = stone.begin(); it != stone.end(); it++)
    {
        //std::cout << "first = " << it->first << ": second = " << it->second << std::endl;
        //mvwprintw(gameField, 1, 10, " %d", it->first);
        mvwprintw(gameField, it->second / 25, 2 *it->first / 25, "  ");
    }
    wattroff(gameField, COLOR_PAIR(2));
}

void NCUL::drawSnake(std::vector<std::pair<int, int>> const &snake, eDirection dir, int player, int snakeSize)
{
    if (player == 1)
    {
        wattron(gameField, COLOR_PAIR(3));
        mvwprintw(gameField, snake[0].second / 25, 2 * snake[0].first / 25, "  ");
        wattroff(gameField, COLOR_PAIR(3));

        for (auto it = snake.begin() + 1; it != snake.end(); it++)
        {
            wattron(gameField, COLOR_PAIR(11));
            mvwprintw(gameField, it->second / 25, 2 * it->first / 25, "  ");
            wattroff(gameField, COLOR_PAIR(11));
        }
    }
    else if (player == 2)
    {
        wattron(gameField, COLOR_PAIR(6));
        mvwprintw(gameField, snake[0].second / 25, 2 * snake[0].first / 25, "  ");
        wattroff(gameField, COLOR_PAIR(6));
        for (auto it = snake.begin() + 1; it != snake.end(); it++)
        {
            wattron(gameField, COLOR_PAIR(11));
            mvwprintw(gameField, it->second / 25, 2 * it->first / 25, "  ");
            wattroff(gameField, COLOR_PAIR(11));
        }
    }
}

void NCUL::drawFruit(const std::pair<int, int>& fruit)
{
    wattron(gameField, COLOR_PAIR(5));
    mvwprintw(gameField, fruit.second / 25, 2 * fruit.first / 25, "  ");
    wattroff(gameField, COLOR_PAIR(5));
}


void NCUL::draw(State &state)
{
    int w, h;
    getmaxyx(gameField, h, w);
    if (h != screenSize.first || w != screenSize.second)
        wresize(gameField, screenSize.first, screenSize.second);

    werase(gameField);

//    if (state.onMenu)
//        drawMenu(state);
//    else if (state.onPause)
//        drawPause(state);
//    else if (state.gameOver)
//        drawGameOver(state);
//    else
    {
        wattron(gameField, COLOR_PAIR(8));
        mvwprintw(gameField, 1, 1, "RET %d", c);
        wattroff(gameField, COLOR_PAIR(8));
        wattron(gameField, COLOR_PAIR(4));
        wborder(gameField, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        wattroff(gameField, COLOR_PAIR(4));
        drawSnake(state.snake1Cord, state.snake1Dir, 1, state.snakeSize);
        //if(state.multiPlayer)
            drawSnake(state.snake2Cord, state.snake2Dir, 2, state.snakeSize);
        drawFruit(state.fruit);
        drawStone(state.stone);
    }

    wrefresh(gameField);
}

Keys NCUL::input()
{
    int key = wgetch(gameField);
    Keys ret = Keys::NONE;
    switch(key) {
        case KEY_UP:
            ret = Keys::UP;
            break;
        case KEY_DOWN:
            ret = Keys::DOWN;
            break;
        case KEY_LEFT:
            ret = Keys::LEFT;
            break;
        case KEY_RIGHT:
            ret = Keys::RIGHT;
            break;
        case 'q':
            ret = Keys::ENTER;
            break;
        case 'p':
            ret = Keys::P;
            break;
        case 'w':
            ret = Keys::W;
            break;
        case 'a':
            ret = Keys::A;
            break;
        case 's':
            ret = Keys::S;
            break;
        case 'd':
            ret = Keys::D;
            break;
//        case KEY_LEFT:
//            ret = Keys::LEFT;
//            break;
//        case KEY_RIGHT:
//            ret = Keys::RIGHT;
//            break;
        default:
            break;
    }
    c = key;
    return ret;
}

void NCUL::wait(int speed)
{
    usleep(speed);
}

NCUL::~NCUL()
{

    delwin(gameField);
    endwin();
}

NCUL *maker() {
    return new NCUL();
}