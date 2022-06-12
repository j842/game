#include <iostream>

#include <curses.h>
#include <vector>
#include <random>
#include <unistd.h>

#include "utils.h"
#include "sound.h"
#include "con.h"
#include "backgroundmusic.h"

int main()
{

    try
    {
        con()->title();
        con()->addToTicker("Spider Attack!");

        backgroundMusic bgm;

        // sound s1("test.wav");
        // s1.play();

        int ch;
        while (true) // breakable loop
        {
            if ((ch = getch()) != ERR) // keypress
            {
                switch (ch)
                {
                    case 'q':
                    case 27:
                        goto exitspiderattack;

                    case KEY_RESIZE:
                        con()->resize();
                }
            }
            bgm.tick();
            con()->tick();
        }
    }
    catch (const std::exception &e)
    {
        con()->endCon();
        std::cerr << e.what() << std::endl;
    }


exitspiderattack:
    con()->endCon();
    std::cout<< std::endl << "Goodbye!" << std::endl;
}
