#include<stdio.h>
#include<iio.h>
#include<unistd.h>

#define IP_ADDR "ip:10.76.84.219"
#define DEVICE_NAME "iio-ad5592r"
#define ATTR_RAW "raw"
#define SAMPLES_COUNT 100


struct iio_context *ctx   = NULL;
struct iio_device *dev = NULL;
struct iio_buffer *buffer=NULL;


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

    int nr_of_channels = iio_device_get_channels_count(dev);
    struct iio_channel *chan[nr_of_channels];
    for(int i = 0; i < nr_of_channels; i++){

        chan[i] = iio_device_get_channel(dev, i);
        if(!chan[i]){
            printf("No channels found!\n");
            return -1;
        }
        iio_channel_enable(chan[i]);
    }

    buffer = iio_device_create_buffer(dev, SAMPLES_COUNT, false);//creates buffer on target

    int bytes_no = iio_buffer_refill(buffer); //get data from device buffer
    printf("bytes_no = %d\n",bytes_no);
    if(bytes_no<0){
        printf("Error reading from buffer!\n");
        return -1;
    }


    for(int i = 0; i < nr_of_channels; i++){
        iio_channel_disable(chan[i]);
    }
    iio_buffer_destroy(buffer);

    return 0;
}




