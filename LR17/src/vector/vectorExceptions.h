#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

class MyException {
private:
	char message[256];
public:
	MyException(const char *msg) : message{0} { strcpy(message, msg); };
	const char* get() const { return message; }; 
};