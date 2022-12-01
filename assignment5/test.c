#include <stdio.h>
#include<unistd.h>

int main()
{
    int i = 0;
    while(i != 3)
    {
        printf("Testing...\n");
        sleep(1);

        i += 1;
    }

    return 0;
}