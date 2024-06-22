package com.yangdai.snakegame.fpga;

import android.util.Log;

import com.yangdai.snakegame.lang.DaemonThread;

public class Segment extends DaemonThread {

    static {
        Keypad.loadLib();
    }

    public static native int writeInt(int value);

    public int value = -1;
    public boolean enable = true;

    @Override
    public void run(){
            while(true) {
                if(0 <= value && value <= 999999 && enable) {

                    if (Segment.writeInt(value) != 0) {

                        try {
                            sleep(1000);
                        } catch (InterruptedException e) {
                            return;
                        }

                    }

                }

                try {
                    sleep(1);
                } catch (InterruptedException e) {
                    return;
                }

            }
    }

}
