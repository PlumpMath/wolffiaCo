all: main

avr: main.hex

main: main.cpp coroutine.h Makefile
	g++ -O3 -std=c++11 -o main main.cpp

## just for checking size
main.hex: main.cpp coroutine.h Makefile
	avr-g++ -Os -std=c++11 -o main.avr main.cpp
	avr-size --mcu=attiny85 -C main.avr

clean:
	rm -rf main main.hex main.avr