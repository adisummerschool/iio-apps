#include <stdio.h>

int main(){

    int i, S;

    S = 0;

    for(i = 1; i <= 10; i++)
    {
        S = S + i;
    }

    printf("S = %d\n", S);

    return 0;
}
