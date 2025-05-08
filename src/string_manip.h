#ifndef string_manip_h_
#define string_manip_h_

#include <stdio.h>
ssize_t getline_wrap(char **restrict lineptr, FILE *restrict stream);

char *modify_string(const char *, int min);

#endif
