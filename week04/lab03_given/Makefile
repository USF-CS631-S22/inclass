PROG = lab03
OBJS = add_c.o add_s.o add4_c.o add4_s.o quadratic_c.o quadratic_s.o\
	   min_c.o min_s.o
HEADERS = 

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c ${HEADERS}
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as -march=armv7-a -o $@ $<

all : ${PROG}

${PROG} : ${PROG}.c ${HEADERS} ${OBJS}
	gcc ${CFLAGS} -o $@ $< ${OBJS}

clean :
	rm -rf ${PROG} ${OBJS}
