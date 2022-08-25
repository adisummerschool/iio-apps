#include <stdio.h>


int main() {

    int s = 0;
    for(int i=0; i<10; i++)
    {
        printf("%d\n",(s += i));
    }

	return 0;
}
