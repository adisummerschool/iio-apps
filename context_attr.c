#include <stdio.h>
#include <iio.h>

struct iio_context *ctx = NULL;
struct iio_device *dev = NULL;
int nr_ctx_attr;

#define URI "ip:10.76.84.217"
#define DEVICE_NAME "ad5592r"

int main (){

	ctx = iio_create_context_from_uri(URI);
	if(ctx == NULL){
		printf("No context found\n");
		return -1;
	}

	nr_ctx_attr = iio_context_get_attrs_count(ctx);
	printf("%d context attr", nr_ctx_attr);

	for(unsigned int i=0;i<nr_ctx_attr;i++)
	{
		const char *name, *value;
		iio_context_get_attr(ctx, i, &name, &value);
		printf("Name: %s , Value: %s \n", name, value);
	}
	return 0;
}
