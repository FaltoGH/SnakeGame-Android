#include <jni.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include "idev.h"

#ifdef __cplusplus
extern "C"{
#endif

JNIEXPORT jstring JNICALL Java_com_yangdai_snakegame_fpga_Keypad_idev(
        JNIEnv *env,
        jclass jc) {

    auto devices = idev::get_devices();

    const std::string fpga_keypad = "\"fpga-keypad\"";
    const std::string EVENT = "event";

    for (const auto &k: devices) {
        if(k.N.compare(fpga_keypad) == 0){
            std::string eventname = k.get_handler_starting_with(EVENT);
            return env->NewStringUTF(eventname.c_str());
        }
    }

    return NULL;
}

#ifdef __cplusplus
}
#endif
