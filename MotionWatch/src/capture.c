#include "capture.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int capturar_frame(void) {
    time_t ahora = time(NULL);
    struct tm *tm_info = localtime(&ahora);
    char filename[128];

    strftime(filename, sizeof(filename), "frames/frame_%Y%m%d_%H%M%S.jpg", tm_info);

    char cmd[256];
    snprintf(cmd, sizeof(cmd),
             "ffmpeg -y -f v4l2 -video_size 640x480 -i /dev/video0 -frames 1 %s > /dev/null 2>&1",
             filename);

    return system(cmd);
}
