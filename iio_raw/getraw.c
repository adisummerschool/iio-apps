#include <stdio.h>
#include <iio.h>
#include <unistd.h>

struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
struct iio_channel *ch[4];

#define URI         "ip:10.76.84.212"
#define DEVICE_NAME "ad5592r"

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

    while(true)
    {
        printf("Sample %d\n", sample);
        for(i = 0; i < chan_count; i++)
        {
            char buf[10];
            iio_channel_attr_read(ch[i], "raw", &buf, 10);
            values[i] = atoi(buf);
            printf("The value: %lld\n", values[i]);
        }

        int x = values[0] - values[1];
        int y = values[2] - values[3];

        printf("x = %d\ny = %d\n\n", x, y);

        sample++;

        fflush(stdout);
        usleep(500 * 1000);
    }



    return 0;
}
