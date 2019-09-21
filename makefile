#   Copyright (c) [2019] juruoyun developer team
#   Juruoyun basic lib is licensed under the Mulan PSL v1.
#   You can use this software according to the terms and conditions of the Mulan PSL v1.
#   You may obtain a copy of Mulan PSL v1 at:
#      http://license.coscl.org.cn/MulanPSL
#   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
#   PURPOSE.
#   See the Mulan PSL v1 for more details.

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
