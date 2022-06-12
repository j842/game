#ifndef __CON
#define __CON

#include <string>
#include <chrono>

class Ticker
{
    public:
        Ticker();

        void init(int width);
        void add(std::string s);
        const char * advance_and_get();

    private:
        std::string mDisplay;
        std::string mBuffer;
        int mWidth;
};

typedef std::chrono::_V2::steady_clock::time_point steady;

class Con
{
public:
    Con();
    ~Con();

    void errormsg(std::string s);
    void title();

    void endCon();

    void addToTicker(std::string s);

    void tick();

private:
    bool HasEnded;
    Ticker mTicker;
    int h,w;
    steady lastTick;
};

Con * con();

#endif