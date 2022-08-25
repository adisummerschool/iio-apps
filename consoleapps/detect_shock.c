#include<stdio.h>
#include<iio.h>
#include<unistd.h>
#include <byteswap.h>
#include <time.h>

#define IP_ADDR "ip:10.76.84.219"
#define DEVICE_NAME "iio-ad5592r"
#define ATTR_RAW "raw"
#define SAMPLES_COUNT 5


#define THRESH 250

struct iio_context *ctx   = NULL;
struct iio_device *dev = NULL;
struct iio_buffer *buffer=NULL;


int main(){

    ctx = iio_create_context_from_uri(IP_ADDR);
    if (!ctx){
        printf("No context!\n");
        return -1;
    }


    dev = iio_context_find_device(ctx, DEVICE_NAME);
    if(!dev){
        printf("No device found!\n");
        return -1;
    }

    int nr_of_channels = iio_device_get_channels_count(dev);
    struct iio_channel *chan[nr_of_channels];
    for(int i = 0; i < nr_of_channels; i++){

        chan[i] = iio_device_get_channel(dev, i);
        if(!chan[i]){
            printf("No channels found!\n");
            return -1;
        }
        iio_channel_enable(chan[i]);
    }

    buffer = iio_device_create_buffer(dev, SAMPLES_COUNT, false);//creates buffer on target
    if (buffer == NULL) {
        printf("No buffer created\n");
        return -3;
    }

    int x=0, y=0, prevx, prevy;
    int eventX, eventY;
    bool first=true;
    bool trigger = false;
    while(1) {
        iio_buffer_refill(buffer);
        trigger = false;
        for (char *ptr = iio_buffer_start(buffer);
             ptr < iio_buffer_end(buffer);
             ptr += iio_buffer_step(buffer)) {

            int16_t values[4];

            values[0] = *(int16_t*)(ptr);
            values[1] = *(int16_t*)(ptr+2);
            values[2] = *(int16_t*)(ptr+4);
            values[3] = *(int16_t*)(ptr+6);

            prevx = x;
            prevy = y;
            x = values[0] - values[1];
            y = values[2] - values[3];

            //printf("%d %d\n" ,x,y );
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
        }
    }


    iio_buffer_destroy(buffer);
    return 0;
}




