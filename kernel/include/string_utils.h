#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include "mbox.h" // Include any necessary dependencies

// Function prototypes
char *custom_strncpy(char *dest, const char *src, size_t n);
int custom_strcmp(const char *s1, const char *s2);
int custom_strncmp(const char *s1, const char *s2, int n);
int custom_strlen(const char *str);
char custom_tolower(char c);
void custom_strcpy(char *dest, const char *src);
void custom_strcat(char *dest, const char *src);
char *custom_strtok(char *str, const char *delim);
int parse_int_from_str(const char* str);
int custom_atoi(const char *str);
char* custom_itoa(int num) ;
#endif /* STRING_UTILS_H_ */
