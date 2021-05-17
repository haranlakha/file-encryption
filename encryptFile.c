#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************************
* SIMPLE FILE ENCRYPTION PROGRAM
*
* This program takes an input file and XOR's the bits against a hash generated using djb2. 
* You can choose any file format for the output.
*
* NOTE: 
* The program will not tell you if your password is correct.
* It will generate an output file regardless.
*
* Compile: 
* 	cc encryptFile.c -o encryptFile
*
* Run:
* 	./encryptFile [input file] [output file] [password]
*
* Example:
* 	./encryptFile input.txt output.txt password
*
* Author: Haran Lakha
*****************************************************************************************/

/***********************************************************************
* Title: djb2 hash algorithm
* Author: Bernstein, Daniel J. aka (djb)
* Year: 1991
* Code from: http://www.cse.yorku.ca/~oz/hash.html
* Original Source: https://groups.google.com/g/comp.lang.c/c/lSKWXiuNOAk
***********************************************************************/

unsigned long djb2(unsigned char *str){

	unsigned long hash = 5381;
    int c;

    while (c = *str++){
    	hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

   	return hash;
}

FILE *inputFile, *outputFile;

int encryptFile(char *input, char *output, char *password){

	int i;
	
	unsigned long hashed = djb2(password);
	
	inputFile = fopen(input, "r");
	outputFile = fopen(output, "w");
	
	if(inputFile == NULL){
		printf("Can't open input file!");
		return -1;
	}
	
	while((i = getc(inputFile)) != EOF){
		putc(i ^ hashed, outputFile);
	}
	
	fclose(inputFile);
	fclose(outputFile);
	
	return 0;
}

int main(int argc, char **argv){

	if(argc == 4){ //if the correct number of arguments are used, proceed
		encryptFile(argv[1], argv[2], argv[3]);
	} else if(argv[3] == NULL){
		printf("Please use a password!\n");
		return -1;
	} else {
		printf("Please use input format: ./encryptFile [input file] [output file] [password]\n");
	}
	
	return 0;
}
