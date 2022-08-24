#include <stdio.h>
#include <iio.h>
#include <byteswap.h>

#define URI "ip:10.76.84.212"
#define DEVICE_NAME "ad5592r"

struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
struct iio_channel *ch[4];
struct iio_buffer *buf = NULL;

#define THRESH 40

unsigned createMask(unsigned a, unsigned b)
{
    unsigned r = 0;
    for (unsigned i=a; i<=b; i++)
        r |= 1 << i;

    return r;
}

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

    buf = iio_device_create_buffer(dev, 100, false);
    if(buf == NULL) {
        printf("Could not create buffer\n");
        return -1;
    }

        int nr_bytes;
        nr_bytes = iio_buffer_refill(buf);
        if(nr_bytes < 0)
            printf("Error refilling buf %d\n", nr_bytes);
        else printf("The nr of bytes is %d\n", nr_bytes);

        int x,y,prevx,prevy;
            bool first=true;
            while(1) {
            for (char *ptr = iio_buffer_start(buf);
                 ptr < iio_buffer_end(buf);
                 ptr += iio_buffer_step(buf)) {

                int16_t values[4];
                int16_t* ptrs[4];

                ptrs[0] = (int16_t*)(ptr);
                ptrs[1] = (int16_t*)(ptr+2);
                ptrs[2] = (int16_t*)(ptr+4);
                ptrs[3] = (int16_t*)(ptr+6);

                values[0] = *ptrs[0];
                values[1] = *ptrs[1];
                values[2] = *ptrs[2];
                values[3] = *ptrs[3];

                prevx = x;
                prevy = y;
                x = values[0] - values[1];
                y = values[2] - values[3];

        //		printf("%d %d %d %d\n" ,prevx,prevy,x,y );
                if(first) {
                    first = false;
                    continue;
                }
                if(abs(x-prevx) > THRESH || abs(y-prevy)>THRESH) {

                    printf("HERE");
                }

            }
            }

        iio_buffer_destroy(buf);

    return 0;
}
