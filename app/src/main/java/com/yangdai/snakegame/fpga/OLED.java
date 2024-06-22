package com.yangdai.snakegame.fpga;

import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Handler;
import android.util.Log;

public class OLED extends Activity {

    static{
        Keypad.loadLib();
    }

    public static native int OLEDImage(int[] image, int width, int height);

    private static java.io.InputStream is0;

    private static Bitmap bm;

    private static int[] pixels;

    private static int width, height;

    public static int displayImage(Context context, int x) {
        // Draw Picture
        Resources resources = context.getResources();
        is0 = resources.openRawResource(x);

        bm = BitmapFactory.decodeStream(is0);

        // create a deep copy of it using getPixels() into different configs
        width = bm.getWidth();
        height = bm.getHeight();
        pixels = new int[width * height];
        bm.getPixels(pixels, 0, width, 0, 0, width, height);

        //java.lang.RuntimeException: Can't create handler inside thread that has not called Looper.prepare()
        Handler mHandle = new Handler();

        mHandle.postDelayed(new Runnable() {
            @Override
            public void run() {
                int ret = OLEDImage(pixels, width, height);
                if(ret < 0){
                    Log.e("OLED", "OLEDImage()="+ ret);
                }
                else{
                    Log.d("OLED", "OLEDImage()="+ ret);
                }
            }
        }, 1000);

        Log.d("OLED", "displayImage() done");
        return 0;
    }

}
