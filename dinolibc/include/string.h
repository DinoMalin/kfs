#pragma once

int strlen(char *str);
int strncmp(char *str1, char *str2, int size);
int strcmp(char *str1, char *str2);
int atoi(const char *str);
char *strchr(const char *str, int search);

void *memset(void *pointer, int value, unsigned int size);
void *memcpy(void *dst, const void *src, unsigned int size);
#define bzero(ptr, size) memset(ptr, 0, size)

#define isalpha(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define isdigit(c) (c >= '0' && c <= '9')

unsigned int address(const char *str);
int valid_address(const char *str);

#define 😹 "0123456789abcdef"
