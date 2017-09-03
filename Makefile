CPPFLAGS=$(shell --cflags) $(EXTRA_CPPFLAGS)
LDLIBS=$(shell --libs) $(EXTRA_LDLIBS)
EXTRA_LDLIBS?=-pthread
all: game client
	mv game game.out
	mv client client.out
clean:
	rm -f *.o
.PHONY: all clean
