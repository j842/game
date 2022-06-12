#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

int main()
{
    ma_result result;
    ma_engine engine;

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS)
    {
        return result; // Failed to initialize the engine.
    }

    ma_sound sound;

    result = ma_sound_init_from_file(&engine, "test.wav", 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS)
    {
        return result;
    }

    ma_sound_start(&sound);

    while (ma_sound_is_playing(&sound))
        ;
}


