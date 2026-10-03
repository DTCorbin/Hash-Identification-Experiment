#include <stdio.h>
#include <stdlib.h>

char hashTable[42][20] = {"","","","Bcrypt","","","","","","","","",
                        "Argon2d","","","","","","Argon2id","","","","","","",
                        "","","","","","","","","","","","","","","","",""};
int strLen(char *str) {
    int len = 0;
    while (str[len] != '\0'){
        len++;
    }
    return len;
}

int hashFunc(char *hash) {
    int index = 0;
    for (int i = 0; i < strLen(hash); i++) {
        index +=((int) hash[i] % 40);
    }
    printf("%d", index);
    return 0;
}

//some hashes only have a $ after the identifier
int checkForEndDelim (char *hash) {
    int len = strLen(hash);
    for (int i = 0; i < len; i++){
        if (hash[i] == '$') {
            return 0;
        }
    }
    return -1;
}

char *extractSingleDelimID (char * hash) {
    int len = strLen(hash);
    int delimCount = 0;
    int idCount = 0;
    char temp[len];
    for (int i = 0; i < (len); i++){
        if (hash[i] == '$') {
            temp[i] = '0';
            break;
        } else {
            temp[i] = hash[i];
            idCount++;
        }
    }
    char *idStr = malloc(sizeof(char) * idCount + 1);
    for (int i = 0; i < idCount; i++) {
        idStr[i] = '0';
    }
    idStr[-1] = '\0';
    int idInc = 0;
    for (int i = 0; i < len; i++) {
        if (temp[i] != '0'){
            idStr[idInc] = temp[i];
            idInc++;
        }
    }
    return idStr;
}


char * checkEnclosed(char *hash) {
    int len = strLen(hash);
    int delimCount = 0;
    int idCount = 0;
    char temp[len];
    for (int i = 0; i < len; i++){
        if (hash[i] == '$' || hash[i] == '{' || hash[i] == '}'){
            delimCount++;
            temp[i] = '0';
        } else {
            temp[i] = hash[i];
            idCount++;
        }
        if (delimCount >= 2) {
            break;
        }
    }
    char *idStr = malloc(sizeof(char) * idCount);
    for (int i = 0; i < idCount; i++) {
        idStr[i] = '0';
    }
    int idInc = 0;
    for (int i = 0; i < len; i++) {
        if (temp[i] != '0'){
            idStr[idInc] = temp[i];
            idInc++;
        }
    }
    return idStr;
}

int main (int argc, char* argv[]) {

    if (argc > 1){
        char *message = argv[1];
        if (message[0] == '$' || message[0] == '{'){
            char *encID = checkEnclosed(message);
            printf("%s", encID);
            //hashFunc(encID);
        } else {
            int hasID = checkForEndDelim(message);
            if (hasID == 0){
                char *strtID = extractSingleDelimID(message);
                hashFunc(strtID);
            } else{
                printf("%d", strLen(message));
            }
        }
        // printf("%s", hashOut.hash);
    } else {
        printf("\e[31m***You must pass your hash as an argument***\e[0m");
    }
    return 0;
}