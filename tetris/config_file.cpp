#include "config_file.h"

InputAction listOfKeys[1] = {0};

void readNextWord(char * wordStorage, char * text, int * position, int size, bool seek)
{
	int oldPos = *position;
	int memoryWalker = 0;
	for (; *position < size; (*position)++) {
		if (text[*position] != ' ' && '!' < text[*position]) {
			wordStorage[memoryWalker] = text[*position];
			++memoryWalker;
		}
		else if (text[*position] == 13) ++memoryWalker;
		else if (text[*position] == '\n') {
			if (memoryWalker == 0) wordStorage[memoryWalker++] = '\n';
			wordStorage[memoryWalker] = NULL;
			break;
		}
		else if (wordStorage[0] != NULL) {
			wordStorage[memoryWalker] = NULL;
			++(*position);
			break;
		}
	}
	if (seek == false) *position = oldPos;
}

int returnCommandIndex(variableCommand* commandList, size_t numberOfItemsInarray, const char* command) {
	for (unsigned int i = 0; i < numberOfItemsInarray; i++) {
		if (strcmp(command, commandList[i].name) == 0) {
			//*commandList[i].address = number;
			return i;
		}
	}
	return -1;	//this means that the command doesn't exist
}

void runOperatorFromList(variableOperator* operatorList, size_t numberOfItemsInarray, const char* operatorString, void* a, int b) {
	for (unsigned int i = 0; i < numberOfItemsInarray; i++) {
		if (strcmp(operatorString, operatorList[i].symbol) == 0) {
			operatorList[i].function(a, b);
		}
	}
}

void assignVariable(void* var0, int var1) {
	*(int*)var0 = var1;
}

void bindFunction(char* text, int* positionInText, int sizeOfText, bool seek) {
	char wordStorage[64];
	int oldPos = *positionInText;
	readNextWord(wordStorage, text, positionInText, sizeOfText, true);
	int numberOfItemsInarray = sizeof(listOfKeys) / sizeof(listOfKeys[0]);
	for (unsigned int i = 0; i < numberOfItemsInarray; i++) {
		if (strcmp(wordStorage, listOfKeys[i].name) == 0) {
			for (int j = 0; j < 2; j++) {
				readNextWord(wordStorage, text, positionInText, sizeOfText, true);
				SDL_Keycode newKey = NULL;
				if (wordStorage[1] == NULL) newKey = wordStorage[0];
				if (newKey) listOfKeys[i].key[j] = newKey;
			}
		}
	}
	if (seek == false) *positionInText = oldPos;
}