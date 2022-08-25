#include <stdio.h>
#include <iio.h>
#include <unistd.h>
#include <time.h>

struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
struct iio_channel *ch[4];
struct iio_buffer *buf = NULL;

#define URI             "ip:10.76.84.212"
#define DEVICE_NAME     "ad5592r"
#define SAMPLES_COUNT   100
#define THRESH          250

int sample = 0;

int main()
{
    ctx = iio_create_context_from_uri(URI);

    if(ctx == NULL)
    {
        printf("No context\n\n");
        return -1;
    }

    dev = iio_context_find_device(ctx, DEVICE_NAME);

    if(dev == NULL)
    {
        printf("No device\n\n");
        return -2;
    }

    printf("Got device %s %lx\n\n", DEVICE_NAME, dev);

    unsigned int chan_count = iio_device_get_channels_count(dev);

    int i;

    for(i = 0; i < chan_count; i++)
    {
        ch[i] = iio_device_get_channel(dev, i);

        if(ch[i] == NULL)
        {
            printf("Channel not found\n\n");
            return -1;
        }

        iio_channel_enable(ch[i]);

        printf("Got channel %s %lx\n\n", iio_channel_get_id(ch[i]), ch[i]);
    }

    buf = iio_device_create_buffer(dev, SAMPLES_COUNT, false);

    if(buf == NULL)
    {
        printf("Buffer creation failed\n");
        return -1;
    }

    int bufSize;
    bufSize = iio_buffer_refill(buf);

    if(bufSize != (chan_count * SAMPLES_COUNT * 2))
    {
        printf("Sample fetching from buffer failed\n");
        return -1;
    }

    printf("Fetched samples from %s\n\n", DEVICE_NAME);

    int x;
    int y;
    int prevx;
    int prevy;
    int eventX, eventY;

    bool first = true;
    bool trigger = true;

    char *ptr;

    while(true)
    {
        iio_buffer_refill(buf);

        trigger = false;

        for(ptr = iio_buffer_start(buf); ptr < iio_buffer_end(buf); ptr = ptr + iio_buffer_step(buf))
        {
            int16_t values[4];

            values[0] = *(int16_t*)(ptr);
            values[1] = *(int16_t*)(ptr + 2);
            values[2] = *(int16_t*)(ptr + 4);
            values[3] = *(int16_t*)(ptr + 6);

            prevx = x;
            prevy = y;
            x = values[0] - values[1];
            y = values[2] - values[3];

            if(first)
            {
                first = false;
                continue;
            }

            if(abs(x - prevx) > THRESH || abs(y - prevy) > THRESH)
            {
                eventX = abs(x - prevx);
                eventY = abs(y - prevy);

                trigger = true;
            }
        }

        if(trigger)
        {
            time_t t = time(NULL);

            struct tm tm = *localtime(&t);

            printf("now: %d-%02d-%02d %02d:%02d:%02d: ", tm.tm_year + 1900,
                   tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
            printf("Accelerometer Event: X:%5d Y:%5d\n", eventX, eventY);
        }
    }

    iio_buffer_destroy(buf);

    return 0;
}
