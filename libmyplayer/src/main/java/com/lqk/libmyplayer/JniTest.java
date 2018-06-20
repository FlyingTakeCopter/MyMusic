package com.lqk.libmyplayer;

/**
 * Created by liuqikang on 2018/6/21.
 */

public class JniTest {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public native void testJni();
}
