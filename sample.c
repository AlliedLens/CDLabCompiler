#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int a, b, sum;

    a =   1;
    b = 1;

    // singline lcomment

    sum = a +     b;
    printf("The sum of %d and %d is: %d\n", a, b, sum);

    if (sum == 12345){
        return 33;
    }

    /*
        here are some
        multine comments here yaaay
    */

    return 0;
}