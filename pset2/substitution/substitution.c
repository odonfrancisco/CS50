#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int checkValidKey(string key);
char convertLetter(char letter, string key);
string toLowerCase(string str);

int main(int argc, string argv[]){
    if(argc == 2){
        string key = toLowerCase(argv[1]);
        // Checks that key is valid. if not, returns 1 to end process;
        if(checkValidKey(key) == 1){
            return 1;
        } else {
            string userText = get_string("plaintext: ");
            string cipherText = userText;
            
            int i = 0;
            while(userText[i] != '\0'){
                if(isalpha(userText[i])){
                    char cipherLetter = convertLetter(userText[i], key);
                    cipherText[i] = cipherLetter;
                }
                i++;
            }
            printf("ciphertext: %s\n", userText);
        }
        
    } else {
        printf("Error, must submit Key as Command Line Argument. Please try again.\n");
        return 1;
    }
}

int checkValidKey(string key){
    int length = strlen(key);
    if(length != 26){
        printf("Error, Key must be 26 characters in length.\n");
        return 1;
    }
    
    for(int i = 0; i < length; i++){
        char letter = key[i];
        if(!isalpha(letter)){
            printf("Error, Key must be alphanumerical\n");
            return 1;
        } else {
            // checks for index of first found letter in key
                // if index is diff than current ind, it is dulpicate letter
            if(strchr(key, letter) - key != i){
                printf("Error, each char in Key must be unique\n");
                return 1;
            }
        }
    }
    
    return 0;
}

string toLowerCase(string str){
    string lowerCaseStr = str;
    for(int i = 0; str[i] != '\0'; i++){
        if(64 < str[i] && str[i] < 91){
            lowerCaseStr[i] += 32;
        }
    }
    return lowerCaseStr;
}

char convertLetter(char letter, string key){
    int index = toupper(letter) - 65;
    char newLetter = toupper(key[index]);
    if(islower(letter)){
        newLetter += 32;
    }
    return newLetter;
        
}