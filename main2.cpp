#include <iostream>
#include <unistd.h>

#include "stb_vorbis.c"

#define CUTE_SOUND_FORCE_SDL
#define CUTE_SOUND_IMPLEMENTATION
#include "cute_sound.h"


void doMain()
{
    cs_error_t err;
    cs_audio_source_t * src;
    src = cs_load_wav("BabyElephantWalk60.wav",&err);

    cs_music_play(src,0);


    // cs_sound_params_t params = cs_sound_params_default();
    // cs_playing_sound_t snd = cs_play_sound(src,params);

    // if (!cs_sound_is_active(snd))
    //     std::cerr << "NOt active!" <<std::endl;

    // if (cs_sound_get_is_paused(snd))
    //     std::cerr << "PAUSED" << std::endl;

    // while (cs_sound_is_active(snd))
    // {
    //     std::cout<<".";
    //     usleep(100);
    // }
    // std::cout << std::endl;
}

int main()
{
    cs_error_t e = cs_init(NULL,44100,2048,NULL);

    if (e!= CUTE_SOUND_ERROR_NONE)
        std::cerr << " Error - " << e << std::endl;

    doMain();

    //sleep(5);

    cs_shutdown();
}