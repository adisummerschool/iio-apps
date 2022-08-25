#include    <stdio.h>
#include    <iio.h>

struct iio_context *ctx = NULL;
struct iio_device  *dev = NULL;
struct iio_channel *chan[4];

#define URI "ip:10.76.84.219"
#define DEVICE_NAME "iio-ad5592r"

int main(){


        ctx = iio_create_context_from_uri("ip:10.76.84.219");
        if(ctx == NULL){
                printf("No context\n");
                return -1;
        }



        int nr_ctx_attrs = iio_context_get_attrs_count(ctx);
        printf("%d context attributes found\n", nr_ctx_attrs);

        for (int i=0; i< nr_ctx_attrs; i++){
            char *name;
            char *value;
            iio_context_get_attr(ctx, i, &name, &value);
            printf("ctxattr[%d] - name:%lx %s -value:%lx %s\n", i, name, name , value, value);
        }



       dev = iio_context_find_device(ctx, "iio-ad5592r");
       if(dev == NULL){
               printf("No device\n");
               return -1;
       }
       printf("Got device %s %lx\n", DEVICE_NAME , dev);




       unsigned int ch =  iio_device_get_channels_count(dev);
       if(ch == NULL){
               printf("No channels\n");
               return -1;
       }
       printf("Got %lx channels\n", ch);



       for (int i = 0; i < ch; i++){

           chan[i] = iio_device_get_channel(dev, i);
           if(chan[i] == NULL){
                   printf("No channels found\n");
                   return -1;
           }
           printf("Got channel %s %lx \n", iio_channel_get_id(chan[i]), chan[i]);
       }

       for (int i = 0; i < ch; i++){
       int nr_chan_attrs = iio_channel_get_attrs_count(chan[i]);
       printf("%d Attributes found on channel %d\n", nr_chan_attrs, i);
       }



       /*int value[4];
       while(1){
       for (int i = 0; i < 4; i++){
           char buf[10];
           iio_channel_attr_read(chan[i], "raw", &buf, 10);
           value[i]=atoi(buf);
       }

       int x = value[0] - value[1];
       int y = value[2] - value[3];

       printf("x = %5d\ty = %5d\n", x, y);
       fflush(stdout);
       usleep(500*1000);
       }*/

       return 0;
}

