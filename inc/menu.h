#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <wctype.h>
#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include "main.h"
#include "structs.h"
#include "del_sentences.h"
#include "sentence_sort.h"
#include "sentences_sort.h"
#include "find_mask_sentences.h"

void printText(Text* textBegin, Text* textEnd);

void cleanMemory(Text* textBegin, Text* textEnd);

int getAction();

void menu(Text* textBegin, Text* textEnd);

#endif
