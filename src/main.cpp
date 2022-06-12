#include <iostream>

#include <curses.h>
#include <vector>
#include <random>

#include "utils.h"
#include "sound.h"

class curses_mgr
{
public:
    curses_mgr()
    {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        curs_set(0);
    }

    ~curses_mgr()
    {

        endwin();
    }
};

void title()
{
    int h, w;
    getmaxyx(stdscr, h, w);

    attron(A_STANDOUT);
    std::string s="SPIDER ATTACK!";
    int l=s.length()/2;
    move(h/2,(w-l)/2);
    addstr(s.c_str());
    refresh();
    attron(A_NORMAL);
}

void errormsg(std::string s)
{
    int h, w;
    getmaxyx(stdscr, h, w);

    clear();
    attron(A_STANDOUT);
    int l=s.length()/2;
    move(h/2,(w-l)/2);
    addstr(s.c_str());
    refresh();
    attron(A_NORMAL);   
}

class backgroundMusic
{
    public:
        backgroundMusic() :
            N(static_cast<int>(mSounds.size())),
            currentSong(-1)
        {
            const std::vector<std::string> musicfiles = {"ff-16b-2c-44100hz.mp3","test.wav"};
            mSounds.resize(musicfiles.size());

            for (size_t i=0;i<musicfiles.size();++i)
            {
                mSounds[i].init(musicfiles[i]);
                if (mSounds[i].okay()==false)
                    errormsg(S()<<"Could not load sound "<<musicfiles[i]<<std::endl);
            }
        }

        bool isPlaying()
        {
            return (currentSong>=0 && currentSong<N && mSounds[currentSong].isPlaying());
        }

        ~backgroundMusic()
        {
            if (isPlaying())
                mSounds[currentSong].stop();
        }

        void tick()
        {
            if (!isPlaying())
            {
                ++currentSong;
                if (currentSong>=N) 
                    currentSong=0;

                mSounds[currentSong].play();                    
            }

            if (!mSounds[currentSong].okay())
               errormsg("Sound not okay"); 
        }

    private:
        std::vector<sound> mSounds;
        const int N;
        int currentSong;
};

int main()
{
        
        try
        {
            curses_mgr m;
            int ch;
            title();

            backgroundMusic bgm;

            // sound s1("test.wav");
            // s1.play();

            while (true) // breakable loop
            {
                if ((ch = getch()) != ERR) // keypress
                {
                    if (ch=='q' || ch==27)
                        break;
                }
                bgm.tick();
            }
                
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    

    std::cerr << "Bye."<<std::endl;
}
