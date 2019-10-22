#   Copyright (c) [2019] juruoyun developer team
#   Juruoyun basic lib is licensed under the Mulan PSL v1.
#   You can use this software according to the terms and conditions of the Mulan PSL v1.
#   You may obtain a copy of Mulan PSL v1 at:
#      http://license.coscl.org.cn$(H)MulanPSL
#   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
#   PURPOSE.
#   See the Mulan PSL v1 for more details.
CC = gcc
ifeq ($(shell uname),Linux)
	H = /
else
	H = \\
endif
all:aes array base64 json md5 string
init:
	mkdir tmp
	mkdir tmp$(H)examples
	mkdir tmp$(H)jry_bl
	mkdir exes
clean:
	del tmp\*.o /s
	del exes\*.exe /s
	del testfiles\*.out /s
	del testfiles\*.ans /s
	del testfiles\*.html /s
#examples
aes:jry_bl/jry_bl_aes jry_bl/jry_bl_base64
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)aes.o examples$(H)aes.c
	$(CC) -o exes$(H)aes tmp$(H)examples$(H)aes.o tmp$(H)jry_bl$(H)jry_bl_string.o tmp$(H)jry_bl$(H)jry_bl_exception.o tmp$(H)jry_bl$(H)jry_bl_malloc.o tmp$(H)jry_bl$(H)jry_bl_aes.o tmp$(H)jry_bl$(H)jry_bl_base64.o -lm	
array:jry_bl/jry_bl_array
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)array.o examples$(H)array.c
	$(CC) -o exes$(H)array tmp$(H)examples$(H)array.o tmp$(H)jry_bl$(H)jry_bl_exception.o tmp$(H)jry_bl$(H)jry_bl_malloc.o tmp$(H)jry_bl$(H)jry_bl_array.o -lm	
base64:jry_bl/jry_bl_base64
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)base64.o examples$(H)base64.c	
	$(CC) -o exes$(H)base64 tmp$(H)examples$(H)base64.o tmp$(H)jry_bl$(H)jry_bl_string.o tmp$(H)jry_bl$(H)jry_bl_exception.o tmp$(H)jry_bl$(H)jry_bl_malloc.o tmp$(H)jry_bl$(H)jry_bl_base64.o -lm	
json:jry_bl/jry_bl_string
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)json.o examples$(H)json.c	
	$(CC) -o exes$(H)json tmp$(H)examples$(H)json.o tmp$(H)jry_bl$(H)jry_bl_string.o tmp$(H)jry_bl$(H)jry_bl_exception.o tmp$(H)jry_bl$(H)jry_bl_malloc.o -lm
md5:jry_bl/jry_bl_md5
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)md5.o examples$(H)md5.c	
	$(CC) -o exes$(H)md5 tmp$(H)examples$(H)md5.o tmp$(H)jry_bl$(H)jry_bl_string.o tmp$(H)jry_bl$(H)jry_bl_exception.o tmp$(H)jry_bl$(H)jry_bl_malloc.o tmp$(H)jry_bl$(H)jry_bl_md5.o -lm
string:jry_bl/jry_bl_string
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)string.o examples$(H)string.c
	$(CC) -o exes$(H)string tmp$(H)examples$(H)string.o tmp$(H)jry_bl$(H)jry_bl_string.o tmp$(H)jry_bl$(H)jry_bl_exception.o tmp$(H)jry_bl$(H)jry_bl_malloc.o -lm

#jry_bl
jry_bl/jry_bl_aes:jry_bl/jry_bl_string
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_aes.o jry_bl$(H)jry_bl_aes.c
jry_bl/jry_bl_array:jry_bl/jry_bl_exception jry_bl/jry_bl_malloc
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_array.o jry_bl$(H)jry_bl_array.c
jry_bl/jry_bl_base64:jry_bl/jry_bl_string
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_base64.o jry_bl$(H)jry_bl_base64.c	
jry_bl/jry_bl_exception:
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_exception.o jry_bl$(H)jry_bl_exception.c	
jry_bl/jry_bl_malloc:
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_malloc.o jry_bl$(H)jry_bl_malloc.c
jry_bl/jry_bl_md5:jry_bl/jry_bl_string
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_md5.o jry_bl$(H)jry_bl_md5.c
jry_bl/jry_bl_string:jry_bl/jry_bl_exception jry_bl/jry_bl_malloc
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_string.o jry_bl$(H)jry_bl_string.c
	