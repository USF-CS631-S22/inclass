PROGS = first_c first_s add_main mul_main hello_c hello_s

OBJS = first_s.o add_c.o add_s.o mul_c.o mul_s.o

CFLAGS = -g

%.o : %.s
	as -march=armv7-a ${CFLAGS} -o $@ $<

all : ${PROGS}


first_c : first_c.c
	gcc ${CFLAGS} -o $@ $^

first_s : first_s.o
	gcc ${CFLAGS} -o $@ $^

add_main : add_main.c add_c.o add_s.o
	gcc ${CFLAGS} -o $@ $^

mul_main : mul_main.c mul_c.o mul_s.o
	gcc ${CFLAGS} -o $@ $^

hello_c : hello_c.o
	gcc ${CFLAGS} -o $@ $^

hello_s : hello_s.o
	gcc ${CFLAGS} -o $@ $^

clean:
	rm -rf ${PROGS} ${OBJS}
