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
        MyLog.d(source);

        new Thread(new Runnable() {
            @Override
            public void run() {
                n_prepared(source);
            }
        }).start();
    }

    public void start(){
        if (TextUtils.isEmpty(source)){
            MyLog.d("source is empty");
            return;
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                n_start();
            }
        }).start();
    }

    public void onCallPrepared(){
        MyLog.d("onCallPrepared in");

        if (lqkOnPreparedListener != null){
            lqkOnPreparedListener.onPrepared();
        }else{
            MyLog.d("lqkOnPreparedListener is NULL");
        }
    }

    public native void n_prepared(String source);

    public native void n_start();
}
