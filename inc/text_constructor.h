#ifndef TEXT_CONSTRUCTOR_H
#define TEXT_CONSTRUCTOR_H

#include "menu.h"
#include "structs.h"

void symbolsMemoryExpansion(Sentence* sentence);

void sentenceConstructor (Sentence* sentence);

Sentence* sentenceRead();

void clearLastSentence(Text* textNode);

int sentenceInList (Text* textBegin, Text* textNode);

void pushToList (Text** textNode);

void textConstructor (Text* textNode);

#endif
