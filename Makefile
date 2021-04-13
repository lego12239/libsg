TARGET := libsg.a
OBJS := sg.o

CFLAGS += -Wall -Wno-main -g3 -ggdb -I. `pkg-config --cflags sdl2`

.PHONY: doc clean clean-doc clean-all dist


$(TARGET): $(OBJS)
	$(AR) rvs $@ $^

doc:
	doxygen

clean:
	rm -f *~ *.o

clean-doc:
	rm -rf doc

clean-all: clean clean-doc
	rm -f $(TARGET)

dist:
	tar -c sg.c sg.h CHANGELOG Doxyfile Makefile examples | xz > libsg-1.txz

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $<
