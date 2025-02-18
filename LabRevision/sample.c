int main(){
    int a; 
    int b; 
    int sum;

    a =   1;
    b = 1;
    sum = a +     b;

    sum += 35;
    printf("The sum of %d and %d is: %d\n", a, b, sum);

    if (sum != 12345 || a >= sum ){
        return 33;
    }
    return 0;
}