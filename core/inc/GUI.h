#ifndef _GUI_H_
# define _GUI_H_

#include <vector>

enum class eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct State
{
    int snakeSize;

    std::vector< std::pair<int, int> > snake1Cord;
    std::vector< std::pair<int, int> > snake2Cord;

    int snake1Score;
    int snake2Score;

    eDirection snake1Dir;
    eDirection snake2Dir;

    std::pair<int, int> fruit;
    std::vector< std::pair<int, int> > stone;
    bool multiPlayer;
    bool gameOver;
    bool exit;
    bool onPause;
    bool onMenu;
	bool eatSound;
	bool endSound;
	int speed;
    int menuPos;
};

enum class Keys
{
    NONE = 0,
    P,
    ESC,
    E,
    Q,
    A,
    D,
    W,
    S,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    ENTER,
    KEY_1,
    KEY_2,
    KEY_3
};

class GUI
{
public:
	virtual ~GUI() {};
	virtual void draw(State &state) = 0;
	virtual Keys input() = 0;
	virtual void init(int w, int h, int snakeSize) = 0;
	virtual void wait(int speed) = 0;
};
#endif // !_GUI_H_