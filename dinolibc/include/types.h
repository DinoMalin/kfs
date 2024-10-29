#pragma once

#define packed __attribute__((packed))
#define aligned(x) __attribute__((aligned(x)))

typedef signed char i8;
typedef unsigned char u8;

typedef short i16;
typedef unsigned short u16;

typedef int i32;
typedef unsigned u32;

typedef long long i64;
typedef unsigned long long u64;
