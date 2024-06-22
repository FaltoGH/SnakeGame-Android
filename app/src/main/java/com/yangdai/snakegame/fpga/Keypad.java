package com.yangdai.snakegame.fpga;

import android.util.Log;

import com.yangdai.snakegame.lang.DaemonThread;

import java.io.DataOutputStream;
import java.util.Objects;

public class Keypad extends DaemonThread {
    public static void loadLib(){
        System.loadLibrary("snakegame");
    }
    static {
        loadLib();
    }


    private static native String read(String event);

    private static native String idev();

    private static String getEventName() {
        return idev();
    }

    private static String eventName;

    public static String read() {
        if (eventName == null) {
            eventName = getEventName();
            if (eventName == null) {
                eventName = "null";
            }
        }

        if (!eventName.equals("null")) {
            return read(eventName);
        }
        return null;
    }

    public interface KeypadHandler{
        int handle(int x);
    }

    KeypadHandler handler;

    public Keypad(KeypadHandler handler){
        this.handler = handler;
    }

    @Override
    public void run() {
        if(chmod777() != 0){
            return;
        }

        while (true) {
            try {
                sleep(1);
            } catch (InterruptedException e) {
                return;
            }

            String keypadInput = read();
            if (keypadInput == null) {
                Log.e("keypad", "keypad input is null");
                return;
            }

            if (keypadInput.length() > 1) {
                Log.e("keypad", "too long keypad input. input="+keypadInput);
                return;
            }

            int iinput = sInputToInt(keypadInput);
            if(iinput == -1){
                Log.e("keypad", "Unknown keypad input:\""+keypadInput+"\"");
                return;
            }

            Log.d("keypad", "keypad input="+iinput);

            if (handler.handle(iinput) != 0) {
                return;
            }
        }
    }

    static boolean mod_changed;
    public static int chmod777() {
        try {
            if(!mod_changed) {
                Process p = Runtime.getRuntime().exec("su");
                DataOutputStream os = new DataOutputStream(p.getOutputStream());
                os.writeBytes("chmod 777 /dev/input/*\n");
                os.writeBytes("chmod 777 /dev/*\n");
                os.writeBytes("exit\n");
                os.flush();
                os.close();
                p.waitFor();
                mod_changed = true;
            }
        }
        catch(Exception ex){
            Log.e("chmod", ex.toString());
            return 1;
        }
        return 0;
    }

    private static int sInputToInt(String key){
        // 1 2 3 ?
        // 4 5 6 ?
        // 7 8 9 ?
        // ? 0 ? 10

        switch (key) {
            case "1":
                return 1;
            case "2":
                return 2;
            case "3":
                return 3;
            case "4":
                return 4;
            case "5":
                return 5;
            case "6":
                return 6;
            case "7":
                return 7;
            case "8":
                return 8;
            case "9":
                return 9;
            case ":":
                return 0;
            case "=":
                return 10;
        }
        return -1;
    }

}
