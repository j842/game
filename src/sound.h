#include <string>

#include "miniaudio.h"


class sound
{
    public:
        sound();
        sound(std::string fname);
        
        void init(std::string fname);
        void play();
        void stop();
        bool isPlaying();
        bool okay();

private:
    ma_result mResult;
    ma_sound mSound;
};