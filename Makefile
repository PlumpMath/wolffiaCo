all: example

example: examples/example.cpp coroutine.hpp Makefile
	g++ -O3 -std=c++11 -I. -o example examples/example.cpp

## just for checking size
avr:
	avr-g++ -O3 -std=c++11 -I. -o example.avr examples/example.cpp coroutine.cpp

	avr-g++ -O3 -std=c++11 -I. -o example-simple.avr examples/example-simple.cpp

	avr-g++ -O3 -std=c++11 -I. -o example-static-0_funcs.avr examples/example-static.cpp
	avr-g++ -O3 -std=c++11 -I. -o example-static-1_func.avr examples/example-static.cpp -DFUNC1
	avr-g++ -O3 -std=c++11 -I. -o example-static-2_funcs.avr examples/example-static.cpp -DFUNC1 -DFUNC2
	avr-g++ -O3 -std=c++11 -I. -o example-static-3_funcs.avr examples/example-static.cpp -DFUNC1 -DFUNC2 -DFUNC3

	avr-g++ -O3 -std=c++11 -I. -o example-class-0_funcs.avr examples/example-class.cpp
	avr-g++ -O3 -std=c++11 -I. -o example-class-1_func.avr examples/example-class.cpp -DFUNC1
	avr-g++ -O3 -std=c++11 -I. -o example-class-2_funcs.avr examples/example-class.cpp -DFUNC1 -DFUNC2
	avr-g++ -O3 -std=c++11 -I. -o example-class-3_funcs.avr examples/example-class.cpp -DFUNC1 -DFUNC2 -DFUNC3

	avr-size -B --mcu=attiny85 example-class-*.avr example-static-*.avr

	avr-size -C --mcu=attiny85 example.avr

clean:
	rm -rf example *.avr