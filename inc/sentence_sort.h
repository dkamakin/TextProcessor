#ifndef SENTENCE_SORT_H
#define SENTENCE_SORT_H

#include "menu.h"

typedef struct Dividers {
    int size;
    int index;
    wchar_t* symbols;
} Dividers;

int compare(const void* s1, const void* s2);

int memoryExpansion (wchar_t*** sentence, int maxSize, int actSize);

Dividers* initStruct (int i);

int isDivider (wchar_t symbol);

wchar_t** sortWords (wchar_t* symbols);

Dividers** findDividers (Sentence* sentenceNode);

wchar_t* initSortedSentence (Sentence* sentenceNode);

void sentenceSort(Text* textBegin, Text* textEnd);

#endif
