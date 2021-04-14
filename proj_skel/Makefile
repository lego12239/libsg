TARGET = tmpl
OBJS = tmpl.o
LIBS = sg
CFLAGS += -Wall -Wno-main -g3 -ggdb `pkg-config --cflags sdl2`
LDFLAGS += $(patsubst %,-Llib%,$(LIBS)) $(patsubst %,-l%,$(LIBS)) -lSDL2 \
	-lSDL2_ttf -lSDL2_mixer -lSDL2_image -lm


$(TARGET): $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(OBJS) $(LDFLAGS)

doc:
	doxygen

clean:
	rm -f *~ *.o

clean-doc:
	rm -rf doc

clean-all: clean clean-doc
	rm -f $(TARGET)

makefile-update:
	wget -q -O- https://raw.githubusercontent.com/lego12239/libsg/master/proj_skel/Makefile > Makefile
	sed -i -re '1 s/tmpl/$(TARGET)/; 2 s/tmpl.o/$(TARGET).o/' Makefile

sg-update:
	rm -rf libsg-1 libsg libsg.tar.gz
#	mkdir libsg-1
#	cd libsg && 
		wget https://github.com/lego12239/libsg/archive/refs/heads/v1.zip -O libsg.zip && \
		unzip libsg.zip && \
		rm -f libsg.zip
	mv libsg-1 libsg
	cd libsg && make

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $<
