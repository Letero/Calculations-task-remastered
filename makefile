CC = g++
CFLAGS = -std=c++14 -g -Wall
OBJS = main.o FileManager.o AllTasks.o TaskThread.o

all: build

rebuild: clean build

build: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ./exec.exe

main.o:
	$(CC) $(CFLAGS) ./Sources/main.cpp -c

FileManager.o:
	$(CC) $(CFLAGS) ./Sources/FileManager.cpp -c

TaskThread.o:
	$(CC) $(CFLAGS) ./Sources/TaskThread.cpp -c 

AllTasks.o:
	$(CC) $(CFLAGS) ./Sources/AllTasks.cpp -c

clean:
	rm *.exe
	rm *.o