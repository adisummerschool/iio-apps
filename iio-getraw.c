#include <stdio.h>
#include <iio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct axis_type {
    int x;
    int y;
} Axis;

struct iio_context *ctx = 0;
struct iio_device *dev = 0;

int run = 1;
int stop = 0;
int slow_down = 0;
int delay = 0;

#define URI "ip:10.76.84.219"
#define DEV_NAME "iio-ad5592r"

#define ATTR_NAME_RAW "raw"

void calibrate() {
    return;
}

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
            calibrate();
        }
    }
    return 0;
}

int main() {
    ctx = iio_create_context_from_uri(URI);

    dev = iio_context_find_device(ctx, DEV_NAME);
    if (dev == 0) {
        printf("error no device found\n");
        return -1;
    }
    printf("device %s found\n", DEV_NAME);

    Axis *axis = (Axis*)malloc(sizeof(Axis));

    int nr_device_channels = iio_device_get_channels_count(dev);
    struct iio_channel **channels = (struct iio_channel**)malloc(nr_device_channels * sizeof (struct iio_channel*));

    for (int i = 0; i < nr_device_channels; i++) {
        channels[i] = iio_device_get_channel(dev, i);
    }

    pthread_t thread;
    pthread_create(&thread, 0, exec, 0);

    while (!stop) {
        int data[4];
        for (int i = 0; i < nr_device_channels; i++) {
            char buf[10];
            iio_channel_attr_read(channels[i], ATTR_NAME_RAW, &buf, 10);
            data[i] = atoi(buf);
            printf("for channel number %d value: %d\n", i, data[i]);
        }
        axis->x = data[0] - data[1];
        axis->y = data[2] - data[3];
        printf("x = %5d\ty = %5d\n", axis->x, axis->y);
        fflush(stdout);
        usleep(delay);
        printf("---------------\n");
    }

    pthread_join(thread, 0);

    return 0;
}
