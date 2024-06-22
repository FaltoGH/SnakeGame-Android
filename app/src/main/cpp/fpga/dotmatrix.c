#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/mman.h>
#include <android/log.h>
#include <errno.h>

JNIEXPORT jint JNICALL
Java_com_yangdai_snakegame_fpga_DotMatrix_DotMatrixControl(
        JNIEnv* env, jobject thiz, jstring data)
{
    const char*buf;
    int dev,ret, len;
    char str[100];

    buf = (*env)->GetStringUTFChars(env, data, 0);
    len = (*env)->GetStringLength(env, data);

    dev = open("/dev/fpga_dotmatrix", O_RDWR|O_SYNC);

    if(dev != -1){
        ret = write(dev, buf, len);
        close(dev);
    }else{
        __android_log_print(ANDROID_LOG_ERROR, "dotmatrix.c", "Device Open ERROR!\n");
        return 1;
    }

    return 0;
}
