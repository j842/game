#include <iostream>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "sound.h"
#include "utils.h"

ma_engine * getEngine()
{
    static ma_engine engine;
    static bool initialised=false;

    if (!initialised)
    {
        ma_result result;
        result = ma_engine_init(NULL, &engine);
        initialised=true;

        if (result != MA_SUCCESS)
        {
            std::cerr << "Error starting sound engine! " << result << std::endl;
            exit(-1);
        }
    }

    return &engine;
}


sound::sound() : mResult(MA_DEVICE_NOT_INITIALIZED)
{
}

sound::sound(std::string fname) : mResult(MA_DEVICE_NOT_INITIALIZED)
{
    init(fname);
}

void sound::play()
{
    ma_sound_start(&mSound);
}
void sound::stop()
{
    ma_sound_stop(&mSound);
}
bool sound::isPlaying()
{
    return ma_sound_is_playing(&mSound);
}

bool sound::okay() { return MA_SUCCESS == mResult; }

void initEngine(ma_engine &engine)
{

}

void sound::init(std::string fname) {
    std::string path = getExePath() + "sounds/" + fname;
    mResult = ma_sound_init_from_file(getEngine(), path.c_str(), 0, NULL, NULL, &mSound);
}
