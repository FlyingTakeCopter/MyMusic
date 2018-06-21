//
// Created by liuqikang on 2018/6/21.
//

#include "FFmpeg.h"

FFmpeg::FFmpeg(JavaMethod *jmid, const char *path) {
    javaMethod = jmid;
    LOGD("FFmpeg path: %s", path);
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

    av_register_all();
    avformat_network_init();

    avcodec_register_all();
    //pFormatCxt = avformat_alloc_context();
    LOGD("url is %s", this->url);
    int res = -1;
    if ((res = avformat_open_input(&pFormatCxt, this->url, 0, 0)) < 0)
    {
        LOGD("avformat_open_input failed %s", av_err2str(res));
        return;
    }

    if (avformat_find_stream_info(pFormatCxt, 0) < 0)
    {
        LOGD("avformat_find_stream_info failed");
        return;
    }

    for (int i = 0; i < pFormatCxt->nb_streams; ++i) {
        if (pFormatCxt->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            if (pAudio == NULL)
            {
                pAudio = new Audio();
                pAudio->audioIndex = i;
                pAudio->pCodecPrm = pFormatCxt->streams[i]->codecpar;
            }
            break;
        }
    }

    if (-1 == pAudio->audioIndex)
    {
        LOGD("audioIndex is -1");
        return;
    }
    LOGD("audioIndex is %d", pAudio->audioIndex);

    pCodec = avcodec_find_decoder(pAudio->pCodecPrm->codec_id);
    if (pCodec == NULL)
    {
        LOGD("avcodec_find_decoder failed");
        return;
    }
    pCodecCxt = avcodec_alloc_context3(pCodec);
    avcodec_parameters_to_context(pCodecCxt, pAudio->pCodecPrm);

    if (avcodec_open2(pCodecCxt, pCodec, 0) != 0)
    {
        LOGD("avcodec_open2 failed");
        return;
    }

    LOGD("avcodec_open2 success");

    javaMethod->onCallPrepared(1);
}

void FFmpeg::start() {
    if (pAudio == NULL)
    {
        return;
    }
    AVPacket pkt;
//    AVFrame *frame = av_frame_alloc();

    int count = 0;
    int res = 0;
    while (1)
    {
        if (av_read_frame(pFormatCxt, &pkt) == 0)
        {
            if (pkt.stream_index == pAudio->audioIndex)
            {
                LOGD("播放当前帧 %d", count++);
            }

        } else
        {
            av_packet_unref(&pkt);
            break;
        }

        av_packet_unref(&pkt);

    }

//    av_packet_free(pkt);

    LOGD("start finished");

}
