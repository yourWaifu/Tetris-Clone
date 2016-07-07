#pragma once
#include <stdio.h>
static int findHandle(void);
static int fileLength(FILE *f);
int sys_FileOpenRead(char *path, int *size);
int sys_FileOpenWrite(char *path);
void sys_FileClose(int handle);
void sys_FileSeek(int handle, int position);
int sys_FileRead(int handle, void* destination, int count);
int sys_FileWrite(int handle, void* source, int count);