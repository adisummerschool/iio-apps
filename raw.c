#include <stdio.h>
#include<iio.h>

struct iio_context *ctx =NULL;
struct iio_device *dev=NULL;
struct iio_channels *chan[4];
static bool stop;

#define URI "ip:10.76.84.212"
#define DEVICE_NAME "ad5592r"

int main() {
    ctx= iio_create_context_from_uri(URI);
    if(ctx == NULL){
        printf("No context!\n");
        return -1;
    }

    dev=iio_context_find_device(ctx, DEVICE_NAME);
    if(dev == NULL){
        printf("No device!\n");
        return -1;
    }
    printf("Got device! %s %lx \n", DEVICE_NAME, dev);



    unsigned int chan_count =iio_device_get_channels_count(dev);


    for(int i=0;i<chan_count;i++ ){

        chan[i]=iio_device_get_channel(dev,i);
        if(chan[i] == NULL){
            printf("No channel!\n");
            return -1;
        }
        printf("Got channels! %s %lx \n", iio_channel_get_id(chan[i]),chan[i]);
    }


    int values[4];
    while(1){
        for(int i=0;i<4;i++){
            char buf[10];
            iio_channel_attr_read(chan[i], "raw", &buf, 10);
            values[i]=atoi(buf);

        }
        long long x=values[0]-values[1];
        long long y=values[2]-values[3];

        printf("x=%5d\ty=%5d\n",x,y);
        fflush(stdout);
        usleep(1000*1000);
    }

    return 0;
}
