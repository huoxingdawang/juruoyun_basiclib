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
BITS = -g -m64
EXDIR = -I examples -I jbl
EXLIB = $(JBL_EXLIB)
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
all:jbl aes array base64 bitset cmd file ht json ll log malloc md5 rand sha1 stream string time test2 var
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
	exes$(H)aes              && pause
	exes$(H)aes_big          && pause
	exes$(H)aes_stream       && pause
	exes$(H)array            && pause
	exes$(H)base64           && pause
	exes$(H)base64_threads   && pause
	exes$(H)bitset           && pause
	exes$(H)cmd              && pause
	exes$(H)file             && pause
	exes$(H)ht               && pause
	exes$(H)json             && pause
	exes$(H)ll               && pause
	exes$(H)log              && pause
	exes$(H)malloc           && pause
	exes$(H)md5              && pause
	exes$(H)rand             && pause
	exes$(H)sha1             && pause
	exes$(H)stream           && pause
	exes$(H)string           && pause
	exes$(H)string_threads   && pause
	exes$(H)test2            && pause
	exes$(H)time             && pause
	exes$(H)time2            && pause
	exes$(H)var         
#examples
aes:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)aes.o               examples$(H)aes.c               $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)aes_big.o           examples$(H)aes_big.c           $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)aes_stream.o        examples$(H)aes_stream.c        $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)aes                   tmp$(H)$(pre)aes.o               tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)aes_big               tmp$(H)$(pre)aes_big.o           tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)aes_stream            tmp$(H)$(pre)aes_stream.o        tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
array:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)array.o             examples$(H)array.c            $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)array                 tmp$(H)$(pre)array.o             tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
base64:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)base64.o            examples$(H)base64.c            $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)base64_threads.o    examples$(H)base64_threads.c    $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)base64                tmp$(H)$(pre)base64.o            tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)base64_threads        tmp$(H)$(pre)base64_threads.o    tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
bitset:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)bitset.o            examples$(H)bitset.c            $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)bitset                tmp$(H)$(pre)bitset.o            tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
cmd:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)cmd.o               examples$(H)cmd.c               $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)cmd                   tmp$(H)$(pre)cmd.o               tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
file:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)file.o              examples$(H)file.c              $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)file                  tmp$(H)$(pre)file.o              tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
json:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)json.o              examples$(H)json.c              $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)json                  tmp$(H)$(pre)json.o              tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
ht:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)ht.o                examples$(H)ht.c                $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)ht                    tmp$(H)$(pre)ht.o                tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
ll:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)ll.o                examples$(H)ll.c                $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)ll                    tmp$(H)$(pre)ll.o                tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
log:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)log.o               examples$(H)log.c               $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)log                   tmp$(H)$(pre)log.o               tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
malloc:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)malloc.o            examples$(H)malloc.c            $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)malloc                tmp$(H)$(pre)malloc.o            tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
md5:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)md5.o               examples$(H)md5.c               $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)md5                   tmp$(H)$(pre)md5.o               tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
rand:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)rand.o              examples$(H)rand.c              $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)rand                  tmp$(H)$(pre)rand.o              tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
stream:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)stream.o            examples$(H)stream.c            $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)stream                tmp$(H)$(pre)stream.o            tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
string:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)string.o            examples$(H)string.c            $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)string_threads.o    examples$(H)string_threads.c    $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)string                tmp$(H)$(pre)string.o            tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)string_threads        tmp$(H)$(pre)string_threads.o    tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
sha1:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)sha1.o              examples$(H)sha1.c              $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)sha1                  tmp$(H)$(pre)sha1.o              tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
time:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)time.o              examples$(H)time.c              $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)time2.o             examples$(H)time2.c             $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)time                  tmp$(H)$(pre)time.o              tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)time2                 tmp$(H)$(pre)time2.o             tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
test2:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)test2.o             examples$(H)test2.c             $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)test2                 tmp$(H)$(pre)test2.o             tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
var:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)var.o               examples$(H)var.c               $(EXDIR) $(EXLIB)
	$(CC) $(BITS) -o exes$(H)var                   tmp$(H)$(pre)var.o               tmp$(H)$(pre)jbl.a              $(EXDIR) $(EXLIB)
