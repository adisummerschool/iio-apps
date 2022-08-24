#include <stdio.h>
#include <iio.h>
#include <unistd.h>
struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
struct iio_channel *chan [4]; //define a struct array
struct iio_buffer *buffer = NULL;

#define URI "ip:10.76.84.217"
#define DEVICE_NAME "ad5592r"

int main() {
    char *p;
    ctx = iio_create_context_from_uri(URI) ;
    if(ctx == NULL){
        printf ("No context \n");
        return -1;
    }
    p = iio_context_get_attr_value(ctx,"hw_carrier");

    int nr_ctx_attr;
    nr_ctx_attr = iio_context_get_attrs_count(ctx);

    dev = iio_context_find_device(ctx,DEVICE_NAME);
    if(dev == NULL){
        printf ("No device \n");
        return -1;
    }


    unsigned int chan_count = iio_device_get_channels_count(dev);// determin the numbers of channels
    for(int i = 0 ; i < chan_count; i++){
        chan[i] = iio_device_get_channel(dev,i);// getting chhannels
        if(chan[i] == NULL){
            printf ("Channel not found\n");
            return -1;
        }
        iio_channel_enable(chan[i]);//enable buffer if found

    }

    buffer = iio_device_create_buffer(dev,100,false);
    if(buffer == NULL){
        printf ("Buffer not found\n");
        return -1;
    }

    int nr_bits = iio_buffer_refill(buffer) ;

    if(nr_bits < 0) printf("Refill failed");
    else printf("The number of bites is %d \n",nr_bits);

    for (void *ptr = iio_buffer_first(buffer, chan);
               ptr < iio_buffer_end(buffer);
               ptr += iio_buffer_step(buffer)) {

    }

    iio_buffer_destroy(buffer);//buffer destroyed after usage
    return 0;
}
