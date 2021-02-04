#include "../inc/del_sentences.h"

void delSentence (Text* p, Text** textBegin, Text** textEnd) {
    if (p->next && !p->prev) {
        *textBegin = p->next;
        free((*textBegin)->prev->sentence->symbols);
        (*textBegin)->prev->sentence->symbols = NULL;
        free((*textBegin)->prev->sentence);
        (*textBegin)->prev->sentence = NULL;
        free((*textBegin)->prev);
        (*textBegin)->prev = NULL;
    } else if (!p->next && p->prev) {
        *textEnd = p->prev;
        free((*textEnd)->next->sentence->symbols);
        (*textEnd)->next->sentence->symbols = NULL;
        free((*textEnd)->next->sentence);
        (*textEnd)->next->sentence = NULL;
        free((*textEnd)->next);
        (*textEnd)->next = NULL;
    } else if (p->next && p->prev) {
        Text *prev = p->prev;
        Text *next = p->next;
        prev->next = p->next;
        next->prev = p->prev;
        free(p->sentence->symbols);
        p->sentence->symbols = NULL;
        free(p->sentence);
        p->sentence = NULL;
        free(p);
    } else {
        wprintf(L"Весь текст удалён, выходим из программы.\n");
        free(p->sentence->symbols);
        free(p->sentence);
        free(p);
        exit(0);
    }
}

void checkSentences(Text* textBegin, Text* textEnd) {
    Text* p = textBegin;
    
    while (p) {
        if (p->sentence->words < 2 || p->sentence->words > 5) {
            Text* tmp = p;
            p = p->next;
            delSentence(tmp, &textBegin, &textEnd);
        }

        else {
            p = p->next;
        }

    }

    menu(textBegin, textEnd);
}
