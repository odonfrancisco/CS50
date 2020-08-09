#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int countLetters(string s);
int countWords(string s);
int countSentences(string s);

int main(void){
    string sentence = get_string("Your text please: \n");
    
    int letters = countLetters(sentence);
    double words = countWords(sentence);
    int sentences = countSentences(sentence);
    
    // Bc the Liau index works based on letters/100 words & sentences/100 words,
        // need to multiply ratio of actual-words:100 to letters & sentences
    float fact = 100/words;
    float L = letters*fact*0.0588;
    float S = sentences*fact*0.296;
    
    // lrint rounds to nearest int
    float index = lrint(L - S - 15.8);
    
    if ( 16 < index){
        printf("Grade 16+\n");
    } else if ( index < 1){
        printf("Before Grade 1\n");
    } else {
        printf("Grade %.0f\n", index);
    }
}

int countLetters(string s){
    int length = strlen(s);
    int counter = 0;
    for(int i=0; i<length; i++){
        if(isalpha(s[i])){
            counter++;
        }
    }
    return counter;
}

int countWords(string s){
    int length = strlen(s);
    int counter = 1;
    for(int i=0; i<length; i++){
        if(isspace(s[i])){
            counter++;
        }
    }
    return counter;
}

int countSentences(string s){
    int length = strlen(s);
    int counter = 0;
    for(int i=0; i<length; i++){
        if(s[i] == '.' || 
            s[i] == '?' ||
            s[i] == '!'){
            counter++;
        }
    }
    return counter;
}