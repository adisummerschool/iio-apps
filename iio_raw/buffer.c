#include <stdio.h>
#include <iio.h>
#include <unistd.h>

struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
struct iio_channel *ch[4];
struct iio_buffer *buf = NULL;

#define URI             "ip:10.76.84.212"
#define DEVICE_NAME     "ad5592r"
#define SAMPLES_COUNT   100

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
        return -1;
    }

    printf("Got device %s %lx\n\n", DEVICE_NAME, dev);

    unsigned int chan_count = iio_device_get_channels_count(dev);

    int values[4];
    int i;

    for(i = 0; i < chan_count; i++)
    {
        ch[i] = iio_device_get_channel(dev, i);

        if(ch[i] == NULL)
        {
            printf("Channel not found\n\n");
            return -1;
        }

        printf("Got channel %s %lx\n", iio_channel_get_id(ch[i]), ch[i]);
    }
    printf("\n");

    for(i = 0; i < chan_count; i++)
    {
        iio_channel_enable(ch[i]);
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

    void *ptr;

    for(i = 0; i< chan_count; i++)
    {
        for(ptr = iio_buffer_first(buf, ch[i]); ptr < iio_buffer_end(buf); ptr = ptr + iio_buffer_step(buf))
        {

        }
    }

    iio_buffer_destroy(buf);

    return 0;
}
