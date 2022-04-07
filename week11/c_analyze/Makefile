PROG = analyze
OBJS = analyze.o quadratic_s.o sum_array_s.o find_max_s.o fact_s.o fib_rec_s.o stolower_s.o

%.o: %.c
	gcc -c -g -o $@ $<

%.o: %.s
	as -g -o $@ $<

$(PROG): $(OBJS)
	gcc -g -o $@ $^
	
clean:
	rm -rf $(PROG) $(OBJS)
