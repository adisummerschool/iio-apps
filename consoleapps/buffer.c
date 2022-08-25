#include <stdio.h>
#include <unistd.h>
#include <iio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define NULL        0
#define THRESH      250

#define URI         "ip:10.76.84.217"
#define DEV_NAME    "ad5592r"

struct iio_context  *ctx;
struct iio_device   *dev;
struct iio_channel  *ch[4];
struct iio_buffer   *buffer;

int main() {

    //Assigning the context and the device
    ctx = iio_create_context_from_uri(URI);
    if(ctx == NULL){
            printf("Specified context does not exist\n");
            return -1;
    }
    uint attr_count = iio_context_get_attrs_count(ctx);
    const char *attr_name;
    const char *attr_value;

    dev = iio_context_find_device(ctx, DEV_NAME);
    if(dev == NULL){
        printf("Could not find specified device");
        return -2;
    }

    //Assigning the channels in the channel array
    uint chan_count = iio_device_get_channels_count(dev);
    for(uint i = 0; i < chan_count; i++){
        ch[i] = iio_device_get_channel(dev, i);
        if(ch[i] == NULL){
            printf("Channel %d does not exist", i);
            return -1;
        }
        iio_channel_enable(ch[i]);
    }

    //Assigning the buffer
    buffer = iio_device_create_buffer(dev, 100, 0);
    if(buffer==NULL) {
        printf("No buffer created\n");
        return -3;
    }

    printf("Context attributes:\n-------------------\n");
    for(uint i = 0; i < attr_count; i++){
        iio_context_get_attr(ctx, i, &attr_name, &attr_value);
        printf("%s: %s\n", attr_name, attr_value);
    }

    int x,y,prevx,prevy;
    int eventX, eventY;
    _Bool first = 1;
    _Bool trigger = 0;
    while(1) {
        iio_buffer_refill(buffer);
        trigger = 0;
        for (char *ptr = iio_buffer_start(buffer);
             ptr < iio_buffer_end(buffer);
             ptr += iio_buffer_step(buffer)) {

            int16_t values[4];

            values[0] = *(int16_t *)(ptr);
            values[1] = *(int16_t *)(ptr+2);
            values[2] = *(int16_t *)(ptr+4);
            values[3] = *(int16_t *)(ptr+6);

            prevx = x;
            prevy = y;
            x = values[0] - values[1];
            y = values[2] - values[3];

            if(first) {
                first = 0;
                continue;
            }
            if(abs(x-prevx) > THRESH || abs(y-prevy)>THRESH) {
                eventX = abs(x-prevx);
                eventY = abs(y-prevy);

                trigger = 1;
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


    iio_buffer_destroy(buffer);
    return 0;

    return 0;
}
