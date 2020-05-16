#include <ctype.h>
#include <stdint.h>
#include <stdlib.h> // malloc free
#include "my_lab.h"
#include "vector/vector.h"

#define FALSE 0
#define TRUE  1
#define NEND(c) ((c) != EOF && (c) != '\n')


typedef struct {
	size_t size;
	char *content;
} line_t;


void getFileName(char *buf)
{
	fgets(buf, BUF_SIZE, stdin);
	for(int i=0; i<BUF_SIZE; i++)
	{
		if(buf[i] == '\n') {
			buf[i] = 0;
			break;
		};
	};
};

void
getFileSize(FILE *file, int* fileSize)
{
	fseek(file, 0L, SEEK_END);
	*fileSize = ftell(file);
	rewind(file);
};


static const char*
loadInputFile(FILE *_in, const int _in_size)
{
	if(_in == NULL) goto ERROR;

	char *buffer = (char*)  malloc(_in_size + 1);

	for(int $pos=0; $pos < _in_size; $pos++)
		buffer[$pos] = fgetc(_in);

	buffer[_in_size] = -1;

	return (const char*) buffer;

ERROR:
  puts("[X] Corrupted input file.");
	exit(-1);
};


static inline void vectorAppend(vector_t *vctr, size_t sz, char *content)
{
	v_add(vctr, sizeof(line_t));
	line_t *dt = (line_t*) vctr->TAIL->data;
	dt->size = sz;
	dt->content = content;
};


static inline void refresh(char **beginLine, int *curLen)
{
	*beginLine += *curLen + 1;
	*curLen = 0;
};


void copyFile(FILE *_out, FILE *_in, const int _in_size)
{
		const char *inputBuffer = loadInputFile(_in, _in_size);
		fclose(_in);

		vector_t $lineVector;
		v_init(&$lineVector);

		int curLen = 0;
		int maxLen = -1;
		char *beginLine = (char *) inputBuffer;
		while( beginLine[curLen] != -1 )
		{
				while( beginLine[curLen] != '\n' &&
						   beginLine[curLen] != -1 )
				    curLen++;

				//--//
				if(maxLen < curLen) maxLen = curLen;
				//--//

				if( beginLine[curLen] == -1 ) {
					vectorAppend(&$lineVector, curLen, beginLine);
					break;
				};

				if( beginLine[curLen] == '\n' ) {
					vectorAppend(&$lineVector, curLen, beginLine);
					refresh( &beginLine, &curLen );
					continue;
				};
		};

		node_t *line = v_next(&$lineVector);
		while( line != NULL ) // a1,a2,..,an,NULL,a1,a2,..,an...
		{
			line_t *currentLine = (line_t *) line->data;
			if(currentLine->size < maxLen)
			{
				for(int j=0; j<currentLine->size; j++)
					fputc(currentLine->content[j], _out);
				fputc('\n', _out);
			}

			line = v_next(&$lineVector);
		};

		v_destruct(&$lineVector);

    free((void *)inputBuffer);
};
