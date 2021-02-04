#include "../inc/find_mask_sentences.h"

int checkMask (wchar_t* mask, wchar_t* piece) {
    // Quit if didn't get the strings.
    if (!mask || !piece) {
        return 0;
    }

    /* True if have reached the end.
     * If the symbols matches check further.
     * If we have a question mark we want to be sure that the piece ended.
     */

    if (*mask == L'\0' && *piece == L'\0') {
        return 1;
    } else if (*mask == *piece) {
        return (checkMask(mask + 1, piece + 1));
    } else if (*mask == L'?') {
        if (*piece == L'\0') {
            return 0;
        } else {
            return (checkMask(mask + 1, piece + 1));
        }

    } else if (*mask == L'*') {
        if (*piece == L'\0') {
            return checkMask(mask+1, piece);
        } else {
            return (checkMask(mask + 1, piece) || checkMask(mask, piece + 1));
        }
    }

    return 0;
}

int checkWords(Sentence* sentence, wchar_t* mask) {
    unsigned long len = wcslen(sentence->symbols) + 1;
    wchar_t* text = malloc(len * sizeof(wchar_t)), *buffer;
    wmemcpy(text, sentence->symbols, len);
    wchar_t* piece = wcstok(text, L" ,.", &buffer);
    int countRight = 0;

    // Check words from a duplicate of the sentence.
    while (piece) {
        if (checkMask(mask, piece)) {
            countRight++;
        }

        piece = wcstok(NULL, L" ,.", &buffer);
    }

    free(text);
    return countRight == sentence->words ? 1 : 0;
}

int maskMemoryExpansion(wchar_t** mask, int maxSize, int actSize) {
    if (maxSize - 1 == actSize) {
        maxSize *= 2;
        *mask = realloc(*mask, maxSize * sizeof(wchar_t));
    }

    return maxSize;
}

wchar_t* readMask () {
    wchar_t* mask = malloc(sizeof(wchar_t));
    int maxSize = 1, actSize = 0;
    wint_t symbol;

    do {
        symbol = fgetwc(stdin);
        maxSize = maskMemoryExpansion(&mask, maxSize, actSize);
        mask[actSize++] = symbol;
    } while (symbol != L'\n' && symbol != WEOF);

    mask[actSize-1] = L'\0';
    return mask;
}

void findMaskSentences(Text* textBegin, Text* textEnd) {
    Text* p = textBegin;

    wprintf(L"Пожалуйста, введите строку-условие:\n");
    wchar_t* mask = readMask();

    wprintf(L"Предложения, удовлетворяющие условию:\n");
    while (p) {
        if (checkWords(p->sentence, mask)) {
            wprintf(L"%ls", p->sentence->symbols);
        }

        p = p->next;
    }

    wprintf(L"\n");
    free(mask);
    menu(textBegin, textEnd);
}
