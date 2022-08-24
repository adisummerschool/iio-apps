#include <stdio.h>
#include <iio.h>

struct iio_context *ctx = NULL;
struct iio_device  *device = NULL;
struct iio_buffer  *buffer = NULL;

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

	buffer = iio_device_create_buffer(device, 100, false);
	if (buffer == NULL) {
		printf("No buffer created\n");
		return -3;
	}

	return 0;
}
