PROGS = main endian
PROG = main
OBJS = sum_array_c.o sum_array_s.o sum_array2_s.o add4f_c.o add4f_s.o\
       fact_c.o fact_s.o strlen_c.o strlen_s.o
HEADERS = 

CFLAGS = -g

# Pattern rules to avoid explicit rules

%.o : %.c ${HEADERS}
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as -march=armv7-a ${CFLAGS} -o $@ $<

all : ${PROGS}

${PROG} : ${PROG}.c ${HEADERS} ${OBJS}
	gcc ${CFLAGS} -o $@ $< ${OBJS}

endian : endian.c
	gcc ${CFLAGS} -o $@ $<

clean :
	rm -rf ${PROGS} ${OBJS}
