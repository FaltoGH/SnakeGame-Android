#include <jni.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define OLED "/dev/fpga_oled"

//ioctl cmd
enum{
    OLED_INIT=0x10, MENU_PRINT, WIN_CLEAR, IMAGE_DRAW,
    RECT_DRAW, LINE_DRAW, CIRCLE_DRAW, TEXT_PRINT
} IOCTL_CMD;

// Clear area
struct cmd_clear_value{
    unsigned short sx; // start x, y
    unsigned short sy;
    unsigned short ex; // end x, y
    unsigned short ey;
};

// Return a nonnegative int on success, negative int on error.
int OLEDImage(int *data, int width, int height){
    int fd, ret;
    unsigned short buf[128*128];
    int i, j;
    unsigned short r = 0, g = 0, b = 0;
    int temp;

    fd = open(OLED, O_WRONLY|O_NDELAY);
    if(fd < 0) return -errno;

    for (i=0;i<128*128;i++) buf[i] = 0xffff; // initialize to white

    for (i=0; i < 128*128; i++){
        temp = data[i];
        b = (unsigned short)((temp & 0x000000FF) >> 3);
        g = (unsigned short)((temp & 0x0000FF00) >> 5);
        r = (unsigned short)((temp & 0x00FF0000) >> 8);
        buf[i] = ((r&0xf800) | (g&0x07e0) | (b&0x001f));
    }

    ret = write (fd, buf, 128*128*2);
    close(fd);

    if (ret > 0) return ret;
    return -1;
}

JNIEXPORT jint JNICALL Java_com_yangdai_snakegame_fpga_OLED_OLEDImage
(JNIEnv *env, jclass thiz, jintArray image, int width, int height){
    int *data;

    data = (int*) (*env)->GetIntArrayElements(env, image, 0);
    int ret = OLEDImage(data, width, height);

    (*env)->ReleaseIntArrayElements(env, image, data, 0);

    return ret;
}
