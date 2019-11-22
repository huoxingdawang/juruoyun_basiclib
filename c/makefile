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
	rm = rm -f
else
	H = \\
	rm = del
endif
all:jry_bl aes array base64 json md5 string var link_list
clean:
	$(rm) tmp$(H)*.o /s
	$(rm) tmp$(H)*.a /s
	$(rm) exes$(H)* /s /Q
	$(rm) testfiles$(H)*.out /s
	$(rm) testfiles$(H)*.ans /s
	$(rm) testfiles$(H)*.html /s
init:
	mkdir tmp
	mkdir tmp$(H)examples
	mkdir tmp$(H)jry_bl
	mkdir exes
run:
	exes$(H)aes
	exes$(H)array
	exes$(H)base64
	exes$(H)link_list
	exes$(H)md5
	exes$(H)string
	exes$(H)var
#examples
aes:jry_bl
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)aes.o examples$(H)aes.c	
	$(CC) -o exes$(H)aes tmp$(H)examples$(H)aes.o tmp$(H)jry_bl$(H)jry_bl.a
array:jry_bl
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)array.o examples$(H)array.c
	$(CC) -o exes$(H)array tmp$(H)examples$(H)array.o tmp$(H)jry_bl$(H)jry_bl.a
base64:jry_bl
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)base64.o examples$(H)base64.c	
	$(CC) -o exes$(H)base64 tmp$(H)examples$(H)base64.o tmp$(H)jry_bl$(H)jry_bl.a
json:jry_bl
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)json.o examples$(H)json.c	
	$(CC) -o exes$(H)json tmp$(H)examples$(H)json.o tmp$(H)jry_bl$(H)jry_bl.a
link_list:jry_bl
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)link_list.o examples$(H)link_list.c	
	$(CC) -o exes$(H)link_list tmp$(H)examples$(H)link_list.o tmp$(H)jry_bl$(H)jry_bl.a
md5:jry_bl
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)md5.o examples$(H)md5.c	
	$(CC) -o exes$(H)md5 tmp$(H)examples$(H)md5.o tmp$(H)jry_bl$(H)jry_bl.a
string:jry_bl
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)string.o examples$(H)string.c
	$(CC) -o exes$(H)string tmp$(H)examples$(H)string.o tmp$(H)jry_bl$(H)jry_bl.a
var:jry_bl
	$(CC) -c -std=c99 -lm -o tmp$(H)examples$(H)var.o examples$(H)var.c	
	$(CC) -o exes$(H)var tmp$(H)examples$(H)var.o tmp$(H)jry_bl$(H)jry_bl.a
#jry_bl
jry_bl					:jry_bl/jry_bl_aes jry_bl/jry_bl_array jry_bl/jry_bl_base64 jry_bl/jry_bl_base64 jry_bl/jry_bl_link_list jry_bl/jry_bl_malloc jry_bl/jry_bl_md5 jry_bl/jry_bl_string jry_bl/jry_bl_var jry_bl/jry_bl_ying
	ar rc tmp$(H)jry_bl$(H)jry_bl.a tmp$(H)jry_bl$(H)*.o
jry_bl/jry_bl_aes		:jry_bl/jry_bl_ying jry_bl/jry_bl_exception jry_bl/jry_bl_malloc jry_bl/jry_bl_string
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_aes.o jry_bl$(H)jry_bl_aes.c
jry_bl/jry_bl_array		:jry_bl/jry_bl_ying jry_bl/jry_bl_exception jry_bl/jry_bl_malloc
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_array.o jry_bl$(H)jry_bl_array.c
jry_bl/jry_bl_base64	:jry_bl/jry_bl_ying jry_bl/jry_bl_exception jry_bl/jry_bl_malloc jry_bl/jry_bl_string
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_base64.o jry_bl$(H)jry_bl_base64.c	
jry_bl/jry_bl_exception	:jry_bl/jry_bl_ying 
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_exception.o jry_bl$(H)jry_bl_exception.c
jry_bl/jry_bl_link_list :jry_bl/jry_bl_ying jry_bl/jry_bl_exception jry_bl/jry_bl_malloc jry_bl/jry_bl_var
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_link_list.o jry_bl$(H)jry_bl_link_list.c
jry_bl/jry_bl_malloc	:jry_bl/jry_bl_ying jry_bl/jry_bl_exception
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_malloc.o jry_bl$(H)jry_bl_malloc.c
jry_bl/jry_bl_md5		:jry_bl/jry_bl_ying jry_bl/jry_bl_exception jry_bl/jry_bl_malloc jry_bl/jry_bl_string
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_md5.o jry_bl$(H)jry_bl_md5.c
jry_bl/jry_bl_string	:jry_bl/jry_bl_ying jry_bl/jry_bl_exception jry_bl/jry_bl_malloc
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_string.o jry_bl$(H)jry_bl_string.c
jry_bl/jry_bl_var		:jry_bl/jry_bl_ying jry_bl/jry_bl_exception jry_bl/jry_bl_malloc jry_bl/jry_bl_string
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_var.o jry_bl$(H)jry_bl_var.c
jry_bl/jry_bl_ying		:
	$(CC) -c -std=c99 -lm -o tmp$(H)jry_bl$(H)jry_bl_ying.o jry_bl$(H)jry_bl_ying.c	