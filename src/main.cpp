#include <iostream>

#include "utils.h"
#include "sound.h"


int main()
{
    sound s0("ff-16b-2c-44100hz.mp3");
    s0.play();

    sound s1("test.wav");
    s1.play();

    while (s0.isPlaying() || s1.isPlaying())
        ;
}


