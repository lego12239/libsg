TARGETS := ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 ex9
CFLAGS += -Wall -Wno-main -g3 -ggdb -I.. `pkg-config --cflags sdl2`
LDFLAGS += -L../ -lsg -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lm

build: $(TARGETS)

clean:
	rm -f *~ *.o

clean-all: clean
	rm -f $(patsubst %,%.o,$(TARGETS)) $(TARGETS)

%: %.c
	$(CC) -c -o $@.o $(CFLAGS) $<
	$(CC) -o $@ -g3 -ggdb $(patsubst %.c,%.o,$<) $(LDFLAGS)
