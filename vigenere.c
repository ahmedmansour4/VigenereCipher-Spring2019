// Name: Ahmed Mansour
// Date: 3/3/19
// This progam encrypts and decyrpts text files inputted from the command line using the Vigenere Cipher. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//This function checks and stores each letter in char array if it is alphabetic, while also converting it to lowercase.
char* storeOnlyLetters(char text[])
{
	char* temp = calloc(512, sizeof(char));
	int k = 0;
	for(int i = 0; i < strlen(text); i++)
	{
		if(isalpha(text[i]) && text[i] != '\n')
		{
			temp[k++] = (char)tolower(text[i]);
		}
	}
	return temp;
}
//This function pads the end of the char array with x's until the array reaches 512 chars in length
char* padX(char plainText[])
{
	for(int i = 0; i < 512; i++)
	{
		if(plainText[i] == 0)
			plainText[i] = 'x';
	}
	return plainText;
}
//This function encrypts the plain text using a key
char* encrypt(char plainText[], char key[])
{
	int plainInt, keyInt = 0;
	char* encryptedText = calloc(512, sizeof(char));
	for(int i = 0; i < strlen(plainText); i++)
	{
		plainInt = (int)(plainText[i] - 97);
		keyInt = (int)(key[i % strlen(key)] - 97);
		encryptedText[i] = (char)(((plainInt + keyInt) % 26) + 97);
	}
	return encryptedText;
}
//This function decrypts the encrypted text using a key
char* decrypt(char encryptedText[], char key[])
{
	int encryptedInt, keyInt = 0;
	char* decryptedText = calloc(512, sizeof(char));
	for(int i = 0; i < strlen(encryptedText); i++)
	{
		encryptedInt = (int)(encryptedText[i] - 97);
		keyInt = (int)(key[i % strlen(key)] - 97);
		decryptedText[i] = (char)((((encryptedInt - keyInt) + 26) % 26) + 97);
	}
	return decryptedText;
}
//This function displays the plain text, key, and cipher text to the terminal
void printAll(char plainText[], char key[], char cipherText[])
{
	int keyLength;
	printf("\n\nVigenere Key:\n\n");
	for(int i = 0; i < 512; i++)
	{
		if(key[i] != 0)
			keyLength = i;
	}
	for(int i = 0; i <= keyLength; i++)
	{
		if(i % 80 == 0 && i != 0)
			printf("\n");
		printf("%c", key[i]);
	}
	
	printf("\n\n\nPlaintext:\n\n");
	
	for(int i = 0; i < 512; i++)
	{
		if(i % 80 == 0 && i != 0)
			printf("\n");
		printf("%c", plainText[i]);
	}
	
	printf("\n\n\nCiphertext:\n\n");
	
	for(int i = 0; i < 512; i++)
	{
		if(i % 80 == 0 && i != 0)
			printf("\n");
		printf("%c", cipherText[i]);
	}
	printf("\n");
}



int	main(int argc, char **argv)	{
	char* plainText = calloc(700, sizeof(char));
	char* temp = calloc(512, sizeof(char));
	char* key = calloc(512, sizeof(char));
	char* cipherText = calloc(512, sizeof(char));
	char* decryptedText = calloc(512, sizeof(char));
	FILE* plainTextFile = fopen(argv[2], "r");
	FILE* keyTextFile = fopen(argv[1], "r");
	
	fread(plainText, sizeof(char), 700, plainTextFile);
	plainText = storeOnlyLetters(plainText);
	plainText = padX(plainText);
	
	fread(key, sizeof(char), 512, keyTextFile);
	key = storeOnlyLetters(key);
	
	cipherText = encrypt(plainText, key);
	
	decryptedText = decrypt(cipherText, key);
	
	printAll(plainText, key, cipherText);
	fclose(plainTextFile);
	fclose(keyTextFile);
	free(plainText);
	free(key);
	free(cipherText);
	free(decryptedText);
	return 0;
}