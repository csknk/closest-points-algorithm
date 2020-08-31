CC = g++
#CFLAGS = -ggdb3 -W -Wall -std=c++17
CFLAGS = -ggdb3 -W 	-std=c++17

main: $(wildcard *.cpp)
	$(CC) $(CFLAGS) -o $@ $<
