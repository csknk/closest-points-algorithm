CC = g++
#CFLAGS = -ggdb3 -W -Wall -std=c++17
CFLAGS = -ggdb3 -W 	-std=c++17

all: main stress

main: $(wildcard *.cpp)
	$(CC) $(CFLAGS) -o $@ $<

stress: $(wildcard *.cpp)
	$(CC) $(CFLAGS) -D STRESS_TEST -o $@ $<
