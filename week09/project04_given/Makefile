PROG = project04
OBJS = project04.o armemu.o cache.o verbose.o\
	   quadratic_c.o quadratic_s.o\
	   max3_c.o max3_s.o\
	   find_max_c.o find_max_s.o\
	   fib_rec_c.o fib_rec_s.o\
       get_bitseq_c.o get_bitseq_s.o\
       stolower_c.o stolower_s.o\
       strncat_c.o strncat_s.o\
       matches_c.o matches_s.o\
	   merge_sort_c.o merge_sort_s.o\
	   
HEADERS = armemu.h

CFLAGS = -g -Wall

%.o : %.c $(HEADERS)
	gcc $(CFLAGS) -c -o $@ $<

%.o : %.s $(HEADERS)
	as -march=armv7-a -g -o $@ $<

$(PROG) : $(OBJS)
	gcc $(CFLAGS) -o $@ $^

clean :
	rm -rf $(PROG) $(OBJS)
