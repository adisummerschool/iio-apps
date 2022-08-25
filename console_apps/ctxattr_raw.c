#include <stdio.h>
#include <iio.h>

struct iio_context *ctx = NULL;
struct iio_device  *device = NULL;

int main() {
	ctx = iio_create_context_from_uri("ip:10.76.84.217");
	if (ctx == NULL) {
		printf("No context\n");
		return -1;
	}

	device = iio_context_find_device(ctx, "ad5592r");
	if (device == NULL) {
		printf("No device\n");
		return -2;
	}

	long long x=0, y=0;
	int values[4];
	struct iio_channel  *chan;

	while (true) {
		for(int i =0;i < 4; i++) {
			chan = iio_device_get_channel(device, i);
			iio_channel_attr_read_longlong(chan, "raw", &values[i]);
		}

		x = values[0] - values[1];
		y = values[2] - values[3];

		printf("x= %d     y= %d\n", x, y);

	}
	return 0;
}
