#include <ctype.h>
#include <stdint.h>
#include <stdlib.h> // malloc free
#include "my_lab.h"
#include "vector/vector.h"

#define FALSE 0
#define TRUE  1
#define NEND(c) ((c) != EOF && (c) != '\n')
#define __CHECK_MAX__(max, cur) ((max) = ( (max) < (cur) ) ? (cur):(max))


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


int getLineLen(void)
{
	int lineLen;
  puts("[*] Input line length [default: 100]:");
  if( scanf("%d", &lineLen) == 0 || lineLen < 1)
		return 100;
  return lineLen;
};


static void
getFileSize(FILE *file, int* fileSize)
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


static inline void refresh(char **beginLine, int *curLen, char **lastDelimiter)
{
	*beginLine += *curLen + 1;
	*curLen = 0;
	*lastDelimiter = NULL;
};


void copyFile(FILE *_out, FILE *_in, const int lineLen)
{
		const char *inputBuffer = loadInputFile(_in);
    fclose(_in);

		vector_t $lineVector;
		v_init(&$lineVector);

		int curLen = 0;
		int maxLen = -1;
		char *lastDelimiter = NULL;
		char *beginLine = (char *) inputBuffer;
		while( beginLine[curLen] != -1 )
		{
				while( isspace(beginLine[curLen]) == FALSE &&
						   beginLine[curLen] != -1 )
				    curLen++;

				if( beginLine[curLen] == -1 ) {
					v_add(&$lineVector, curLen, beginLine);
				  __CHECK_MAX__(maxLen, curLen);
					break;
				};

				if( beginLine[curLen] == '\n' ) {
					v_add(&$lineVector, curLen, beginLine);
				  __CHECK_MAX__(maxLen, curLen);
					refresh( &beginLine, &curLen, &lastDelimiter );
					continue;
				};

				if( curLen < lineLen ) {
					lastDelimiter = beginLine + curLen;
					curLen++;
				} else {
					if( lastDelimiter == NULL ) curLen = lineLen;
					if( curLen > lineLen )      curLen = lastDelimiter - beginLine;

					v_add(&$lineVector, curLen, beginLine);
				  __CHECK_MAX__(maxLen, curLen);
					refresh( &beginLine, &curLen, &lastDelimiter );
				};
		};

		node_t *line;
		for(int i=0; i<$lineVector.count; i++)
		{
			line = v_next(&$lineVector);
			if( line->size >= maxLen ) continue;

			for(int j=0; j<line->size; j++)
				fputc(line->content[j], _out);
			fputc('\n', _out);
		};

		v_destruct(&$lineVector);

    free((void *)inputBuffer);
};
