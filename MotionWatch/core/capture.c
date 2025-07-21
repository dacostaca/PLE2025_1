#include "capture.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int capturar_frame(const char* filename) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd),
             "ffmpeg -y -loglevel error -f v4l2 -video_size 640x480 -i /dev/video0 -frames 1 %s",
             filename);

    int ret = system(cmd);
    if (ret != 0) {
        fprintf(stderr, "Error capturando frame: %s\n", filename);
        return -1;
    }
    return 0;
}
