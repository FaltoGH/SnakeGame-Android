package com.yangdai.snakegame.fpga;


public class LED {

    static {
        Keypad.loadLib();
    }

    public static native int on();

    public static native int off();

    public static native int set(int value);

    public static int fill(int x){
        if(x < 0){
            x = 0;
        }
        else if(x > 8){
            // The number of LEDs is eight.
            x = 8;
        }

        int y = 0;
        for(;x>0;x--){
            y <<= 1;
            y += 1;
        }

        return set(y);
    }

}
