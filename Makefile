CFLAGS = -Wall -Wextra -Werror -pendantic -std=c11

test: midi.c
	gcc $(CFLAS) read_midi.c -o read_midi
	./read_midi files/midi.mid
	rm read_midi
