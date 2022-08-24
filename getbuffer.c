#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.212"
#define DEVICE_NAME "ad5592r"

struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
struct iio_channel *ch[4];
struct iio_buffer *buf = NULL;

int main() {

    ctx = iio_create_context_from_uri("ip:10.76.84.212");
    if(ctx == NULL) {
        printf("No context\n");
        return -1;
    }

    dev = iio_context_find_device(ctx, DEVICE_NAME);
    if(dev == NULL) {
        printf("No device\n");
        return -1;
    }
    printf("Got device %s %lx\n", DEVICE_NAME, dev);

    int nr_chan;
    nr_chan = iio_device_get_channels_count(dev);
    printf("IIO device has %u channels:\n", nr_chan);

    for (int i=0; i < nr_chan; i++) {

        ch[i] = iio_device_get_channel(dev, i);
        if(ch[i] == NULL) {
            printf("Channel not found\n");
            return -1;
        }

        iio_channel_enable(ch[i]);

        printf("Got channel %s %lx\n", iio_channel_get_id(ch[i]), ch[i]);
    }

        int nr_bytes;
        buf = iio_device_create_buffer(dev, 100, false);
        nr_bytes = iio_buffer_refill(buf);
        if(nr_bytes < 0)
            printf("Not bytes found. \n");

        else
            printf("Number of bytes is %d \n", nr_bytes);

        iio_buffer_destroy(buf);

        for (void *ptr = iio_buffer_first(buf, ch[4]);
                   ptr < iio_buffer_end(buf);
                   ptr += iio_buffer_step(buf)) {
            /* Use "ptr" to read or write a sample for this channel */
            const int16_t i = ((int16_t*)ptr)[0];
            ((int16_t*)ptr)[1] = i;

        }
    return 0;
}
