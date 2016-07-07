#include "sys_file.h"

#define MAX_HANDLES 10
static FILE* fileHandles[MAX_HANDLES] = { 0 };

static int findHandle(void) {
	for (int i = 0; i < MAX_HANDLES; i++) {
		if (fileHandles[i] == NULL)
			return i;
	}
	return -1;
}

static int fileLength(FILE *f) {
	int pos;
	int end;

	pos = ftell(f);
	fseek(f, 0, SEEK_END);
	end = ftell(f);
	fseek(f, pos, SEEK_SET);

	return end;
}

int sys_FileOpenRead(char *path, int *size) {
	int handleIndex = findHandle();
	FILE *fileHandle = fopen(path, "rb");
	if (fileHandle == 0) {
		if (size != 0)
			*size = -1;
		return -1;
	}
	fileHandles[handleIndex] = fileHandle;
	if (size != 0)
		*size = fileLength(fileHandle);
	return handleIndex;
}

int sys_FileOpenWrite(char *path) {
	int handleIndex = findHandle();
	FILE *fileHandle = fopen(path, "wb");
	if (fileHandle == 0) {
		handleIndex = -1;
	}
	fileHandles[handleIndex] = fileHandle;
	return handleIndex;
}

void sys_FileClose(int handle) {
	if (handle < 0 || MAX_HANDLES - 1 < handle)
		return;
	if (fileHandles[handle] != NULL) {
		fclose(fileHandles[handle]);
		fileHandles[handle] = NULL;
	}
}

void sys_FileSeek(int handle, int position) {
	if (handle < 0 || MAX_HANDLES - 1 < handle)
		return;
	if (fileHandles[handle] != NULL) {
		fseek(fileHandles[handle], position, SEEK_SET);
	}
}

int sys_FileRead(int handle, void* destination, int count) {
	if (handle < 0 || MAX_HANDLES - 1 < handle || destination == 0)
		return 0;
	int bytesRead = (int)fread(destination, 1, count, fileHandles[handle]);
	return bytesRead;
}

int sys_FileWrite(int handle, void* source, int count) {
	if (handle < 0 || MAX_HANDLES - 1 < handle || source == 0)
		return 0;
	int bytesWritten = (int)fwrite(source, 1, count, fileHandles[handle]);
	return bytesWritten;
}