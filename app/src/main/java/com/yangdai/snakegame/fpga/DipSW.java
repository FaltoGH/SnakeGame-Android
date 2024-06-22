package com.yangdai.snakegame.fpga;

import android.util.Log;

import com.yangdai.snakegame.lang.DaemonThread;

public class DipSW extends DaemonThread {
    static{
        Keypad.loadLib();
    }

    private final DipSWHandler handler;

    public static native int GetValue();

    public int currentValue;

    public DipSW(DipSWHandler handler){
        this.handler = handler;
    }

    public interface DipSWHandler{
        int handle(int x);
    }

    @Override
    public void run() {
        currentValue = GetValue();

        while(true) {
            int newValue = GetValue();
            if(currentValue != newValue){
                currentValue = newValue;

                Log.d("DipSW", "dip switch value="+currentValue);

                if(handler.handle(newValue) != 0){
                    return;
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
