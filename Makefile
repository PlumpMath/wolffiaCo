all: example

example: example.cpp coroutine.h Makefile
	g++ -O3 -std=c++11 -o example example.cpp

## just for checking size
avr:
	avr-g++ -O3 -std=c++11 -o example.avr example.cpp
	avr-size --mcu=attiny85 -C example.avr

	avr-g++ -O3 -std=c++11 -o example-static.avr example-static.cpp
	avr-size --mcu=attiny85 -C example-static.avr

	avr-g++ -O3 -std=c++11 -o example-simple.avr example-simple.cpp
	avr-size --mcu=attiny85 -C example-simple.avr

	avr-g++ -O3 -std=c++11 -o example-class.avr example-class.cpp
	avr-size --mcu=attiny85 -C example-class.avr


clean:
	rm -rf example *.avr