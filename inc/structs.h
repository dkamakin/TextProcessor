#ifndef STRUCTS_H
#define STRUCTS_H

#include <wchar.h>

typedef struct Sentence {
    unsigned long size;
    unsigned long capacity;
    int words;
    wchar_t* symbols;
} Sentence;

typedef struct Text {
    struct Text* next;
    struct Text* prev;
    Sentence* sentence;
} Text;

#endif
