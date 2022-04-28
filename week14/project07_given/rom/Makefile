HEX_FILES = 00-dp-3nop.hex 01-dp-2nop.hex 02-blbx.hex 03-ldr.hex\
            04-dp-fwd.hex 05-ldr-stl.hex 06-blbx-fls.hex

.PRECIOUS: %.o

%.o: %.s
	as -o $@ $<

%.hex: %.o
	objdump -d $< | python3 makerom3.py > $@

all: $(HEX_FILES)

clean:
	rm -rf $(HEX_FILES) *.o
