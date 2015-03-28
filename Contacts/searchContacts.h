#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <new>
#include <string>
#include <vector>
using namespace std;

char * convertStringToLower(char * cstring, int strSize) {
	const int arraySize = 26;
	char alphaUpper[arraySize] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	char alphaLower[arraySize] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	char * letter;

	for(unsigned i = 0; i < strSize; i++) {
		letter = static_cast<char *>(std::addressof(cstring[i]));
		for(unsigned j = 0; j < arraySize; j++) {
			if(*letter == alphaUpper[j]) {
				*letter = alphaLower[j];
			}
		}
	}
	return cstring;
}

char * convertStrToChars(string * input, char * cstring) {
	for(unsigned i = 0; i < (*input).size(); i++) {
		cstring[i] = (*input)[i];
	}
	cstring[(*input).size()] = '\0';

	return cstring;
}

char * convertStrToChars(string input, char * cstring) {
	for(unsigned i = 0; i < input.size(); i++) {
		cstring[i] = input[i];
	}
	cstring[input.size()] = '\0';
	return cstring;	
}