//
// Created by liuqikang on 2018/6/21.
//

#include "FFmpeg.h"

FFmpeg::FFmpeg(JavaMethod *jmid, const char *path) {
    javaMethod = jmid;
    url = path;
}

FFmpeg::~FFmpeg() {

}

void* decodeAudio(void*data)
{
    FFmpeg*fmpeg = (FFmpeg *) data;
    fmpeg->decode();
    pthread_exit(&fmpeg->decodeThread);
}

void FFmpeg::prepared() {

    pthread_create(&decodeThread, 0, decodeAudio,this);
}

void FFmpeg::decode() {
    avcodec_register_all();
    avformat_network_init();
    pFormatCxt = avformat_alloc_context();
    if (avformat_open_input(&pFormatCxt, url, 0, 0) != 0)
    {
        LOGD("avformat_open_input failed");
        return;
    }

    if (av)
}
