TARGET=elcapo
TARGET_OBJS=elcapo.o

CFLAGS=-DDEBUG

all: sleep periodic ${TARGET}

sleep: sleep.o
	gcc -o $@ $<

periodic: periodic.o
	gcc -o $@ $<

${TARGET}: ${TARGET_OBJS}
	gcc -o ${TARGET} $<

%.o: %.c
	gcc ${CFLAGS} -o $@ -c $<

clean:
	rm -f ${TARGET} sleep periodic *.o
