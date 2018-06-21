package com.lqk.mymusic;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.lqk.libmyplayer.JniTest;
import com.lqk.libmyplayer.listener.LqkOnPreparedListener;
import com.lqk.libmyplayer.log.MyLog;
import com.lqk.libmyplayer.player.LqkPlayer;

public class MainActivity extends AppCompatActivity {

//    JniTest jniTest;
    LqkPlayer lqkPlayer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        jniTest = new JniTest();
//        jniTest.testJni();
        lqkPlayer = new LqkPlayer();
        lqkPlayer.setLqkOnPreparedListener(new LqkOnPreparedListener() {
            @Override
            public void onPrepared() {
                MyLog.d("prepared finished");
                lqkPlayer.n_start();
            }
        });
        begin();
    }

    void begin(){
        lqkPlayer.setSource("sdcard/ffmpegtest/audio.mp3");
        lqkPlayer.prepared();
    }
}
