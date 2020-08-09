#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int main(void){
    int userNum = get_int("What is your num? : ");
    int steps = collatz(userNum);
    printf("steps: %i\n", steps);
}

int collatz(int n){
    if(n == 1){
        return 0;
    }
    
    
    if(n % 2 == 0){
        return collatz(n/2)+1;
    } else {
        return collatz(3*n+1)+1;
    }
}