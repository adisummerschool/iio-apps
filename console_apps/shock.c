#include <stdio.h>
#include <iio.h>
#include <time.h>

struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
struct iio_buffer *buf = NULL;

struct iio_channel *chn[4];
int nr_chan;

#define URI "ip:10.76.84.217"
#define DEVICE_NAME "ad5592r"
#define BUF_SIZE 100
#define THRESH 250

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

	printf("GOOD DEVICE: %s : %p\n\n", DEVICE_NAME, dev);
	nr_chan = iio_device_get_channels_count(dev);

	printf("%d CHANNELS FOUND\n\n", nr_chan);
	for(unsigned int i=0; i<nr_chan; i++)
	{
		chn[i] = iio_device_get_channel(dev ,i);
		if(!chn[i]){
			printf("Channel not found %d\n",i);
			return -1;
		}
		iio_channel_enable(chn[i]);
	}

	buf = iio_device_create_buffer(dev, BUF_SIZE, false);
	if(buf == NULL)
	{
		printf("Buffer error");
		return -1;
	}
	printf("GOOD BUFFER %p\n\n", buf);

	int nr = iio_buffer_refill(buf);
	printf("Bytes: %d\n", nr);


	int x,y,prevx,prevy;
	int eventX, eventY;
	bool first=true;
	bool trigger = false;
	while(1)
	{
		for (void *ptr = iio_buffer_first(buf, chn[1]); ptr < iio_buffer_end(buf); ptr += iio_buffer_step(buf))
		{
			int16_t values[4];
			for(int i=0;i<4;i++)
				values[i] = ((int16_t*)ptr)[i];

			prevx = x;
			prevy = y;

			x = values[0] - values[1];
			y = values[2] - values[3];


			if(first) {
				first = false;
				continue;
			}
			if(abs(x-prevx) > THRESH || abs(y-prevy)>THRESH) {
				eventX = abs(x-prevx);
				eventY = abs(y-prevy);

				trigger = true;
			}

			if(trigger) {
				time_t t = time(NULL);
				struct tm tm = *localtime(&t);
				printf("now: %d-%02d-%02d %02d:%02d:%02d: ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
				printf("Accelerometer Event: X:%5d Y:%5d\n", eventX, eventY);
			}
		}
	}



	iio_buffer_destroy(buf);
	for(unsigned int i=0; i<nr_chan; i++)
		iio_channel_disable(chn[i]);


	//WORK IN PROGRESS

	return 0;
}
