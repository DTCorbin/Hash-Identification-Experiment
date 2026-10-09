#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char *chopLeft(char *hash, int spaces) {
	hash += spaces;
	return hash;
}

char *chopRight(char *str, char delimiter) {
	int len = strLen(str);
	char temp[len];
	strcpy(temp, str);
	for (int i = len; str[i] != delimiter; i--) {
		temp[i] = '0';
		len--;
	}
	temp[len] = '\0';
	char *trimmed = (char *)malloc(sizeof(char)*len);
	strcpy(trimmed, temp);
	return trimmed;
}

char *extractID(char *str, char delimiter) {
	char *id;
	id = chopLeft(str, 1);
	id = chopRight(id, delimiter);
	return id;
}


int scanSingleDelimiter(char *hash) {
	int exists = 0;
	int len = strLen(hash);
	for (int i = 0; i < (len/3); i++) {
		if (hash[i] == '$') {
			exists = 1;
		}
	}
	return exists;
}

int main (int argc, char* argv[]) {

    if (argc > 1){
        char *message = argv[1];
		char *id = strdup(message);
        if (message[0] == '$'){
		id = extractID(id, '$');
            	printf("Identifier: %s", id);
	    	free(id);
	} else if (message[0] == '{'){
		id = extractID(id, '}');
            	printf("Identifier: %s", id);
	    	free(id);
        } else if (int check = scanSingleDelimiter(message) != 1){
            	printf("Other type of hash");
	} else {
		id = chopRight(id, '$');
		printf("Identifier: %s", id);
	    	free(id);
	}
    } else {
        printf("\e[31m***You must pass your hash as an argument***\e[0m");
    }
    return 0;
}
