#include <stdio.h>
#include <iio.h>

#define NUMAR 5 
#define URI "ip:10.76.84.219"
#define DEVICE_NAME "iio-ad5592r"


struct iio_context *ctx     =NULL;
struct iio_device *dev      =NULL;
struct  iio_channel *chan[4];


int main(){
char *p;
        ctx = iio_create_context_from_uri("ip:10.76.84.219");
        if(ctx == NULL){
            printf("no context \n");
            return -1;
        }
        printf("%x",ctx);


        p = iio_context_get_attr_value(ctx,"hw_carrier");
        printf("%x \n",p);

        int nr_ctx_attrs;
        nr_ctx_attrs = iio_context_get_attrs_count(ctx);
        printf("%d context attributes found \n",nr_ctx_attrs);

        char p1;
        int q1;
        char ptr1;

        printf("sizeof %d %d %d\n",sizeof(p1),sizeof(q1),sizeof(ptr1));

        for(int i = 0; i< nr_ctx_attrs;i++){

            char *name,*value;
            iio_context_get_attr(ctx,1,&name,&value);
            printf(" ctxattr[%d] - name:%lx -value:%lx %s \n",i,name,value);

        }
        dev = iio_context_find_device(ctx,"iio-ad5592r");
        if(dev == NULL){
            printf("no context \n");
            return -1;
        }
        printf("Got device %s %lx\n",DEVICE_NAME,dev);



        unsigned int ch = iio_device_get_channels_count(dev);
        if(ch == NULL){
            printf("no channel \n");
            return -1;
        }
        printf("Got %lx channels \n",ch);

        for ( int i = 0 ; i < ch ; i++){

            chan[i] = iio_device_get_channel(dev,i);
            if(chan[i] == NULL){
                printf("No channels found ");
                        return -1;
            }
            printf("Got channels %s %lx \n",iio_channel_get_id(chan[i]),chan[i]);
        }


        for (int i = 0 ;i < ch ; i++){

            int nr_chan_attrs = iio_channel_get_attrs_count(chan[i]);
            printf("Channel %d has %d attributes\n",i,nr_chan_attrs);
        }

        int value[4];
               int n = 10;
               do
               {
               for (int i = 0; i < 4; i++){
                   char buf[10];
                   iio_channel_attr_read(chan[i], "raw", &buf, 10);
                   value[i]= atoi(buf);
               }

               int x = value[0] - value[1];

               int y = value[2] - value[3];

               printf("x = %5d\ty = %5d\n", x, y);
               fflush(stdout);
               usleep(1000*1000);

               }
               while(n!=0);
		return 0;
		}
