#include <stdio.h>
#include <iio.h>

struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
int nr_chan;

#define URI "ip:10.76.84.217"
#define DEVICE_NAME "ad5592r"
#define DELTA 30

int main (){

	ctx = iio_create_context_from_uri(URI);
	if(ctx == NULL){
		printf("No context found\n");
		return -1;
	}

	dev = iio_context_find_device(ctx, DEVICE_NAME);
	if(dev == NULL){
		printf("no device found\n");
		return -1;
	}

	printf("DEVICE: %s : %x\n\n", DEVICE_NAME, dev);
	nr_chan = iio_device_get_channels_count(dev);
	struct iio_channel *chn[nr_chan];

	for(unsigned int i=0; i<nr_chan; i++)
	{
		chn[i] = iio_device_get_channel(dev, i);
		if(!chn[i]){
			printf("Channel not found\n");
			return -1;
		}
	}

	while(1)
	{
		long long raw[nr_chan];
		for(unsigned int i=0; i<nr_chan; i++)
		{
			char buf[10];
			iio_channel_attr_read(chn[i], "raw", &buf, 10);
			raw[i] = atoi(buf);
		}

		int x = raw[0]+raw[1];
		int y = raw[2]+raw[3];
		printf("x= %lld\t y= %lld\n", x, y);
		printf("\n");
		if(x > DELTA)
			printf("Roteste X STANGA");
		else if(x < -DELTA)
			printf("Roteste X DREAPTA ");
		else if(y > DELTA)
			printf("Roteste Y STANGA");
		else if(y < -DELTA)
			printf("Roteste Y DREAPTA");
		else{
			printf("PERFECT");
			break;
		}

		usleep(500*1000);
	}
	return 0;
}
