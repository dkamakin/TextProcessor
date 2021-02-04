#include "../inc/text_constructor.h"

void symbolsMemoryExpansion (Sentence* sentence) {
    if (sentence->size+1 >= sentence->capacity) {
        sentence->capacity *= 2;
        sentence->symbols = realloc(sentence->symbols, sentence->capacity * sizeof(wchar_t));
    }
}

void sentenceConstructor (Sentence* sentence) {
    sentence->symbols = malloc(sizeof(wchar_t));
    sentence->capacity = 1;
    sentence->size = 0;
    sentence->words = 0;
}

Sentence* sentenceRead () {
    Sentence* sentence = malloc(sizeof(Sentence));
    sentenceConstructor(sentence);
    wint_t symbol;
    int inWord = 1, inSentence = 0;

    do {
        symbol = fgetwc(stdin);

        // Delete spaces in the beginning.
        while (!inSentence && (symbol == L' ')) {
            symbol = fgetwc(stdin);
        }

        inSentence = 1;

        symbolsMemoryExpansion(sentence);

        // Count words. Skip del.
        if (!inWord && (symbol == L' ' || symbol == L',')) {
            inWord = 1;
        }

        if (inWord && iswprint(symbol) && symbol != L' ' && symbol != L',' && symbol != L'.') {
            sentence->words++;
            inWord = 0;
        }

        if (sentence->size != 0 && symbol == L'\n') {
            wprintf(L"Предложение не может содержать символа переноса строки. Пожалуйста, повторите ввод последнего "
                    "предложения.\n");
            free(sentence->symbols);
            free(sentence);
            return NULL;
        }

        sentence->symbols[sentence->size++] = symbol;

    } while (symbol != L'.' && symbol != L'\n' && symbol != WEOF);

    sentence->symbols[sentence->size] = L'\0';

    return sentence;
}

void clearLastSentence (Text* textNode) {
    free(textNode->sentence->symbols);
    textNode->sentence->symbols = NULL;
    free(textNode->sentence);
    textNode->sentence = NULL;
    textNode = textNode->prev;
    free(textNode->next);
    textNode->next = NULL;
}

int sentenceInList (Text* textBegin, Text* textNode) {
    Text* p = textBegin;

    while (p->next) {
        if (!wcscasecmp(textNode->sentence->symbols, p->sentence->symbols)) {
            return 1;
        }

        p = p->next;
    }

    return 0;
}

void pushToList (Text** textNode) {
    (*textNode)->next = malloc(sizeof(Text));
    (*textNode)->next->prev = *textNode;
    (*textNode) = (*textNode)->next;
    (*textNode)->next = NULL;
}

void textConstructor (Text* textNode) {
    Text* textBegin = textNode;

    while (1) {
        textNode->sentence = sentenceRead();

        while (!textNode->sentence) {
            textNode->sentence = sentenceRead();
        }

        /* Delete all sentences without words.
         * Delete the last '\n' sentence.
         * Delete duplicates.
         */

        if (textNode->sentence->size == 1 && (*textNode->sentence->symbols == L'\n' ||
                                              *textNode->sentence->symbols == L'.' ||
                                              *textNode->sentence->symbols == WEOF)) {
            if (!textNode->prev) {
                wprintf(L"Выходим из программы.\n");
                free(textNode->sentence->symbols);
                free(textNode->sentence);
                exit(0);
            } else if (*textNode->sentence->symbols == L'.') {
                free(textNode->sentence->symbols);
                free(textNode->sentence);
            } else {
                clearLastSentence(textNode);
                break;
            }
        } else if (textNode->prev && sentenceInList(textBegin, textNode)) {
            free(textNode->sentence->symbols);
            free(textNode->sentence);
        } else {
            pushToList(&textNode);
        }
    }

}
