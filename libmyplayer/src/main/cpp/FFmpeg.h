//
// Created by liuqikang on 2018/6/21.
//

#ifndef MYMUSIC_FFMPEG_H
#define MYMUSIC_FFMPEG_H


#include <sys/types.h>
#include "JavaMethod.h"
#include <pthread.h>

extern "C"
{
#include <libavcodec/avcodec.h>
#include "libavformat/avformat.h"
};

class FFmpeg {
public:
    JavaMethod*javaMethod = NULL;
    const char* url = NULL;
    pthread_t decodeThread;
    AVFormatContext*pFormatCxt = NULL;

    FFmpeg(JavaMethod*jmid, const char* path);
    ~FFmpeg();

    void prepared();

    void decode();
};


#endif //MYMUSIC_FFMPEG_H
