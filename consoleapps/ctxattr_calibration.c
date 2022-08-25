#include <stdio.h>
#include <iio.h>

struct iio_context *ctx = NULL;
struct iio_device  *device = NULL;

#define URI "ip:10.76.84.212"
#define DEVICE_NAME "ad5592r"
#define GOOD_TRSH 50
#define SLIGHT_TRSH 500

int main() {
    ctx = iio_create_context_from_uri(URI);
    if (ctx == NULL) {
        printf("No context\n");
        return -1;
    }

    device = iio_context_find_device(ctx, DEVICE_NAME);
    if (device == NULL) {
        printf("No device found!\n");
        return -2;
    }

    struct iio_channel  *chan;
    bool x_ok = false, y_ok = false;

    printf("\n\nPlace the board on a leveled surface\n");
    fflush(stdout);

    usleep(2000 * 1000);

    while (1) {
        usleep(500 * 1000);

        long long x=0, y=0;
        long long values[4];

        for(int i =0;i < 4; i++) {
            chan = iio_device_get_channel(device, i);
            iio_channel_attr_read_longlong(chan, "raw", &values[i]);
        }

        x = values[0] - values[1];
        y = values[2] - values[3];
        x_ok = false;
        y_ok = false;

        printf("\n");

        printf("\nX:  ");
        if(x < GOOD_TRSH && x > -GOOD_TRSH) {
            printf("good enough");
            x_ok = true;
        }
        else if (x < 0 && x > -SLIGHT_TRSH) printf("slight clockwise spin");
        else if (x < 0) printf("clockwise spin");
        else if (x > 0 && x < SLIGHT_TRSH) printf("slight counter-clockwise spin");
        else if (x > 0) printf("counter-clockwise spin");

        printf("\nY:  ");
        if(y < GOOD_TRSH && y > -GOOD_TRSH) {
            printf("good enough");
            y_ok = true;
        }
        else if (y < 0 && y > -SLIGHT_TRSH) printf("slight clockwise spin");
        else if (y < 0) printf("clockwise spin");
        else if (y > 0 && y < SLIGHT_TRSH) printf("slight counter-clockwise spin");
        else if (y > 0) printf("counter-clockwise spin");

        fflush(stdout);

        if(x_ok && y_ok) {
            printf("\nSuccessful calibration!\n");
            return 0;
        }

    }
    return 0;
}
