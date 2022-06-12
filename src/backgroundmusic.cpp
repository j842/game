#include "backgroundmusic.h"
#include "utils.h"
#include "con.h"

backgroundMusic::backgroundMusic() : N(static_cast<int>(mSounds.size())),
                                     currentSong(-1)
{
    const std::vector<std::string> musicfiles = {"test.wav", "ff-16b-2c-44100hz.mp3"};
    mSounds.resize(musicfiles.size());

    for (size_t i = 0; i < musicfiles.size(); ++i)
    {
        mSounds[i].init(musicfiles[i]);
        if (mSounds[i].okay() == false)
            con()->errormsg(S() << "Could not load sound " << musicfiles[i] << std::endl);
    }
}

bool backgroundMusic::isPlaying()
{
    return (currentSong >= 0 && currentSong < N && mSounds[currentSong].isPlaying());
}

backgroundMusic::~backgroundMusic()
{
    if (isPlaying())
        mSounds[currentSong].stop();
}

void backgroundMusic::tick()
{
    if (!isPlaying())
    {
        ++currentSong;
        if (currentSong >= N)
            currentSong = 0;

        mSounds[currentSong].play();
    }

    if (!mSounds[currentSong].okay())
        con()->errormsg("Sound couldn't play.");
}
