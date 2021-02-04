#include "../inc/sentences_sort.h"

int countWords (wchar_t* sentence, unsigned long size) {
   wchar_t* buffer, *countWordsSentence = calloc(size+1, sizeof(wchar_t));
   wmemcpy(countWordsSentence, sentence, size);
   wchar_t* piece = wcstok(countWordsSentence, L" ,.", &buffer);
   int words = 0;

   while (piece) {
       words++;
       piece = wcstok(NULL, L" ,.", &buffer);
   }

   free(countWordsSentence);
   return words;
}

int countAverageLen (const wchar_t* sentence) {
    unsigned long lenSentence = wcslen(sentence) + 1, len = 0;
    wchar_t* buffer, *sentenceCheck = calloc(lenSentence, sizeof(wchar_t));
    wmemcpy(sentenceCheck, sentence, lenSentence);
    wchar_t* piece = wcstok(sentenceCheck, L" ,.", &buffer);
    int words = 0;

    while (piece) {
        words++;
        len += wcslen(piece);
        piece = wcstok(NULL, L" ,.", &buffer);
    }

    free(sentenceCheck);
    return (int)len / words;
}

int compareByAverageLen (const void* s1, const void* s2) {
    return countAverageLen(*(const wchar_t**)s1) - countAverageLen(*(const wchar_t**)s2);
}

void sentencesSort (Text* textBegin, Text* textEnd) {
    Text* p = textBegin;
    int size = 0;

    // Count sentences.
    while (p) {
        size++;
        p = p->next;
    }

    wchar_t** text = malloc(size * sizeof(wchar_t*));
    p = textBegin;
    size = 0;

    // Bidirectional list to a 2D array.
    while (p) {
        text[size++] = p->sentence->symbols;
        p = p->next;
    }

    // Sort the array.
    qsort(text, size, sizeof(wchar_t*), compareByAverageLen);

    // Make a new list.
    p = textBegin;
    size = 0;

    while (p) {
        p->sentence->size = wcslen(text[size]);
        p->sentence->words = countWords(text[size], p->sentence->size);
        p->sentence->capacity = p->sentence->size;
        p->sentence->symbols = calloc(p->sentence->size+1, sizeof(wchar_t));
        wmemcpy(p->sentence->symbols, text[size], p->sentence->size+1);
        p->sentence->symbols[p->sentence->size] = L'\0';
        free(text[size++]);
        p = p->next;
    }

    free(text);
    menu(textBegin, textEnd);
}
