HEX_FILES = 00-dp-reg.hex 01-dp-imm.hex 02-dp-lsl-imm.hex\
            03-dp-lsr-reg.hex 04-dp-asr-imm.hex\
			05-mem-reg.hex 06-mem-imm.hex 07-mem-shift-reg.hex\
			08-blbx.hex 09-b.hex 10-beq.hex 11-ble.hex 12-bgt.hex\
			13-mul.hex 14-rsb.hex\
			15-quadratic_s.hex 16-get_bitseq_s.hex 17-max3_s.hex\
			18-sum_array_s.hex 19-fib_rec_s.hex\
# TODO		20-merge_sort_s.hex

.PRECIOUS: %.o

%.o: %.s
	as -o $@ $<

%.hex: %.o
	objdump -d $< | python3 makerom3.py > $@

all: $(HEX_FILES)

clean:
	rm -rf $(HEX_FILES) *.o
