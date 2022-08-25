#include <stdio.h>
#include <iio.h>
#include <pthread.h>
#include <unistd.h>

struct iio_context *ctx = 0;
struct iio_device *dev = 0;

int run = 1;
int stop = 0;
int slow_down = 0;
int delay = 0;
int display = 1;

#define URI "ip:10.76.84.219"
#define DEV_NAME "iio-ad5592r"

#define TRESHOLD 250

void *exec() {
    while (run) {
        char c = getchar();
        if (c == 'x') {
            stop = 1;
            run = 0;
        }
        else if (c == 'f') {
            if (delay > 0) {
                delay -= 100000;
            }
        }
        else if (c == 's') {
            delay += 100000;
        }
        else if (c == 'c') {
//            display = 0;
        }
    }
    return 0;
}

int main() {
    ctx = iio_create_context_from_uri(URI);
    if (ctx == 0) {
        printf("error no context found\n");
        return -1;
    }

    dev = iio_context_find_device(ctx, DEV_NAME);
    if (dev == 0) {
        printf("error no device found\n");
        return -1;
    }
    printf("device %s found\n", DEV_NAME);

    int nr_device_channels = iio_device_get_channels_count(dev);
    struct iio_channel **channels = (struct iio_channel**)malloc(nr_device_channels * sizeof (struct iio_channel*));

    for (int i = 0; i < nr_device_channels; i++) {
        channels[i] = iio_device_get_channel(dev, i);
        iio_channel_enable(channels[i]);
    }

    int samples_count = 5;

    struct iio_buffer *buffer = iio_device_create_buffer(dev, samples_count, 0);

    pthread_t thread;
    pthread_create(&thread, 0, exec, 0);

    int x, y;
    int prevx, prevy;

    int check_for_shock = 0;

    while (!stop) {

        if (iio_buffer_refill(buffer) == 800) {
            printf("read 800 bytes read\n");
        }

        for (void *ptr = iio_buffer_start(buffer);
                   ptr < iio_buffer_end(buffer);
                   ptr += iio_buffer_step(buffer)) {
            uint16_t data[4];
            data[0] = *(uint16_t*)ptr;
            data[1] = *(uint16_t*)(ptr + 2);
            data[2] = *(uint16_t*)(ptr + 4);
            data[3] = *(uint16_t*)(ptr + 6);

            if (display) {
                printf("%d-----------%d \\\\\\\\\\\\\\\\\\\\\\ ", data[0], data[1]);
                printf("%d-----------%d\n", data[2], data[3]);
            }

            x = data[0] - data[1];
            y = data[2] - data[3];

            if (check_for_shock) {
                if (abs(x - prevx) > TRESHOLD || abs(y - prevy) > TRESHOLD) {
                    printf("SHOCK\n");
                }
            }

            prevx = x;
            prevy = y;

            check_for_shock = 1;

            if(display) {
                printf("x = %d    y = %d\n", x, y);
            }
        }

        fflush(stdout);
        usleep(delay);
        printf("---------------\n");
    }

    pthread_join(thread, 0);

    // clean up

    for (int i = 0; i < nr_device_channels; i++) {
        iio_channel_disable(channels[i]);
    }
    iio_buffer_destroy(buffer);


    return 0;
}
