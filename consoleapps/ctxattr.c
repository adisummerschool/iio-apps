#include <stdio.h>
#include <iio.h>

struct iio_context *ctx = NULL;
struct iio_context *dev = NULL;
struct iio_context *ch[4];
struct iio_buffer  *buffer;
#define URI "ip:10.76.84.219"
#define DEVICE_NAME  "iio-ad5592r"
int main() {
    char *p;
    ctx = iio_create_context_from_uri("ip:10.76.84.219");
    dev = iio_context_find_device(ctx, DEVICE_NAME);

    if(ctx == NULL)
    {
        printf("No context\n");
        return -1;
    }
    p = iio_context_get_attr_value(ctx,"hw_carrier");
    int nr_ctx_attrs;
    nr_ctx_attrs = iio_context_get_attrs_count(ctx);
    printf("%d context attributs found\n", nr_ctx_attrs );
    int i = 0;
    for(i = 0; i < nr_ctx_attrs; i++){
        char *name;
        char *value;
        iio_context_get_attr(ctx, i, &name, &value);
        printf("ctxattr[%d] - name: %ls %s - value %lx %s\n",i, name, value);
        printf("\n");
}
    dev = iio_context_find_device(ctx, DEVICE_NAME);
    if(ctx == NULL)
    {
        printf("No device\n");
        return -1;
    }
    printf("Got device %s %lx\n", DEVICE_NAME, dev);

    unsigned int chan_count = iio_device_get_channels_count(dev);
    for(int i = 0; i < chan_count; i++)
    {
          ch[i] = iio_device_get_channel(dev, i);
          if(ch == NULL) {
                   printf("Channel not found \n");
                   return -1;
    }
    iio_channel_enable(ch[i]);
    //printf("Got channel: %s %lx\n", iio_channel_get_id(ch[i]), ch[i]);

    buffer = iio_device_create_buffer(dev, 100,false);
    int iio_buff_refill = iio_buffer_refill(buffer);

    printf("%d\n",iio_buff_refill);

    iio_buffer_destroy(buffer);

}
//    int values[4];
//    while(1){
//    for(int i = 0; i < 4 ; i++)
//    {
//        for (void *ptr = iio_buffer_first(buffer, ch[i]);
//                   ptr < iio_buffer_end(buffer);
//                   ptr += iio_buffer_step(buffer)) {
//            values[i] = (int)ptr;

//        }

//    }


//        int x = values[0] - values[1];
//        int y = values[2] - values[3];

//        printf("x = %5d\ty = %5d\n", x, y);
//        fflush(stdout);
//        usleep(1000 * 500);

// }



    return 0;
}
