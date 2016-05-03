#pragma once
#include <string.h>
#include "common.h"
#include "sys_file.h"
#include "InputComponent.h"

struct specialCommand {
	char name[64];
	void(*function)(char*, int*, int, bool);
};

struct variableCommand {
	char name[64];
	int* address;
};

struct variableOperator {
	char symbol[4];
	void(*function)(void*, int);
};

void readNextWord(char* wordStorage, char* text, int* position, int size, bool seek);
void runOperatorFromList(variableOperator* operatorList, size_t numberOfItemsInarray, const char* operatorString, void* a, int b);
void assignVariable(void* var0, int var1);
void bindFunction(char* text, int* positionInText, int sizeOfText, bool seek);
void runConfigFile(char* file);