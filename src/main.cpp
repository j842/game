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

        backgroundMusic bgm;

        // sound s1("test.wav");
        // s1.play();

        int ch;
        while (true) // breakable loop
        {
            if ((ch = getch()) != ERR) // keypress
            {
                if (ch == 'q' || ch == 27)
                    break;
            }
            bgm.tick();
        }
    }
    catch (const std::exception &e)
    {
        con()->endCon();
        std::cerr << e.what() << std::endl;
    }

    con()->endCon();
    std::cout<< std::endl << "Goodbye!" << std::endl;
}
