#include <stdio.h>
#include <iio.h>

struct iio_context *ctx   = NULL;
struct iio_device  *dev   = NULL;
struct iio_channel *ch[4];

#define URI "ip:10.76.84.217"
#define DEVICE_NAME "ad5592r"

int main() {

	ctx = iio_create_context_from_uri(URI);
	if(ctx == NULL) {
		printf("No context\n");
		return -1;
	}

	int nr_ctx_attrs = iio_context_get_attrs_count(ctx);
	printf("%d context attributes found\n",nr_ctx_attrs);

	for(int i = 0;i < nr_ctx_attrs;i++) {
		char *name;
		char *value;
		iio_context_get_attr(ctx, i, &name, &value);
		printf("ctxattr[%d] - name:%lx %s - value %lx %s\n",i, name, name, value, value);
	}

	dev = iio_context_find_device(ctx,DEVICE_NAME);
	if(dev == NULL) {
		printf("No device\n");
		return -1;
	}
	printf("Got device %s %lx\n", DEVICE_NAME, dev);

	unsigned int chan_count = iio_device_get_channels_count(dev);
	for(int i = 0 ; i < chan_count ; i++) {
		ch[i] = iio_device_get_channel(dev, i);
		if(ch[i] == NULL) {
			printf("Channel not found\n");
			return -1;
		}
		printf("Got channel %s %lx \n", iio_channel_get_id(ch[i]), ch[i]);
	}


	int values[4];

	while(1) {
		for(int i =0;i < 4; i++) {
			char buf[10];
			iio_channel_attr_read(ch[i], "raw", &buf, 10);
			values[i]=atoi(buf);
		}

		int x = values[0] - values[1];
		int y = values[2] - values[3];

		printf("x = %5d\ty = %5d\n", x, y);
		fflush(stdout);
		usleep(500 * 1000);

	}

	return 0;

}
