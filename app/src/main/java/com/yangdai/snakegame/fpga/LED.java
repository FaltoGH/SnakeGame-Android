package com.yangdai.snakegame.fpga;


public class LED {

    static {
        Keypad.loadLib();
    }

    public static native int on();
    public static native int off();
    public static native int set(int value);



}
