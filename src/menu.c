#include "../inc/menu.h"

void printText(Text* textBegin, Text* textEnd) {
    Text* p = textBegin;
    wprintf(L"Ваш текст:\n");

    while (p) {
        wprintf(L"%ls", p->sentence->symbols);
        p = p->next;
    }

    wprintf(L"\n");
    menu(textBegin, textEnd);
}

void cleanMemory(Text* textBegin, Text* textEnd) {
    while (textBegin) {
        Text* tmp = textBegin;
        textBegin = textBegin->next;
        delSentence(tmp, &textBegin, &textEnd);
    }
}

int getAction() {
    int action;

    if (wscanf(L"%d%*c", &action)) {
        return action;
    }

    return -1;
}

void menu(Text* textBegin, Text* textEnd) {
    wprintf(L"Пожалуйста, выберите одно из предложенных действий.\n");
	switch (getAction()) {
	    case 1:
	        findMaskSentences(textBegin, textEnd);
	        break;
	    case 2:
	        sentencesSort(textBegin, textEnd);
	        break;
	    case 3:
	        sentenceSort(textBegin, textEnd);
	        break;
	    case 4:
	        checkSentences(textBegin, textEnd);
	        break;
	    case 5:
	        printText(textBegin, textEnd);
	        break;
	    case 6:
            	cleanMemory(textBegin, textEnd);
	    case -1:
	        wprintf(L"Произошла ошибка. Выходим из программы.\n");
	        exit(0);
	default:
	    wprintf(L"Введён некорректный запрос. Пожалуйста, попробуйте снова.\n");
	    menu(textBegin, textEnd);
	}
}
