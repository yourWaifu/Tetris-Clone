#include "config_file.h"

void readNextWord(char * wordStorage, char * text, int * position, int size, bool seek)
{
	int oldPos = *position;
	int memoryWalker = 0;
	for (; *position < size; (*position)++) {
		if (text[*position] != ' ' && '!' < text[*position]) {
			wordStorage[memoryWalker] = text[*position];
			++memoryWalker;
		}
		else if (text[*position] == 13) {
			if (memoryWalker == 0) memoryWalker++;
			else {
				wordStorage[memoryWalker] = NULL;
				break;
			}
		}
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
	if (*position == size) wordStorage[memoryWalker] = NULL;
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
	if (listOfKeys.empty()) return;
	for (unsigned int i = 0; i < listOfKeys.size(); i++) {
		if (strcmp(wordStorage, listOfKeys[i]->name) == 0) {
			for (int j = 0; j < 2; j++) {
				readNextWord(wordStorage, text, positionInText, sizeOfText, true);
				SDL_Keycode newKey = NULL;
				if (wordStorage[0] == 39 && wordStorage[2] == 39) newKey = wordStorage[1];
				if (newKey) listOfKeys[i]->key[j] = newKey;
			}
			break;
		}
	}
	if (seek == false) *positionInText = oldPos;
}

void runConfigFile(char * file)
{
	variableCommand variableCommandList[4] = { { "w", &gameResolution.w } ,{ "h", &gameResolution.h }, { "canHoldTetromino", (int*)&canShowGhostPiece }, {"fullscreen", (int*)&gameResolution.fullscreen} };
	variableOperator operatorList[1] = { { "=", assignVariable } };
	specialCommand specialCommandList[1] = { { "bind", bindFunction } };

	int size;
	int fileHandle = sys_FileOpenRead(file, &size);
	void *buffer = malloc(size);
	sys_FileRead(fileHandle, buffer, size);
	char* fileTextToChar = (char *)buffer;
	int memoryWalker = 0;
	while (memoryWalker < size) {
		//get variable name from file
		char command[64] = "";
		readNextWord(command, fileTextToChar, &memoryWalker, size, true);

		//check if it's a variable
		int commandIndex = returnCommandIndex(variableCommandList, sizeof(variableCommandList) / sizeof(variableCommandList[0]), command);
		if (commandIndex != -1) {	//if the command exist
			char operatorString[4] = "";
			readNextWord(operatorString, fileTextToChar, &memoryWalker, size, true);	//get operator
			readNextWord(command, fileTextToChar, &memoryWalker, size, true);			//get number
			if (command[0] == 't' && command[1] == 'r' && command[2] == 'u' && command[3] == 'e' && command[4] == NULL) command[0] = '1';	//turn true into 1
			runOperatorFromList(operatorList, sizeof(operatorList) / sizeof(operatorList[0]), operatorString, variableCommandList[commandIndex].address, convertStringToIntger(command));
		}
		else {
			size_t numberOfItemsInarray = sizeof(specialCommandList) / sizeof(specialCommandList[0]);
			for (unsigned int i = 0; i < numberOfItemsInarray; i++) {
				if (strcmp(command, specialCommandList[i].name) == 0) {
					specialCommandList[i].function(fileTextToChar, &memoryWalker, size, true);
				}
			}
		}

		//go to next line
		while (memoryWalker < size) {
			readNextWord(command, fileTextToChar, &memoryWalker, size, true);
			if (strcmp(command, "\n") == 0) {
				++memoryWalker;
				break;
			}
		}
	}

	sys_FileClose(fileHandle);
	free(buffer);
	buffer = NULL;
}
