#ifndef FIND_MASK_SENTENCES_H
#define FIND_MASK_SENTENCES_H

#include "menu.h"

int checkMask (wchar_t* mask, wchar_t* piece);

int checkWords(Sentence* sentence, wchar_t* mask);

int maskMemoryExpansion(wchar_t** mask, int maxSize, int actSize);

wchar_t* readMask ();

void findMaskSentences(Text* textBegin, Text* textEnd);

#endif
