#include "my_lab.h"
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> // malloc free

#define NEND(c) ((c) != EOF && (c) != '\n')
#define FALSE 0
#define TRUE  0

typedef struct {
	size_t size;
	char *content;
} line_t;


void getFileName(char *buf)
{
    int i = 0;
    int c = getchar();
    for(; i<BUF_SIZE-1; i++)
    {
        if( !NEND(c) )
            break;
        buf[i] = c;
        c = getchar();
    }
    buf[i] = 0;
};


int getLineLen(void)
{
    int lineLen = 100;
    printf("[*] Input line length [default: 100]: ");
    if( scanf("%d", &lineLen) == 0 || lineLen < 1)
	return 100;
    return lineLen;
};


static void
getFileSize(FILE *file, const int* fileSize)
{
	fseek(file, 0L, SEEK_END);
	*fileSize = ftell(file);
	rewind(file);
};


static const char*
loadInputFile(FILE *_in)
{
	if(_in == NULL) goto ERROR;
	int fileSize = 0;
	getFileSize(_in, &fileSize);
	if( fileSize == 0 ) {
		fclose(_in);
		goto ERROR;
	};
	
	char *buffer = (char*)  malloc(fileSize + 1);

	for(int $pos=0; $pos < fileSize; $pos++)
		buffer[$pos] = fgetc(_in);

	buffer[fileSize] = -1;
	
	return (const char*) buffer;

ERROR:
    puts("[X] Corrupted input file.");
	exit(-1);	
};


void copyFile(FILE *_out, FILE *_in, const int lineLen)
{
    const char *inputBuffer = loadInputFile(_in);
    fclose(_in);

    int curLen = 0;
	line_t lineArray[1024] = {0,NULL}; // NOTE: Replace const-size initialization
	char *lastDelimiter = NULL;
    char *beginLine = inputBuffer;
    while( beginLine[curLen] != -1 )
    {
    	while( isspace(beginLine[curLen]) == FALSE && curLen <= lineLen )
			curLen++;
	    
		if(lineLen=>curLen)
			lastDelimiter = beginLine[curLen];
		else {
			if( lastDelimiter != NULL ) {
				*lastDelimiter = '\x00';
				
			}
			else
		}
    };

    free(inputBuffer);
};

// #---------------------------------#
// #aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa#
// #aaaaaaaa aaaaaaaaaaa aaaaaaaaaaaa#
// # aaaaaaaa aaaaaaaaaaa aaaaaaaa aa#
