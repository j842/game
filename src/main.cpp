#include <iostream>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "utils.h"

class sound
{
    public:
        sound(std::string fname, ma_engine * engine)
        {
            std::string path = getExePath() + "sounds/" + fname;
             mResult = ma_sound_init_from_file(engine, path.c_str(), 0, NULL, NULL, &mSound);
        }

        void play()
        {
            ma_sound_start(&mSound);    
        }
        void stop()
        {
            ma_sound_stop(&mSound);
        }
        bool isPlaying()
        {
            return ma_sound_is_playing(&mSound);
        }

        bool okay() {return MA_SUCCESS==mResult;}

private:
    ma_result mResult;
    ma_sound mSound;
};


void initEngine(ma_engine & engine)
{
    ma_result result;
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS)
    {
        std::cerr << "Error starting sound engine! "<<result<<std::endl;
        exit(result); // Failed to initialize the engine.
    }

}


int main()
{
    ma_engine engine;
    initEngine(engine);

    sound s0("ff-16b-2c-44100hz.mp3",&engine);
    s0.play();

    sound s1("test.wav",&engine);
    s1.play();

    while (s0.isPlaying() || s1.isPlaying())
        ;
}


