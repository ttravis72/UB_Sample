CC = g++
FLAGS = -g -Wall -Wno-sign-compare -std=c++11
EXECUTABLE = BestFirstSearch

all: program2.o Driver.o
	$(CC) $(FLAGS) -o $(EXECUTABLE) program2.o Driver.o

program2.o: program2.cpp
	$(CC) $(FLAGS) -c program2.cpp

Driver.o: Driver.cpp
	$(CC) $(FLAGS) -c Driver.cpp

clean:
	rm -rf *.o *~ $(EXECUTABLE)
