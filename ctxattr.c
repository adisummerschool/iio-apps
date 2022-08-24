#include <stdio.h>
#include<iio.h>


struct iio_context *ctx =NULL;

#define URI "ip:10.76.84.212"
#define DEVICE_NAME "ad5592r"

int main() {

    ctx= iio_create_context_from_uri(URI);
    if(ctx == NULL){
        printf("No context\n");
        return -1;
    }

    int nr_cttx_attrs=iio_context_get_attrs_count(ctx);

    printf("%d context attributes found\n", nr_cttx_attrs);

    for(int i=0; i< nr_cttx_attrs;i++){
        char *name, *value;
        iio_context_get_attr(ctx, i, &name, &value);
        printf("ctxattr[%d] - name:%lx %s - value %lx %s \n", i, name, name, value, value);
    }
    return 0;

}
