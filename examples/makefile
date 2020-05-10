#   Copyright (c) [2019] juruoyun developer team
#   Juruoyun basic lib is licensed under the Mulan PSL v1.
#   You can use this software according to the terms and conditions of the Mulan PSL v1.
#   You may obtain a copy of Mulan PSL v1 at:
#      http://license.coscl.org.cn$(H)MulanPSL
#   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER BITSPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
#   PURPOSE.
#   See the Mulan PSL v1 for more details.
CC = gcc
BITS = -m64 
BITSLIB = $(JBL_BITSLIB)
ifeq ($(shell uname),Linux)
	H = /
	rm = rm -f
else
	H = \\
	rm = del
endif
# all:jbl aes array base64 bitset cmd file json hash_table link_list malloc md5 rand stream string time sha1 test var
all:jbl aes array base64 bitset cmd md5 rand stream string sha1 var
clean:
	$(rm) tmp$(H)*.o /s
	$(rm) tmp$(H)*.a /s
	$(rm) exes$(H)* /s /Q
	$(rm) testfiles$(H)*.out /s
	$(rm) testfiles$(H)*.ans /s
	$(rm) testfiles$(H)*.html /s
init:
	mkdir tmp
	mkdir exes
run:
	exes$(H)string
	exes$(H)aes
#	exes$(H)array
	exes$(H)base64
	exes$(H)bitset
	exes$(H)cmd
	exes$(H)file
	exes$(H)json
	exes$(H)hash_table
	exes$(H)link_list
	exes$(H)malloc
	exes$(H)rand
	exes$(H)md5
	exes$(H)stream
	exes$(H)sha1
	exes$(H)time
	exes$(H)test
	exes$(H)var
#examples
aes:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)aes.o examples$(H)aes.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)aes tmp$(H)aes.o tmp$(H)jbl.a
#array:jbl
#	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)array.o examples$(H)array.c $(BITSLIB)
#	$(CC) -o exes$(H)array tmp$(H)array.o tmp$(H)jbl.a
base64:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)base64.o examples$(H)base64.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)base64 tmp$(H)base64.o tmp$(H)jbl.a
bitset:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)bitset.o examples$(H)bitset.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)bitset tmp$(H)bitset.o tmp$(H)jbl.a
cmd:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)cmd.o examples$(H)cmd.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)cmd tmp$(H)cmd.o tmp$(H)jbl.a	
file:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)file.o examples$(H)file.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)file tmp$(H)file.o tmp$(H)jbl.a
json:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)json.o examples$(H)json.c	$(BITSLIB)
	$(CC) $(BITS) -o exes$(H)json tmp$(H)json.o tmp$(H)jbl.a
hash_table:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)hash_table.o examples$(H)hash_table.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)hash_table tmp$(H)hash_table.o tmp$(H)jbl.a	
link_list:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)link_list.o examples$(H)link_list.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)link_list tmp$(H)link_list.o tmp$(H)jbl.a
malloc:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)malloc.o examples$(H)malloc.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)malloc tmp$(H)malloc.o tmp$(H)jbl.a
md5:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)md5.o examples$(H)md5.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)md5 tmp$(H)md5.o tmp$(H)jbl.a
rand:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)rand.o examples$(H)rand.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)rand tmp$(H)rand.o tmp$(H)jbl.a	
stream:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)stream.o examples$(H)stream.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)stream tmp$(H)stream.o tmp$(H)jbl.a
string:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)string.o examples$(H)string.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)string tmp$(H)string.o tmp$(H)jbl.a
sha1:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)sha1.o examples$(H)sha1.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)sha1 tmp$(H)sha1.o tmp$(H)jbl.a
time:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)time.o examples$(H)time.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)time tmp$(H)time.o tmp$(H)jbl.a
test:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)test.o examples$(H)test.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)test tmp$(H)test.o tmp$(H)jbl.a
var:jbl
	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)var.o examples$(H)var.c $(BITSLIB)
	$(CC) $(BITS) -o exes$(H)var tmp$(H)var.o tmp$(H)jbl.a
