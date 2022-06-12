#include <ncurses.h>
#include <chrono>
#include <unistd.h>

#include "con.h"
#include "utils.h"

Con *con()
{
    static Con c;
    return &c;
}

Con::Con() : HasEnded(false)
{
    lastTick = std::chrono::steady_clock::now();

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    set_escdelay(50);
    mousemask(ALL_MOUSE_EVENTS, NULL); // https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/mouse.html

    getmaxyx(stdscr, h, w);

    move(0, 0);
    std::string msg = S() << "w= " << w << "  h= " << h;
    addstr(msg.c_str());
    refresh();

    mTicker.init(w);
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
        HasEnded = true;
    }
}

void Con::title()
{
    attron(A_STANDOUT);
    std::string s = "SPIDER ATTACK!";
    int l = s.length() / 2;
    move(h / 2, (w - l) / 2);
    addstr(s.c_str());
    refresh();
    attroff(A_STANDOUT);
}

void Con::errormsg(std::string s)
{
    clear();
    attron(A_STANDOUT);
    int l = s.length() / 2;
    move(h / 2, (w - l) / 2);
    addstr(s.c_str());
    refresh();
    attroff(A_STANDOUT);
}

void Con::tick()
{
    steady end = std::chrono::steady_clock::now();

    int64_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - lastTick).count();

    if (elapsed > 200)
    {
        move(h - 1, 0);
        const char *s = mTicker.advance_and_get();
        addstr(s);
        refresh();

        lastTick = end;
    }
}

void Con::resize()
{
    getmaxyx(stdscr, h, w);
    mTicker.resize(w);
}

Ticker::Ticker() : mWidth(0)
{
}

void Ticker::init(int width)
{
    mWidth = width;
    mDisplay = std::string(mWidth, ' ');
}

void Ticker::add(std::string s)
{
    mBuffer += s;
}

const char *Ticker::advance_and_get()
{
    mDisplay.erase(0, 1);
    _transferchar();

    return mDisplay.c_str();
}

void Con::addToTicker(std::string s)
{
    mTicker.add(s);
}

void Ticker::resize(int newwidth)
{
    if (newwidth < mWidth)
    {
        mBuffer.insert(0, mDisplay.substr(newwidth));
        mDisplay.erase(newwidth);
    }
    else
        while (static_cast<int>(mDisplay.length()) < newwidth)
            _transferchar();
    mWidth = newwidth;
}

void Ticker::_transferchar()
{
    if (mBuffer.length() > 0)
    {
        mDisplay.push_back(mBuffer[0]);
        mBuffer.erase(0, 1);
    }
    else
        mDisplay.push_back(' ');
}
