#include<stdio.h>
#include<iio.h>
#include<unistd.h>

#define IP_ADDR "ip:10.76.84.219"
#define DEVICE_NAME "iio-ad5592r"
#define ATTR_RAW "raw"


struct iio_context *ctx   = NULL;
struct iio_device *dev = NULL;


int read_raw(bool inf);

int main(){

    ctx = iio_create_context_from_uri(IP_ADDR);
    if (!ctx){
        printf("No context!\n");
        return -1;
    }


    dev = iio_context_find_device(ctx, DEVICE_NAME);
    if(!dev){
        printf("No device found!\n");
        return -1;
    }

    read_raw(true);

    return 0;
}


int read_raw(bool inf){
    int nr_of_channels = iio_device_get_channels_count(dev);
    struct iio_channel *chan[nr_of_channels];
    for(int i = 0; i < nr_of_channels; i++){

        chan[i] = iio_device_get_channel(dev, i);
        if(!chan[i]){
            printf("No channels found!\n");
            return -1;
        }
    }

    do{
        long long raw_data[nr_of_channels];
        for(int i = 0; i < nr_of_channels; i++){
            char buf[10];
            iio_channel_attr_read(chan[i], ATTR_RAW, buf, 10);
            raw_data[i]=atoi(buf);

        }
        int x = raw_data[0]-raw_data[1];
        int y = raw_data[2]-raw_data[3];
        printf("\nx = %5d\ty = %5d\n", x, y);
        fflush(stdout);

    }while(inf);

    return 0;

}


