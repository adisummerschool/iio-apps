#include <stdio.h>
#include <iio.h>

 struct iio_contex *ctx = NULL; //def context
 struct iio_device *dev = NULL; //def device
 struct iio_channel *ch [4]; // def channel

#define URI "ip:10.76.84.217"
#define DEVICE_NUME "ad5592r"

int main() {
    char *p;
  ctx = iio_create_context_from_uri("ip:10.76.84.217"); //context
           printf("%x\n", ctx);
            if(ctx == NULL){   // verificare conctarea placa
                printf("No contex\n");
                return -1;
            }

           int nr_ctx_attrs; // nr de atribute
           nr_ctx_attrs = iio_context_get_attrs_count(ctx);
           printf("%d \n", nr_ctx_attrs);

           for(int i=0; i< nr_ctx_attrs; i++){  //afisare de atribute
               char *name, *value;
               iio_context_get_attr(ctx, i, &name, &value);
               printf("ctxattr[%d] - nume:%lx %s - value %lx %s\n", i, name, name, value, value);
}
         return 0;

}

