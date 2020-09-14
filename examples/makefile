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
BITS = -g
EXLIB = $(JBL_EXLIB)
complain_re2c = jbl
ifeq ($(shell uname),Linux)
	system = linux
else
ifeq ($(shell uname),Darwin)
	system = macos
else	
	system = windows
endif
endif

ifeq ($(system),linux)
	H = /
	rm = rm -f
	pre = linux_
endif
ifeq ($(system),windows)
	H = \\
	rm = del
	pre = win_
endif
ifeq ($(system),macos)
	H = /
	rm = rm -f
	pre = macos_
endif
# all:jbl aes array base64 bitset cmd file json ht ll malloc md5 rand stream string time sha1 test2 var
all:jbl aes base64 bitset cmd file ht json ll log malloc md5 rand sha1 stream string time test2 var
clean:
	$(rm) tmp$(H)* /s /Q
	$(rm) exes$(H)* /s /Q
	$(rm) testfiles$(H)*.out /s
	$(rm) testfiles$(H)*.ans /s
	$(rm) testfiles$(H)*.html /s
	$(rm) tools$(H)*.exe /s
	$(rm) tools$(H)*$(H)*.exe /s
init:
	mkdir tmp
	mkdir exes
ifeq ($(system),linux)
	sudo gcc tools/pause.c -o /bin/pause
endif
ifeq ($(system),macos)
	sudo gcc tools/pause.c -o /bin/pause
endif
run:
	exes$(H)aes         && pause
	exes$(H)aes_big     && pause
	exes$(H)aes_stream  && pause
#	exes$(H)array       && pause
	exes$(H)base64      && pause
	exes$(H)bitset      && pause
	exes$(H)cmd         && pause
	exes$(H)file        && pause
	exes$(H)ht          && pause
	exes$(H)json        && pause
	exes$(H)ll          && pause
	exes$(H)log         && pause
	exes$(H)malloc      && pause
	exes$(H)md5         && pause
	exes$(H)rand        && pause
	exes$(H)sha1        && pause
	exes$(H)stream      && pause
	exes$(H)string      && pause
	exes$(H)time        && pause
	exes$(H)time2       && pause
	exes$(H)var         
#examples
aes:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)aes.o          examples$(H)aes.c         $(EXLIB)
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)aes_big.o   	  examples$(H)aes_big.c     $(EXLIB)
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)aes_stream.o   examples$(H)aes_stream.c  $(EXLIB)
	$(CC) $(BITS) -o exes$(H)aes         tmp$(H)$(pre)aes.o        tmp$(H)$(pre)jbl.a
	$(CC) $(BITS) -o exes$(H)aes_big     tmp$(H)$(pre)aes_big.o    tmp$(H)$(pre)jbl.a
	$(CC) $(BITS) -o exes$(H)aes_stream  tmp$(H)$(pre)aes_stream.o tmp$(H)$(pre)jbl.a
base64:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)base64.o        examples$(H)base64.c     $(EXLIB)
	$(CC) $(BITS) -o exes$(H)base64      tmp$(H)$(pre)base64.o     tmp$(H)$(pre)jbl.a
bitset:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)bitset.o        examples$(H)bitset.c     $(EXLIB)
	$(CC) $(BITS) -o exes$(H)bitset      tmp$(H)$(pre)bitset.o     tmp$(H)$(pre)jbl.a
cmd:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)cmd.o           examples$(H)cmd.c        $(EXLIB)
	$(CC) $(BITS) -o exes$(H)cmd         tmp$(H)$(pre)cmd.o        tmp$(H)$(pre)jbl.a	
file:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)file.o          examples$(H)file.c       $(EXLIB)
	$(CC) $(BITS) -o exes$(H)file        tmp$(H)$(pre)file.o       tmp$(H)$(pre)jbl.a
json:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)json.o          examples$(H)json.c	    $(EXLIB)
	$(CC) $(BITS) -o exes$(H)json        tmp$(H)$(pre)json.o       tmp$(H)$(pre)jbl.a
ht:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)ht.o            examples$(H)ht.c         $(EXLIB)
	$(CC) $(BITS) -o exes$(H)ht          tmp$(H)$(pre)ht.o         tmp$(H)$(pre)jbl.a	
ll:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)ll.o            examples$(H)ll.c         $(EXLIB)
	$(CC) $(BITS) -o exes$(H)ll          tmp$(H)$(pre)ll.o         tmp$(H)$(pre)jbl.a
log:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)log.o           examples$(H)log.c        $(EXLIB)
	$(CC) $(BITS) -o exes$(H)log         tmp$(H)$(pre)log.o        tmp$(H)$(pre)jbl.a
malloc:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)malloc.o        examples$(H)malloc.c     $(EXLIB)
	$(CC) $(BITS) -o exes$(H)malloc      tmp$(H)$(pre)malloc.o     tmp$(H)$(pre)jbl.a
md5:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)md5.o           examples$(H)md5.c        $(EXLIB)
	$(CC) $(BITS) -o exes$(H)md5         tmp$(H)$(pre)md5.o        tmp$(H)$(pre)jbl.a
rand:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)rand.o          examples$(H)rand.c       $(EXLIB)
	$(CC) $(BITS) -o exes$(H)rand        tmp$(H)$(pre)rand.o       tmp$(H)$(pre)jbl.a	
stream:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)stream.o        examples$(H)stream.c     $(EXLIB)
	$(CC) $(BITS) -o exes$(H)stream      tmp$(H)$(pre)stream.o     tmp$(H)$(pre)jbl.a
string:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)string.o        examples$(H)string.c         $(EXLIB)
	$(CC) $(BITS) -o exes$(H)string      tmp$(H)$(pre)string.o     tmp$(H)$(pre)jbl.a
sha1:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)sha1.o          examples$(H)sha1.c       $(EXLIB)
	$(CC) $(BITS) -o exes$(H)sha1        tmp$(H)$(pre)sha1.o       tmp$(H)$(pre)jbl.a
time:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)time.o          examples$(H)time.c       $(EXLIB)
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)time2.o         examples$(H)time2.c      $(EXLIB)
	$(CC) $(BITS) -o exes$(H)time        tmp$(H)$(pre)time.o       tmp$(H)$(pre)jbl.a
	$(CC) $(BITS) -o exes$(H)time2       tmp$(H)$(pre)time2.o      tmp$(H)$(pre)jbl.a
test2:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)test2.o          examples$(H)test2.c       $(EXLIB)
	$(CC) $(BITS) -o exes$(H)test2        tmp$(H)$(pre)test2.o       tmp$(H)$(pre)jbl.a
var:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)var.o           examples$(H)var.c        $(EXLIB)
	$(CC) $(BITS) -o exes$(H)var         tmp$(H)$(pre)var.o        tmp$(H)$(pre)jbl.a
