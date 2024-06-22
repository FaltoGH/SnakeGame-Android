#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/mman.h>
#include <errno.h>
#include <android/log.h>

#define TEXTLCD "/dev/fpga_textlcd"
#define TEXTLCD_BASE            0xbc
#define TEXTLCD_COMMAND_SET     _IOW(TEXTLCD_BASE, 0, int)
#define TEXTLCD_FUNCTION_SET    _IOW(TEXTLCD_BASE, 1, int)
#define TEXTLCD_DISPLAY_CONTROL _IOW(TEXTLCD_BASE, 2, int)
#define TEXTLCD_CURSOR_SHIFT    _IOW(TEXTLCD_BASE, 3, int)
#define TEXTLCD_ENTRY_MODE_SET  _IOW(TEXTLCD_BASE, 4, int)
#define TEXTLCD_RETURN_HOME     _IOW(TEXTLCD_BASE, 5, int)
#define TEXTLCD_CLEAR           _IOW(TEXTLCD_BASE, 6, int)
#define TEXTLCD_DD_ADDRESS      _IOW(TEXTLCD_BASE, 7, int)
#define TEXTLCD_WRITE_BYTE      _IOW(TEXTLCD_BASE, 8, int)

struct strcommand_variable{
    char rows;
    char nfonts;
    char display_enable;
    char cursor_enable;

    char nblink;
    char set_screen;
    char set_rightshit;
    char increase;
    char nshift;
    char pos;
    char command;
    char strlength;
    char buf[16];
};

static struct strcommand_variable strcommand;
static int initialized = 0;

void initialize(){
    if (!initialized){
        strcommand.rows = 0;
        strcommand.nfonts = 0;
        strcommand.display_enable = 1;
        strcommand.cursor_enable = 0;
        strcommand.nblink = 0;
        strcommand.set_screen = 0;
        strcommand.set_rightshit = 1;
        strcommand.increase = 1;
        strcommand.nshift = 0;
        strcommand.pos = 10;
        strcommand.command = 1;
        strcommand.strlength = 16;
        initialized = 1;
    }
}

int TextLCDIoctol(int cmd, char* buf){
    int fd, ret, i;

    fd = open(TEXTLCD, O_WRONLY | O_NDELAY);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "textlcd.c", "TextLCDIoctol:Device Open ERROR!\n");
        return -errno;
    }

    if (cmd == TEXTLCD_WRITE_BYTE) {
        ioctl(fd, TEXTLCD_DD_ADDRESS, &strcommand, 32);
        for (i = 0; i < strlen(buf); i++) {
            strcommand.buf[0] = buf[i];
            ret = ioctl(fd, cmd, &strcommand, 32);
        }
    }else{
        ret = ioctl(fd, cmd, &strcommand, 32);
    }

    close(fd);

    return ret;
}

JNIEXPORT jint
JNICALL Java_com_yangdai_snakegame_fpga_TextLCD_TextLCDOut
        (JNIEnv *env, jobject obj, jstring str, jstring str2) {
    jboolean iscopy;
    char *buf0, *buf1;
    int fd, ret;

    fd = open(TEXTLCD, O_WRONLY | O_NDELAY);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "textlcd.c", "TextLCDOut:Device Open ERROR!\n");
        return -errno;
    }

    initialize();

    buf0 = (char *) (*env)->GetStringUTFChars(env, str, &iscopy);
    buf1 = (char *) (*env)->GetStringUTFChars(env, str2, &iscopy);

    strcommand.pos = 0;
    ioctl(fd, TEXTLCD_DD_ADDRESS, &strcommand, 32);
    ret = write(fd, buf0, strlen(buf0));

    strcommand.pos = 40;
    ioctl(fd, TEXTLCD_DD_ADDRESS, &strcommand, 32);
    ret = write(fd, buf1, strlen(buf1));

    close(fd);

    (*env)->ReleaseStringUTFChars(env, str, buf0);
    (*env)->ReleaseStringUTFChars(env, str2, buf1);

    return ret;
}

JNIEXPORT jint
JNICALL Java_com_yangdai_snakegame_fpga_TextLCD_IOCtlClear
        (JNIEnv *env, jobject obj) {
    initialize();
    return TextLCDIoctol(TEXTLCD_CLEAR, NULL);
}

JNIEXPORT jint
JNICALL Java_com_yangdai_snakegame_fpga_TextLCD_IOCtlReturnHome
        (JNIEnv *env, jobject obj) {
    initialize();
    return TextLCDIoctol(TEXTLCD_RETURN_HOME, NULL);
}

JNIEXPORT jint
JNICALL Java_com_yangdai_snakegame_fpga_TextLCD_IOCtlDisplay
        (JNIEnv *env, jobject obj, jboolean data) {
    initialize();
    if (data) {
        strcommand.display_enable = 0x01;
    } else {
        strcommand.display_enable = 0x00;
    }
    return TextLCDIoctol(TEXTLCD_DISPLAY_CONTROL, NULL);

}

JNIEXPORT jint
JNICALL Java_com_yangdai_snakegame_fpga_TextLCD_IOCtlCursor
        (JNIEnv *env, jobject obj, jboolean data) {
    initialize();
    if (data) {
        strcommand.cursor_enable = 0x01;
    } else {
        strcommand.cursor_enable = 0x00;
    }

    return TextLCDIoctol(TEXTLCD_DISPLAY_CONTROL, NULL);
}

JNIEXPORT jint JNICALL Java_com_yangdai_snakegame_fpga_TextLCD_IOCtlBlink
        (JNIEnv *env, jobject obj, jboolean data) {
    initialize();

    if (data) {strcommand.nblink = 0x01;}
    else {strcommand.nblink = 0x00;}

    return TextLCDIoctol(TEXTLCD_DISPLAY_CONTROL, NULL);
}

JNIEXPORT jint JNICALL Java_com_yangdai_snakegame_fpga_TextLCD_write
        (JNIEnv *env, jobject obj, jstring x) {

    int fd;

    fd = open(TEXTLCD, O_WRONLY | O_NDELAY);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_ERROR, "textlcd.c", "write:Device Open ERROR!\n");
        return -errno;
    }

    const char* cx = (*env)->GetStringUTFChars(env, x, 0);

    write(fd, cx, strlen(cx));
    close(fd);

    (*env)->ReleaseStringUTFChars(env, x, cx);

    return 0;
}
