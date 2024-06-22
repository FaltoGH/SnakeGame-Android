//
// Created on 2024-06-19.
//
#include <jni.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define LED "/dev/fpga_led"

JNIEXPORT jint JNICALL Java_com_yangdai_snakegame_fpga_LED_on
        (JNIEnv *env, jobject obj) {
    int fd;
    fd = open(LED, O_RDWR);
    if (fd < 0)
        return -errno;

    unsigned short data = 0xff;
    write(fd, &data, 1);
    close(fd);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_yangdai_snakegame_fpga_LED_off
        (JNIEnv *env, jobject obj){
    int fd;
    fd = open(LED, O_RDWR);
    if (fd < 0)
        return -errno;

    unsigned short data = 0x00;
    write(fd, &data, 1);
    close(fd);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_yangdai_snakegame_fpga_LED_set
        (JNIEnv *env, jobject obj, jint x){
    int fd;
    fd = open(LED, O_RDWR);
    if (fd < 0)
        return -errno;

    int data = 0xff & x;
    write(fd, &data, 1);
    close(fd);
    return 0;
}


