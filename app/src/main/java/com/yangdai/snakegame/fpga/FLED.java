package com.yangdai.snakegame.fpga;

import android.util.Log;

import com.yangdai.snakegame.lang.DaemonThread;


public class FLED extends DaemonThread {

    static{
        Keypad.loadLib();
    }

/*
#define FULL_LED1 9
#define FULL_LED2 8
#define FULL_LED3 7
#define FULL_LED4 6
#define ALL_LED   5
*/
    public static final int FULL_LED1 = 9;
    public static final int FULL_LED2 = 8;
    public static final int FULL_LED3 = 7;
    public static final int FULL_LED4 = 6;
    public static final int ALL_LED = 5;

    /** @param red 0x0~0x100 (9 bit)
     *  @param green 0x0~0x100 (9 bit)
     *  @param blue 0x0~0x100 (9 bit)
     *  */
    public static native int FLEDControl(int led_num, int red, int green, int blue);

    public static int off(){
        return FLEDControl(ALL_LED, 0, 0, 0);
    }

    public int FLEDControl_t(int led_num, int red, int green, int blue){
        int ret = FLEDControl(led_num, red, green, blue);
        if(ret == 0){
            hastooff = true;
        }
        return ret;
    }

    private volatile boolean hastooff;

    @Override
    public void run() {
        while(true){

            if(hastooff){
                hastooff = false;
                try {
                    sleep(1000);
                } catch (InterruptedException e) {
                    return;
                }
                if(!hastooff){
                    off();
                }
            }

            try {
                sleep(1000);
            } catch (InterruptedException e) {
                return;
            }

        }
    }
}
