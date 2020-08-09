#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int getCount(void);
void makeTriangle(int, string);

int main(void){
    int count = getCount();
    makeTriangle(count, "#");

}

int getCount(void){
    int count;
    do{
        count = get_int("Enter Height: ");
    } while(!(0 < count && count < 9));
    return count;
}

void makeTriangle(int count, string latt){
    string form = " ";
    for(int i=0; i<count; i++){
        for(int e=0; e<count-i-1; e++){
            printf("%s", form);
        }
        for(int e=count-i-1; e<count; e++){
            printf("%s", latt);
        }
        printf("  ");
        for(int e=count-i-1; e<count; e++){
            printf("%s", latt);
        }
        printf("%s\n", form);
    }
}