objects = menu.o text_constructor.o main.o del_sentences.o sentence_sort.o sentences_sort.o find_mask_sentences.o
src = src/
compile_flags = -Wall -c

all: prog

prog: $(objects)
	gcc $(objects) -o menu 

sentences_sort.o: $(src)/sentences_sort.c
	gcc $(compile_flags) $(src)/sentences_sort.c

find_mask_sentences.o: $(src)/find_mask_sentences.c
	gcc $(compile_flags) $(src)/find_mask_sentences.c

sentence_sort.o: $(src)/sentence_sort.c
	gcc $(compile_flags) $(src)/sentence_sort.c

del_sentences.o: $(src)/del_sentences.c
	gcc $(compile_flags) $(src)/del_sentences.c

text_constructor.o: $(src)/text_constructor.c
	gcc $(compile_flags) $(src)/text_constructor.c

menu.o: $(src)/menu.c
	gcc $(compile_flags) $(src)/menu.c

main.o: $(src)/main.c
	gcc $(compile_flags) $(src)/main.c

clean:
	rm -rf *.o menu
