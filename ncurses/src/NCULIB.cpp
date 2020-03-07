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

void NCUL::init(int w, int h, int snakeSize)
{
    screenSize.first = h / snakeSize;
    screenSize.second = 2 * w / snakeSize;

    //initscr();
    newterm(getenv("TERM"), stdout, stdin);
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
    init_pair(7, COLOR_BLUE, COLOR_CYAN);
    init_pair(8, COLOR_BLACK, COLOR_RED);
    init_pair(9, COLOR_BLACK, COLOR_CYAN);
    init_pair(10, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(11, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(12, COLOR_RED, COLOR_CYAN);
    init_pair(13, COLOR_YELLOW, COLOR_RED);

}

void NCUL::drawMenu(State &state)
{
    wbkgd(gameField, COLOR_PAIR(4));
    wattron(gameField, COLOR_PAIR(7));
    mvwprintw(gameField, (screenSize.first / 2) - 3, (screenSize.second / 2) - 2, "Play");
    mvwprintw(gameField, (screenSize.first / 2) - 2, (screenSize.second / 2) - 5, "Multiplayer");
    mvwprintw(gameField, (screenSize.first / 2) - 1, (screenSize.second / 2) - 2, "Exit");

    wattroff(gameField, COLOR_PAIR(7));

    wattron(gameField, COLOR_PAIR(12));
    if (state.menuPos == 0)
        mvwprintw(gameField, (screenSize.first / 2) - 3, (screenSize.second / 2) - 2, "Play");
    else if (state.menuPos == 1)
        mvwprintw(gameField, (screenSize.first / 2) - 2, (screenSize.second / 2) - 5, "Multiplayer");
    else
        mvwprintw(gameField, (screenSize.first / 2) - 1, (screenSize.second / 2) - 2, "Exit");
    wattroff(gameField, COLOR_PAIR(12));
}

void NCUL::drawGameOver(State &state)
{
    wbkgd(gameField, COLOR_PAIR(5));
    wattron(gameField, COLOR_PAIR(13));
    mvwprintw(gameField, (screenSize.first / 2) - 1, (screenSize.second / 2) - 5, "Game Over");
    mvwprintw(gameField, (screenSize.first / 2), (screenSize.second / 2) - 9, "Press ESC to exit");

    mvwprintw(gameField, 1, 2, "Score 1: %d", state.snake1Score);
    if (state.multiPlayer)
        mvwprintw(gameField, 2, 2, "Score 2: %d", state.snake2Score);
    wattron(gameField, COLOR_PAIR(13));
}

void NCUL::drawPause(State &state)
{
    wbkgd(gameField, COLOR_PAIR(4));

    wattron(gameField, COLOR_PAIR(7));
    mvwprintw(gameField, (screenSize.first / 2) - 2, (screenSize.second / 2) - 4, "Continue");
    mvwprintw(gameField, (screenSize.first / 2) - 1, (screenSize.second / 2) - 2, "Exit");
    wattroff(gameField, COLOR_PAIR(7));

    wattron(gameField, COLOR_PAIR(12));
    if (state.menuPos == 0)
        mvwprintw(gameField, (screenSize.first / 2) - 2, (screenSize.second / 2) - 4, "Continue");
    else
        mvwprintw(gameField, (screenSize.first / 2) - 1, (screenSize.second / 2) - 2, "Exit");
    wattroff(gameField, COLOR_PAIR(12));
}

void NCUL::drawStone(const std::vector<std::pair<int, int>>& stone)
{
    wattron(gameField, COLOR_PAIR(2));
    for (auto it = stone.begin(); it != stone.end(); it++)
    {
        mvwprintw(gameField, it->second / 25, 2 *it->first / 25, "  ");
    }
    wattroff(gameField, COLOR_PAIR(2));
}

void NCUL::drawSnake(std::vector<std::pair<int, int>> const &snake, int player)
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

    if (state.onMenu)
        drawMenu(state);
    else if (state.onPause)
        drawPause(state);
    else if (state.gameOver)
        drawGameOver(state);
    else
    {
        wbkgd(gameField, COLOR_PAIR(1));
        drawSnake(state.snake1Cord, 1);
        if(state.multiPlayer)
            drawSnake(state.snake2Cord, 2);
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
        case 10:
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
        case 'q':
            ret = Keys::Q;
            break;
        case 'e':
            ret = Keys::E;
            break;
        case '1':
            ret = Keys::KEY_1;
            break;
        case '2':
            ret = Keys::KEY_2;
            break;
        case '3':
            ret = Keys::KEY_3;
            break;
        case 27:
            ret = Keys::ESC;
            break;
        default:
            break;
    }
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
    std::cout << "Call destructor ncurses" << std::endl;
}

NCUL *maker() {
    return new NCUL();
}