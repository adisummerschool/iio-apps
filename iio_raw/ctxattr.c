#include <stdio.h>
#include <iio.h>
#include <unistd.h>

struct iio_context *ctx = NULL;

#define URI         "ip:10.76.84.212"

int main(){
    char *p;
    ctx = iio_create_context_from_uri(URI);

    if(ctx == NULL)
    {
        printf("No context\n\n");
        return -1;
    }

    p = iio_context_get_attr_value(ctx, "hw_carrier");

    int nr_ctx_attrs;
    nr_ctx_attrs = iio_context_get_attrs_count(ctx);
    printf("%d context attributes found\n\n", nr_ctx_attrs);

    int i;

    for(i = 0; i < nr_ctx_attrs; i++)
    {
        char *name, *value;
        iio_context_get_attr(ctx, i, &name, &value);
        printf("ctxattr[%d] - name:%lx %s - value %lx %s\n", i, name, name, value, value);
    }
    printf("\n");

    return 0;
}
