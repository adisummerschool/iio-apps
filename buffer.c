#include <stdio.h>
#include<iio.h>


struct iio_context *ctx =NULL;
struct iio_device *dev=NULL;
struct iio_channels *chan[4];
struct iio_buffer *buffer;



#define URI "ip:10.76.84.212"
#define DEVICE_NAME "ad5592r"

int main() {

    ctx= iio_create_context_from_uri(URI);
    if(ctx == NULL){
        printf("No context\n");
        return -1;
    }

    dev=iio_context_find_device(ctx, DEVICE_NAME);
    if(dev == NULL){
        printf("No device\n");
        return -1;
    }
    printf("Got device %s %lx \n", DEVICE_NAME, dev);



    unsigned int chan_count = iio_device_get_channels_count(dev);

    for(int i=0; i< chan_count; i++){
        chan[i]=iio_device_get_channel(dev, i);
        if(chan[i]==NULL){
            printf("channel not found");
            return -1;
        }
       iio_channel_enable(chan[i]);
        printf("got channel %s %lx \n", iio_channel_get_id(chan[i]), chan[i]);
        long long raw;

                   iio_channel_attr_read_longlong(chan[i], "raw", &raw);
                   printf("RAW: %lld\n", raw);
    }

  buffer=iio_device_create_buffer(dev, 100, false);

  if(buffer == NULL){
      printf("No buffer\n");
      return -1;
  }

  int nr = iio_buffer_refill(buffer);
  printf("Bytes: %d\n", nr);


  iio_buffer_destroy(buffer);
  for(int i=0; i< chan_count; i++){
      iio_channel_disable(chan[i]);
  }

  for (void *ptr = iio_buffer_first(buffer, chan);
             ptr < iio_buffer_end(buffer);
             ptr += iio_buffer_step(buffer)) {
      /* Use "ptr" to read or write a sample for this channel */
  }

  printf("Buffer step: %d\n", iio_buffer_step(buffer));

    return 0;

}
