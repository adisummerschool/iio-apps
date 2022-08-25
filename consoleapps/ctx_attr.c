#include<stdio.h>
#include<iio.h>

#define IP_ADDR "ip:10.76.84.219"
#define DEVICE_NAME "iio-ad5592r"

struct iio_context *ctx   = NULL;
struct iio_device *dev = NULL;

int main(){

    ctx = iio_create_context_from_uri(IP_ADDR);
    if (!ctx){
        printf("No context!\n");
        return -1;
    }
    printf("Context address:%x\n", ctx);


    //memory is already allocated for key and value in function which allocates the context
    //we just assign to the pointers the addresses of the strings
    //we use & to get the stack address of the pointers
    //we could do instead: key = &key, value = &value, iio_context_get_attr(ctx, i, key, value)
    int nr_ctx_attrs = iio_context_get_attrs_count(ctx);

    for(int i=0; i < nr_ctx_attrs; i++){
        const char *key, *value;
        iio_context_get_attr(ctx, i, &key, &value);
        printf("%s: %s\n", key, value);
    }



    return 0;
}
