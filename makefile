CC = gcc
all:main clean
	@echo -e "\nOK................................\n\n\n"
clean:
	-rm *.o
main: main.o jry_bl_string.o jry_bl_array.o
	$(CC) -o main main.o jry_bl_string.o -lm
main.o:
	$(CC) -c -lm -o main.o main.c
jry_bl_string.o:
	$(CC) -c -lm -o jry_bl_string.o ./jry_bl/jry_bl_string.c
jry_bl_array.o:
	$(CC) -c -lm -o jry_bl_array.o ./jry_bl/jry_bl_array.c
