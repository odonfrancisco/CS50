#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

long getCreditNum(void);
int getNumLength(long);
bool isValidCard(long);

int main(void){
    long creditNum = getCreditNum();
    int numLength = getNumLength(creditNum);
    // First digit of credit num
    int oneDigit = creditNum/(pow(10, numLength-1));
    // First two digits of credit num
    int twoDigits = creditNum/(pow(10, numLength-2));
    string cardType = "INVALID";

    if((numLength == 13 || numLength == 16) && oneDigit == 4){
        if(isValidCard(creditNum)){
            cardType = "VISA";
        }
    } else if(numLength == 16 && (50 < twoDigits && twoDigits < 56)){
        if(isValidCard(creditNum)){
            cardType = "MASTERCARD";
        }
    } else if(numLength == 15 && (twoDigits == 34 || twoDigits == 37)){
        if(isValidCard(creditNum)){
            cardType = "AMEX";
        }
    }

    printf("%s\n", cardType);   
    return 0;
}

long getCreditNum(void){
    long num;
    num = get_long("Insert Credit Card Number: ");
    return num;
}

int getNumLength(long num){
    int length = floor(log10(num)) + 1;
    return length;
}

bool isValidCard(long cardNum){
    bool isValid = false;
    int sum = 0;
    // Makes copy of cardNum to work with in loop;
    long numCopy = cardNum/10;
    
    while(numCopy){
        int dig = (numCopy % 10)*2;
        while(dig){
            sum += dig % 10;
            dig /= 10;
        }
        numCopy /= 100;
    }
    
    numCopy = cardNum;
    
    while(numCopy){
        int dig = numCopy % 10;
        sum += dig;
        numCopy /= 100;
    }

    if(sum % 10 == 0){
        isValid = true;
    }
    return isValid;
}