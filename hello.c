#include <stdio.h>


int main() {

    int val;
    for(int i = 0; i < 10; i++)
    {
        printf("%d\n", (val += i));
    }

	return 0;
}
