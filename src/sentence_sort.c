#include "../inc/sentence_sort.h"


int compare (const void* s1, const void* s2) {
    return (int)(wcslen(*(const wchar_t**)s2) - wcslen(*(const wchar_t**)s1));
}

int memoryExpansion (wchar_t*** sentence, int maxSize, int actSize) {
    if (maxSize == actSize) {
        maxSize *= 2;
        *sentence = realloc(*sentence, maxSize * sizeof(wchar_t*));
    }

    return maxSize;
}

Dividers* initStruct (int i) {
    Dividers* dividers = calloc(1, sizeof(Dividers));
    dividers->size = 0;
    dividers->index = i;
    return dividers;
}

wchar_t** sortWords (wchar_t* symbols) {
    int maxSize = 1, actSize = 0;
    wchar_t** sortedSentence = malloc(sizeof(wchar_t*)), *buffer;
    wchar_t* piece = wcstok(symbols, L" ,.", &buffer);

    while (piece) {
        maxSize = memoryExpansion(&sortedSentence, maxSize, actSize);
        sortedSentence[actSize++] = piece;
        piece = wcstok(NULL, L" ,.", &buffer);
    }

    qsort(sortedSentence, actSize, sizeof(wchar_t*), compare);
    return sortedSentence;
}

int isDivider (wchar_t symbol) {
    return symbol == L',' || symbol == L' ' || symbol == L'.';
}

Dividers** findDividers (Sentence* sentenceNode) {
    Dividers** dels = malloc(sizeof(Dividers*));
    int checkDividers = 0, maxSize = 1, actSize = 0;

    // +1 is for the dot.
    for (int i = 0; i < sentenceNode->size+1; i++) {
        if (isDivider(sentenceNode->symbols[i]) && !checkDividers) {
            Dividers* dividers = initStruct(i);

            for (int j = i; isDivider(sentenceNode->symbols[j]); j++) {
                dividers->size++;
            }

            if (maxSize == actSize) {
                maxSize *= 2;
                dels = realloc(dels, maxSize * sizeof(Dividers*));
            }

            dels[actSize] = dividers;
            checkDividers = 1;
        }

        // Copy dividers to an array.
        else if (checkDividers && !isDivider(sentenceNode->symbols[i])) {
            dels[actSize]->symbols = malloc(dels[actSize]->size * sizeof(wchar_t));
            wcsncpy(dels[actSize]->symbols, &sentenceNode->symbols[dels[actSize]->index],
                    dels[actSize]->size);
            actSize++;
            checkDividers = 0;
        }
    }

    return dels;
}

wchar_t* initSortedSentence (Sentence* sentenceNode) {
    wchar_t* ans = calloc((sentenceNode->size+1), sizeof(wchar_t));
    Dividers** dels = findDividers(sentenceNode);
    wchar_t** sortedSentence = sortWords(sentenceNode->symbols);

    // Copy a word then dividers to the array and move the pointer (res is the beginning of the sentence).
    wchar_t* res = ans;

    for (int i = 0; i < sentenceNode->words; i++) {
        wmemcpy(ans, sortedSentence[i], wcslen(sortedSentence[i]));
        ans += wcslen(sortedSentence[i]);
        wmemcpy(ans, dels[i]->symbols, dels[i]->size);
        ans += dels[i]->size;
        free(dels[i]->symbols);
        free(dels[i]);
    }

    res[sentenceNode->size] = L'\0';

    free(sortedSentence);
    free(sentenceNode->symbols);
    free(dels);
    return res;
}

void sentenceSort(Text* textBegin, Text* textEnd) {
    Text* p = textBegin;

    while (p) {
        p->sentence->symbols = initSortedSentence(p->sentence);
        p = p->next;
    }

    menu(textBegin, textEnd);
}
