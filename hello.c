#include <stdio.h>
#include "second.h"

#define NUMAR 5

int main() {

	int nr=6;
	printf("Hello practica %d \n", NUMAR);
	from_second_file("analog");

	int sum = 0;
	for (int i = 0; i <= 10; i++) {
		sum += i;
	}
	printf("\n %d \n ", sum);

	return 0;
}
