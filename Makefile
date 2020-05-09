CC = gcc
CFLAGS = -g3 -std=c99 -pedantic -Wall -lm

all : Heatmap Unit clean

Heatmap : heatmap.o track.o trackpoint.o location.o
	${CC} ${CFLAGS} -lm -o $@ $^

Unit : track_unit.c track.o trackpoint.o location.o
	${CC} ${CFLAGS} -lm -o $@ $^


heatmap.o : heatmap.c track.h trackpoint.h location.h
	${CC} ${CFLAGS} -c  heatmap.c

track.o : track.c track.h trackpoint.h location.h
	${CC} ${CFLAGS} -c  track.c

trackpoint.o : trackpoint.c trackpoint.h location.h
	${CC} ${CFLAGS} -c  trackpoint.c

location.o : location.c location.h
	${CC} ${CFLAGS} -c  location.c

clean:
	rm -f *.o *.h.gch vgcore.*