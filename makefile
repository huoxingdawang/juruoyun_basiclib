#   Copyright (c) [2019] juruoyun developer team
#   Juruoyun basic lib is licensed under the Mulan PSL v1.
#   You can use this software according to the terms and conditions of the Mulan PSL v1.
#   You may obtain a copy of Mulan PSL v1 at:
#      http://license.coscl.org.cn$(H)MulanPSL
#   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
#   PURPOSE.
#   See the Mulan PSL v1 for more details.
CC = g++
ifeq ($(shell uname),Linux)
	H = /
else
	H = \\
endif
all: string json base64 md5
init:
	mkdir tmp
	mkdir tmp$(H)examples
	mkdir tmp$(H)jry_bl
	mkdir exes
string:jry_bl_string.o jry_bl_array.o jry_bl_exception.o jry_bl_malloc.o
	$(CC) -c -lm -o tmp$(H)examples$(H)string.o examples$(H)string.cpp
	$(CC) -o exes$(H)string tmp$(H)examples$(H)string.o tmp$(H)jry_bl$(H)jry_bl_string.o tmp$(H)jry_bl$(H)jry_bl_exception.o tmp$(H)jry_bl$(H)jry_bl_malloc.o -lm
json:jry_bl_string.o jry_bl_array.o jry_bl_exception.o jry_bl_malloc.o
	$(CC) -c -lm -o tmp$(H)examples$(H)json.o examples$(H)json.cpp	
	$(CC) -o exes$(H)json tmp$(H)examples$(H)json.o tmp$(H)jry_bl$(H)jry_bl_string.o tmp$(H)jry_bl$(H)jry_bl_exception.o tmp$(H)jry_bl$(H)jry_bl_malloc.o -lm
base64:jry_bl_string.o jry_bl_array.o jry_bl_exception.o jry_bl_malloc.o jry_bl_base64.o
	$(CC) -c -lm -o tmp$(H)examples$(H)base64.o examples$(H)base64.cpp	
	$(CC) -o exes$(H)base64 tmp$(H)examples$(H)base64.o tmp$(H)jry_bl$(H)jry_bl_string.o tmp$(H)jry_bl$(H)jry_bl_exception.o tmp$(H)jry_bl$(H)jry_bl_malloc.o tmp$(H)jry_bl$(H)jry_bl_base64.o -lm	
md5:jry_bl_string.o jry_bl_array.o jry_bl_exception.o jry_bl_malloc.o jry_bl_md5.o
	$(CC) -c -lm -o tmp$(H)examples$(H)md5.o examples$(H)md5.cpp	
	$(CC) -o exes$(H)md5 tmp$(H)examples$(H)md5.o tmp$(H)jry_bl$(H)jry_bl_string.o tmp$(H)jry_bl$(H)jry_bl_exception.o tmp$(H)jry_bl$(H)jry_bl_malloc.o tmp$(H)jry_bl$(H)jry_bl_md5.o -lm		
jry_bl_string.o:
	$(CC) -c -lm -o tmp$(H)jry_bl$(H)jry_bl_string.o jry_bl$(H)jry_bl_string.cpp
jry_bl_array.o:
	$(CC) -c -lm -o tmp$(H)jry_bl$(H)jry_bl_array.o jry_bl$(H)jry_bl_array.cpp
jry_bl_exception.o:
	$(CC) -c -lm -o tmp$(H)jry_bl$(H)jry_bl_exception.o jry_bl$(H)jry_bl_exception.cpp	
jry_bl_malloc.o:
	$(CC) -c -lm -o tmp$(H)jry_bl$(H)jry_bl_malloc.o jry_bl$(H)jry_bl_malloc.cpp	
jry_bl_base64.o:jry_bl_string.o
	$(CC) -c -lm -o tmp$(H)jry_bl$(H)jry_bl_base64.o jry_bl$(H)jry_bl_base64.cpp	
jry_bl_md5.o:jry_bl_string.o
	$(CC) -c -lm -o tmp$(H)jry_bl$(H)jry_bl_md5.o jry_bl$(H)jry_bl_md5.cpp	