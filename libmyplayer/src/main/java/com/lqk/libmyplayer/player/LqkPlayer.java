package com.lqk.libmyplayer.player;

import android.text.TextUtils;

import com.lqk.libmyplayer.listener.LqkOnPreparedListener;
import com.lqk.libmyplayer.log.MyLog;

/**
 * Created by liuqikang on 2018/6/21.
 */

public class LqkPlayer {
    static {
        System.loadLibrary("native-lib");
    }

    LqkOnPreparedListener lqkOnPreparedListener;

    public void setLqkOnPreparedListener(LqkOnPreparedListener lqkOnPreparedListener) {
        this.lqkOnPreparedListener = lqkOnPreparedListener;
    }

    private String source;
    // 设置路径（本地/网络）
    public void setSource(String path){
        source = path;
    }
    // 准备播放器
    public void prepared(){
        if (TextUtils.isEmpty(source)){
            MyLog.d("source is empty");
            return;
        }
    }

    public void onCallPrepared(){
        if (lqkOnPreparedListener != null){
            lqkOnPreparedListener.onPrepared();
        }
    }

    public native void n_prepared(String source);
}
