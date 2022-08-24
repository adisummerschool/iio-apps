#include <stdio.h>
#include <iio.h>
#include <pthread.h>

struct iio_context *ctx = 0;

#define URI "ip:10.76.84.219"

int main() {
    ctx = iio_create_context_from_uri(URI);

    int nr_ctx_attrs;
    nr_ctx_attrs = iio_context_get_attrs_count(ctx);
    printf("%d\n", nr_ctx_attrs);

    for (int i = 0; i < nr_ctx_attrs; i++) {
        char *name, *value;
        iio_context_get_attr(ctx, i, &name, &value);
        printf("for attribute %d: name = %s value = %s\n", i, name, value);
    }

    return 0;
}
