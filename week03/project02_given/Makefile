PROG = project02
OBJS = scan.o parse.o eval.o
HEADERS = ntlang.h

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c ${HEADERS}
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s ${HEADERS}
	as -o $@ $<

all : ${PROG}

${PROG} : ${PROG}.c ${HEADERS} ${OBJS}
	gcc ${CFLAGS} -o $@ $< ${OBJS}

clean :
	rm -rf ${PROG} ${OBJS}
