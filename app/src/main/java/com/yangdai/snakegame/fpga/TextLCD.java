package com.yangdai.snakegame.fpga;


public class TextLCD{

    static {
        Keypad.loadLib();

        disp = true; cursor = false; blink = false;

        IOCtlClear();
        IOCtlReturnHome();
        IOCtlDisplay(true);
        IOCtlCursor(false);
        IOCtlBlink(false);

        ret = TextLCDOut(" HANBACK ", " Electronics! ");
    }

    public static native int TextLCDOut(String str, String str2);

    public static native int IOCtlClear();

    public static native int IOCtlDisplay (boolean data);

    public static native int IOCtlReturnHome ();

    public static native int IOCtlCursor(boolean data);

    public static native int IOCtlBlink(boolean data);

    public static native int write(String x);

    private static int ret;
    private static boolean disp, cursor, blink;
}
