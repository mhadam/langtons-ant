SOURCES = langtons_ant.cpp lodepng.cpp
OBJECTS = $(SOURCES:.cpp=.o)
CC = clang++
DEBUG = -g -std=c++11
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall -L/usr/lib/x86_64-linux-gnu/ $(DEBUG)
EXECUTABLE=langtons_ant

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm *.o *~ $(EXECUTABLE)
