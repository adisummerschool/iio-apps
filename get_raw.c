#include <stdio.h>
#include <iio.h>

 struct iio_contex *ctx = NULL; //def context
 struct iio_device *dev = NULL; //def device
 struct iio_channel *ch [4]; // def channel

#define URI "ip:10.76.84.217"
#define DEVICE_NUME "ad5592r"

int main() {

    ctx = iio_create_context_from_uri("ip:10.76.84.217"); //context
             printf("%x\n", ctx);
              if(ctx == NULL){   // verificare conctarea placa
                  printf("No contex\n");
                  return -1;
              }


    dev = iio_context_find_device(ctx, DEVICE_NUME); //afisare device
             if(dev == NULL){   // verificare conctarea placa
                 printf("No device\n");
                 return -1;
             }
             printf("Go device %s %lx\n", DEVICE_NUME, dev);



    unsigned int chan_count = iio_device_get_channels_count(dev); //afisare canale
              for(int i = 0; i < chan_count; i++){
                  ch[i] = iio_device_get_channel(dev, i);
                  if(ch[i] == NULL){   // verificare conctarea channel
                      printf("Channel not found\n");
                      return -1;
                  }
                  printf("Go channel %s %lx \n", iio_channel_get_id(ch[i]), ch[i]);
              }



    int values[4]; // loop citre axa x, y
         while(1){
        for(int i = 0; i<4 ;i++){
            char buf[10];
            iio_channel_attr_read(ch[i],"raw",&buf, 10);
            values[i]= atoi(buf);
        }
        int x=values[0]-values[1];
        int y=values[2]-values[3];
        printf("x=%5d       y=%5d\n",x,y);
        fflush(stdout);
        usleep( 500*1000 );
    }
    return 0;
}
