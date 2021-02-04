#ifndef SENTENCES_SORT_H
#define SENTENCES_SORT_H

#include "menu.h"

int countAverageLen (const wchar_t* sentence);

int compareByAverageLen (const void* s1, const void* s2);

void sentencesSort (Text* textBegin, Text* textEnd);

#endif


