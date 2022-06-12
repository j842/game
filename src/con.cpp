#include <ncurses.h>

#include "con.h"


Con * con() 
{
    static Con c;
    return &c;
}


Con::Con() : HasEnded(false)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    set_escdelay(50);
}

Con::~Con()
{
    endCon();
}

void Con::endCon()
{
    if (!HasEnded)
        {
            endwin();
            HasEnded=true;
        }
}

void Con::title()
{
    int h, w;
    getmaxyx(stdscr, h, w);

    attron(A_STANDOUT);
    std::string s = "SPIDER ATTACK!";
    int l = s.length() / 2;
    move(h / 2, (w - l) / 2);
    addstr(s.c_str());
    refresh();
    attron(A_NORMAL);
}

void Con::errormsg(std::string s)
{
    int h, w;
    getmaxyx(stdscr, h, w);

    clear();
    attron(A_STANDOUT);
    int l = s.length() / 2;
    move(h / 2, (w - l) / 2);
    addstr(s.c_str());
    refresh();
    attron(A_NORMAL);
}
