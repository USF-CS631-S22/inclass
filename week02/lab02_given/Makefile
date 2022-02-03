PROGS = lab02
OBJS = scan.o parse.o
HEADERS = ntlang.h

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c ${HEADERS}
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s ${HEADERS}
	as -o $@ $<

all : ${PROGS}

lab02 : lab02.c ${HEADERS} ${OBJS}
	gcc ${CFLAGS} -o $@ $< ${OBJS}

clean :
	rm -rf ${PROGS} ${OBJS}
