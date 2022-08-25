#include <stdio.h>
#include <iio.h>
#include <byteswap.h>
#include <time.h>

struct iio_context *ctx = NULL;
struct iio_device  *dev = NULL;
struct iio_buffer  *buf = NULL;
struct iio_channel  *ch[4];

#define THRESH 250
#define URI "ip:10.76.84.212"
#define DEVICE_NAME "ad5592r"

int main() {
    ctx = iio_create_context_from_uri(URI);
    if (ctx == NULL) {
        printf("No context\n");
        return -1;
    }

    dev = iio_context_find_device(ctx, DEVICE_NAME);
    if (dev == NULL) {
        printf("No device\n");
        return -2;
    }


    for(int i =0;i < 4; i++) {
        ch[i] = iio_device_get_channel(dev, i);
        iio_channel_enable(ch[i]);
    }


    buf = iio_device_create_buffer(dev, 100, false);
    if (buf == NULL) {
        printf("No buffer created\n");
        return -3;
    }

    int x,y,prevx,prevy;
    int eventX, eventY;
    bool first = true;
    bool trigger = false;

    while(1) {
        iio_buffer_refill(buf);
            trigger = false;
        for (char *ptr = iio_buffer_start(buf);
             ptr < iio_buffer_end(buf);
             ptr += iio_buffer_step(buf)) {

        int16_t values[4];

        values[0] = *(int16_t*)(ptr);
        values[1] = *(int16_t*)(ptr+2);
        values[2] = *(int16_t*)(ptr+4);
        values[3] = *(int16_t*)(ptr+6);

        prevx = x;
        prevy = y;
        x = values[0] - values[1];
        y = values[2] - values[3];

        //printf("%d %d %d %d\n" ,prevx,prevy,x,y );
        if(first) {
            first = false;
            continue;
        }
        if(abs(x-prevx) > THRESH || abs(y-prevy)>THRESH) {
            eventX = abs(x-prevx);
            eventY = abs(y-prevy);

            trigger = true;

        }

        }
        if(trigger) {
                    time_t t = time(NULL);
                    struct tm tm = *localtime(&t);
                    printf("now: %d-%02d-%02d %02d:%02d:%02d: ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                    printf("Accelerometer Event: X:%5d Y:%5d\n", eventX, eventY);
                    fflush(stdout);
    }
    }

    iio_buffer_destroy(buf);
    return 0;
}
