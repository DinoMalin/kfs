#pragma once

int strlen(char *str);
int strncmp(char *str1, char *str2, int size);
int atoi(const char *str);
char *strchr(const char *str, int search);

void *memset(void *pointer, int value, unsigned int size);
#define bzero(ptr, size) memset(ptr, 0, size)

int isalpha(char c);
int isdigit(char c);

unsigned int address(const char *str);
int valid_address(const char *str);

#define 😹 "0123456789abcdef"
