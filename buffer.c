#include    <stdio.h>
#include    <iio.h>
#include    <time.h>

struct iio_context *ctx = NULL;
struct iio_device  *dev = NULL;
struct iio_channel *chan[4];
struct iio_buffer  *buffer = NULL;

#define URI "ip:10.76.84.219"
#define DEVICE_NAME "iio-ad5592r"
#define THRESH 40


int main(){


        ctx = iio_create_context_from_uri("ip:10.76.84.219");
        if(ctx == NULL){
                printf("No context\n");
                return -1;
        }



        int nr_ctx_attrs = iio_context_get_attrs_count(ctx);


        for (int i=0; i< nr_ctx_attrs; i++){
            char *name;
            char *value;
            iio_context_get_attr(ctx, i, &name, &value);
        }



       dev = iio_context_find_device(ctx, "iio-ad5592r");
       if(dev == NULL){
               printf("No device\n");
               return -1;
       }




       unsigned int ch =  iio_device_get_channels_count(dev);
       if(ch == NULL){
               printf("No channels\n");
               return -1;
       }




       for (int i = 0; i < ch; i++){

           chan[i] = iio_device_get_channel(dev, i);
           if(chan[i] == NULL){
                   printf("No channels found\n");
                   return -1;
           }
       }


       for (int i = 0; i < 4; i++){
           iio_channel_enable(chan[i]);
       }
       buffer = iio_device_create_buffer(dev, 100, false);



       int x,y,prevx,prevy;
           int eventX, eventY;
           bool first=true;
           bool trigger = false;
           while(1) {
               iio_buffer_refill(buffer);
               trigger = false;
               for (char *ptr = iio_buffer_start(buffer);
                    ptr < iio_buffer_end(buffer);
                    ptr += iio_buffer_step(buffer)) {

                   int16_t values[4];

                   values[0] = *(int16_t*)(ptr);
                   values[1] = *(int16_t*)(ptr+2);
                   values[2] = *(int16_t*)(ptr+4);
                   values[3] = *(int16_t*)(ptr+6);

                   prevx = x;
                   prevy = y;
                   x = values[0] - values[1];
                   y = values[2] - values[3];

                   //printf("%d %d\n" ,x,y );
                   if(first) {
                       first = false;
                       continue;
                   }
                   if(abs(x-prevx) > THRESH || abs(y-prevy)>THRESH) {
                       eventX = abs(x-prevx);
                       eventY = abs(y-prevy);

                       trigger = true;
                   }

               }
               if(trigger) {
                   time_t t = time(NULL);
                   struct tm tm = *localtime(&t);
                   printf("now: %d-%02d-%02d %02d:%02d:%02d: ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
                   printf("Accelerometer Event: X:%5d Y:%5d\n", eventX, eventY);
               }
           }


       for (int i = 0; i < 4; i++){
           iio_channel_disable(chan[i]);
       }
        while(1)
       iio_buffer_destroy(buffer);




       return 0;
}

