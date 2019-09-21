CC = g++
all: main.o jry_bl_string.o jry_bl_array.o jry_bl_exception.o jry_bl_malloc.o
	$(CC) -o main tmp/main.o tmp/jry_bl_string.o tmp/jry_bl_exception.o tmp/jry_bl_malloc.o -lm
main.o:
	$(CC) -c -lm -o tmp/main.o main.cpp
jry_bl_string.o:
	$(CC) -c -lm -o tmp/jry_bl_string.o ./jry_bl/jry_bl_string.cpp
jry_bl_array.o:
	$(CC) -c -lm -o tmp/jry_bl_array.o ./jry_bl/jry_bl_array.cpp
jry_bl_exception.o:
	$(CC) -c -lm -o tmp/jry_bl_exception.o ./jry_bl/jry_bl_exception.cpp	
jry_bl_malloc.o:
	$(CC) -c -lm -o tmp/jry_bl_malloc.o ./jry_bl/jry_bl_malloc.cpp	
