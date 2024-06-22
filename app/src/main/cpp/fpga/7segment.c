//
// Created on 2024-06-18.
//

#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/mman.h>
#include <android/log.h>

jint
Java_com_yangdai_snakegame_fpga_Segment_writeString(JNIEnv* env,
                                                    jobject thiz, jstring data){
    int dev, ret;
    dev = open("/dev/fpga_segment", O_RDWR|O_SYNC);

    if(dev != -1){

        const char *nativeString = (*env)->GetStringUTFChars(env, data, 0);

        // use your string
        ret = write(dev, nativeString, 6);
        close(dev);

        (*env)->ReleaseStringUTFChars(env, data, nativeString);

    } else{
        __android_log_print(ANDROID_LOG_ERROR, "7segment.c", "Device Open ERROR!\n");
        return 1;
    }
    return 0;
}

jint
Java_com_yangdai_snakegame_fpga_Segment_writeInt(JNIEnv* env,
                                                 jobject thiz, jint data){
    int dev, ret;
    dev = open("/dev/fpga_segment", O_RDWR|O_SYNC);

    if(dev != -1){

        char str[7];
        sprintf(str, "%06d", data);

        ret = write(dev, str, 6);
        close(dev);

    } else{
        __android_log_print(ANDROID_LOG_ERROR, "7segment.c", "Device Open ERROR!\n");
        return 1;
    }
    return 0;
}
