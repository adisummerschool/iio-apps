#include <stdio.h>
#include <iio.h>

#define URI "ip:10.76.84.212"
#define DEVICE_NAME "ad5592r"

struct iio_context *ctx = NULL;

int main() {
    char *p;

    ctx = iio_create_context_from_uri(URI);

    if(ctx == NULL){
        printf("No context \n");
        return -1;
        }

    p = iio_context_get_attr_value(ctx, "hw_carrier");

    int nr_ctx_attrs;
    nr_ctx_attrs = iio_context_get_attrs_count(ctx);
    printf("%d context attributes found \n", nr_ctx_attrs);

    for(int i = 0 ; i < nr_ctx_attrs ; i++)
    {
        char *name, *value;
        iio_context_get_attr(ctx, i, &name, &value);
        printf("ctrxattr[%d] -name:%x %s -value %x %s \n",i, name,name, value, value);

    }

    return 0;
}
