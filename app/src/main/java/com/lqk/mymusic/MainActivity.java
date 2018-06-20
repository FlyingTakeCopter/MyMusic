package com.lqk.mymusic;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.lqk.libmyplayer.JniTest;

public class MainActivity extends AppCompatActivity {

    JniTest jniTest;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jniTest = new JniTest();
        jniTest.testJni();
    }

}
