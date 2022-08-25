#include <stdio.h>

#define NUMAR 5

int main() {

    printf("Hello practicai %d \n", NUMAR);
    int s=0;
    int v[10];
    for (int i = 1;i<10;i++)
    {
        s=s+i;
        v[i]=i;
        printf("Suma numereor");

        for(int j=1;j<i+1;j++){
            if(j==i) printf(" %d" ,v[j]);
            else printf(" %d +" ,v[j]);
        }

        printf(" este : %d",s);
        printf ("\n");
    }


	return 0;
}
