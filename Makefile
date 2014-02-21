CFLAGS=-O3 -std=c++11 -I./include -D__AVR_ATtiny85__
#CFLAGS=-O3 -I./include -D__AVR_ATtiny85__

all: example

example: examples/example.cpp include/coroutine.h src/locks.c Makefile examples/fizzbuzz.cpp examples/fizzbuzz.h include/wolffia.h
	g++ $(CFLAGS) -o example examples/example.cpp examples/fizzbuzz.cpp src/locks.c

## just for checking size
avr:
	avr-g++ $(CFLAGS) -o example.avr examples/example.cpp src/locks.c examples/fizzbuzz.cpp src/wolffia.c

	avr-g++ $(CFLAGS) -o example-simple.avr examples/example-simple.cpp
	avr-g++ $(CFLAGS) -o example-kernel.avr examples/kernel-example.c src/wolffia.c src/wolffia-buffer.c src/wolffia-events.c

	avr-g++ $(CFLAGS) -o example-static-0_funcs.avr examples/example-static.cpp
	avr-g++ $(CFLAGS) -o example-static-1_func.avr examples/example-static.cpp -DFUNC1
	avr-g++ $(CFLAGS) -o example-static-2_funcs.avr examples/example-static.cpp -DFUNC1 -DFUNC2
	avr-g++ $(CFLAGS) -o example-static-3_funcs.avr examples/example-static.cpp -DFUNC1 -DFUNC2 -DFUNC3

	avr-g++ $(CFLAGS) -o example-class-0_funcs.avr examples/example-class.cpp
	avr-g++ $(CFLAGS) -o example-class-1_func.avr examples/example-class.cpp -DFUNC1
	avr-g++ $(CFLAGS) -o example-class-2_funcs.avr examples/example-class.cpp -DFUNC1 -DFUNC2
	avr-g++ $(CFLAGS) -o example-class-3_funcs.avr examples/example-class.cpp -DFUNC1 -DFUNC2 -DFUNC3

	avr-size -B --mcu=attiny85 example-simple.avr example-class-*.avr example-static-*.avr

	@echo Example stats
	avr-size -C --mcu=attiny85 example.avr

	@echo Kernel example stats
	avr-size -C --mcu=attiny85 example-kernel.avr

test: Makefile tests/maintest.cpp src/locks.c include/coroutine.h src/wolffia.c include/wolffia.h
	g++ -Iinclude -o test tests/maintest.cpp src/locks.c src/wolffia.c
	./test

	g++ -Iinclude -std=c++11 -o test-c11 tests/maintest.cpp src/locks.c src/wolffia.c
	./test-c11

clean:
	rm -rf example *.avr test test-c11