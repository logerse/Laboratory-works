#define BUF_SIZE 100


int getMaxLen(FILE *file);
int getLineLen(void);
void getFileName(char *buf);
void copyFile(FILE *_in, FILE *_out, const int lineLen);
