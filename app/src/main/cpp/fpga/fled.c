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

#define FULL_LED1 9
#define FULL_LED2 8
#define FULL_LED3 7
#define FULL_LED4 6
#define ALL_LED   5

// Return value is zero if success, negative integer if error.
JNIEXPORT jint JNICALL
Java_com_yangdai_snakegame_fpga_FLED_FLEDControl(JNIEnv* env, jobject thiz,
jint led_num, jint val1, jint val2, jint val3){
    int fd, ret;
    char buf[3];
    fd = open("/dev/fpga_fullcolorled", O_WRONLY);
    if(fd<0){
        return -errno;
    }
    ret = (int)led_num;
    if(5 <= ret && ret <= 9){
        ioctl(fd, ret);
    }
    buf[0] = val1;
    buf[1] = val2;
    buf[2] = val3;

    write(fd, buf, 3);

    close(fd);

    return 0;
}