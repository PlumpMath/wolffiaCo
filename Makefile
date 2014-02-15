all: example

example: tests/example.cpp coroutine.h Makefile
	g++ -O3 -std=c++11 -I. -o example tests/example.cpp

## just for checking size
avr:
	avr-g++ -O3 -std=c++11 -I. -o example.avr tests/example.cpp
	avr-size --mcu=attiny85 -C example.avr

	avr-g++ -O3 -std=c++11 -I. -o example-static.avr tests/example-static.cpp
	avr-size --mcu=attiny85 -C example-static.avr

	avr-g++ -O3 -std=c++11 -I. -o example-simple.avr tests/example-simple.cpp
	avr-size --mcu=attiny85 -C example-simple.avr

	avr-g++ -O3 -std=c++11 -I. -o example-class.avr tests/example-class.cpp
	avr-size --mcu=attiny85 -C example-class.avr


clean:
	rm -rf example *.avr