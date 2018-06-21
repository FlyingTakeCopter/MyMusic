//
// Created by liuqikang on 2018/6/21.
//

#ifndef MYMUSIC_AUDIO_H
#define MYMUSIC_AUDIO_H

extern "C"
{
#include <libavcodec/avcodec.h>
};

class Audio {
public:
    int audioIndex;
    AVCodecParameters*pCodecPrm = NULL;


    Audio();
    ~Audio();


};


#endif //MYMUSIC_AUDIO_H
