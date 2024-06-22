package com.yangdai.snakegame.fpga;

public class DipSW {
    static{
        Keypad.loadLib();
    }

    public static native int GetValue();
}
