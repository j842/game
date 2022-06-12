#ifndef __BACKGROUNDMUSIC
#define __BACKGROUNDMUSIC

#include <vector>
#include "sound.h"

class backgroundMusic
{
    public:
        backgroundMusic();
        ~backgroundMusic();

        bool isPlaying();

        void tick();

    private:
        std::vector<sound> mSounds;
        const int N;
        int currentSong;
};


#endif