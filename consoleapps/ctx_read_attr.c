#include <stdio.h>
#include <unistd.h>
#include <iio.h>

#define NULL        0

#define URI         "ip:10.76.84.212"
#define DEV_NAME    "ad5592r"

struct iio_context *ctx;
struct iio_device  *dev;
struct iio_channel *ch[4];

int main() {

    //Assigning the context and the device
    ctx = iio_create_context_from_uri(URI);
    if(ctx == NULL){
            printf("Specified context does not exist\n");
            return -1;
    }
    uint attr_count = iio_context_get_attrs_count(ctx);
    const char *attr_name;
    const char *attr_value;

    dev = iio_context_find_device(ctx, DEV_NAME);
    if(dev == NULL){
        printf("Could not find specified device");
        return -1;
    }

    //Assigning the channels in the channel array
    uint chan_count = iio_device_get_channels_count(dev);
    for(uint i = 0; i < chan_count; i++){
        ch[i] = iio_device_get_channel(dev, i);
        if(ch[i] == NULL){
            printf("Channel %d does not exist", i);
            return -1;
        }
    }

    printf("Context attributes:\n-------------------\n");
    for(uint i = 0; i < attr_count; i++){
        iio_context_get_attr(ctx, i, &attr_name, &attr_value);
        printf("%s: %s\n", attr_name, attr_value);
    }

    printf("\nChannel attributes:\n-------------------\n");
    for(uint i = 0; i < chan_count; i++){
        for(uint j = 0; j < iio_channel_get_attrs_count(ch[i]); j++){
            printf("Channel %d attribute: %s\n", i, iio_channel_get_attr(ch[i], j));
        }
    }

	return 0;
}
