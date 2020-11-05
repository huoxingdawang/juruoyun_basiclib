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
	$(CC) $(BITS) -o exes$(H)aes         tmp$(H)$(pre)aes.o        tmp$(H)$(pre)jbl.a $(EXLIB)
	$(CC) $(BITS) -o exes$(H)aes_big     tmp$(H)$(pre)aes_big.o    tmp$(H)$(pre)jbl.a $(EXLIB)
	$(CC) $(BITS) -o exes$(H)aes_stream  tmp$(H)$(pre)aes_stream.o tmp$(H)$(pre)jbl.a $(EXLIB)
base64:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)base64.o        examples$(H)base64.c     $(EXLIB)
	$(CC) $(BITS) -o exes$(H)base64      tmp$(H)$(pre)base64.o     tmp$(H)$(pre)jbl.a $(EXLIB)
bitset:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)bitset.o        examples$(H)bitset.c     $(EXLIB)
	$(CC) $(BITS) -o exes$(H)bitset      tmp$(H)$(pre)bitset.o     tmp$(H)$(pre)jbl.a $(EXLIB)
cmd:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)cmd.o           examples$(H)cmd.c        $(EXLIB)
	$(CC) $(BITS) -o exes$(H)cmd         tmp$(H)$(pre)cmd.o        tmp$(H)$(pre)jbl.a $(EXLIB)
file:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)file.o          examples$(H)file.c       $(EXLIB)
	$(CC) $(BITS) -o exes$(H)file        tmp$(H)$(pre)file.o       tmp$(H)$(pre)jbl.a $(EXLIB)
json:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)json.o          examples$(H)json.c	    $(EXLIB)
	$(CC) $(BITS) -o exes$(H)json        tmp$(H)$(pre)json.o       tmp$(H)$(pre)jbl.a $(EXLIB)
ht:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)ht.o            examples$(H)ht.c         $(EXLIB)
	$(CC) $(BITS) -o exes$(H)ht          tmp$(H)$(pre)ht.o         tmp$(H)$(pre)jbl.a $(EXLIB)
ll:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)ll.o            examples$(H)ll.c         $(EXLIB)
	$(CC) $(BITS) -o exes$(H)ll          tmp$(H)$(pre)ll.o         tmp$(H)$(pre)jbl.a $(EXLIB)
log:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)log.o           examples$(H)log.c        $(EXLIB)
	$(CC) $(BITS) -o exes$(H)log         tmp$(H)$(pre)log.o        tmp$(H)$(pre)jbl.a $(EXLIB)
malloc:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)malloc.o        examples$(H)malloc.c     $(EXLIB)
	$(CC) $(BITS) -o exes$(H)malloc      tmp$(H)$(pre)malloc.o     tmp$(H)$(pre)jbl.a $(EXLIB)
md5:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)md5.o           examples$(H)md5.c        $(EXLIB)
	$(CC) $(BITS) -o exes$(H)md5         tmp$(H)$(pre)md5.o        tmp$(H)$(pre)jbl.a $(EXLIB)
rand:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)rand.o          examples$(H)rand.c       $(EXLIB)
	$(CC) $(BITS) -o exes$(H)rand        tmp$(H)$(pre)rand.o       tmp$(H)$(pre)jbl.a $(EXLIB)
stream:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)stream.o        examples$(H)stream.c     $(EXLIB)
	$(CC) $(BITS) -o exes$(H)stream      tmp$(H)$(pre)stream.o     tmp$(H)$(pre)jbl.a $(EXLIB)
string:
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)string.o        examples$(H)string.c         $(EXLIB)
	$(CC) $(BITS) -o exes$(H)string      tmp$(H)$(pre)string.o     tmp$(H)$(pre)jbl.a $(EXLIB)
sha1:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)sha1.o          examples$(H)sha1.c       $(EXLIB)
	$(CC) $(BITS) -o exes$(H)sha1        tmp$(H)$(pre)sha1.o       tmp$(H)$(pre)jbl.a $(EXLIB)
time:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)time.o          examples$(H)time.c       $(EXLIB)
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)time2.o         examples$(H)time2.c      $(EXLIB)
	$(CC) $(BITS) -o exes$(H)time        tmp$(H)$(pre)time.o       tmp$(H)$(pre)jbl.a $(EXLIB)
	$(CC) $(BITS) -o exes$(H)time2       tmp$(H)$(pre)time2.o      tmp$(H)$(pre)jbl.a $(EXLIB)
test2:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)test2.o          examples$(H)test2.c       $(EXLIB)
	$(CC) $(BITS) -o exes$(H)test2        tmp$(H)$(pre)test2.o       tmp$(H)$(pre)jbl.a $(EXLIB)
var:
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)var.o           examples$(H)var.c        $(EXLIB)
	$(CC) $(BITS) -o exes$(H)var         tmp$(H)$(pre)var.o        tmp$(H)$(pre)jbl.a $(EXLIB)
#   Copyright (c) [2020] juruoyun developer team
#   Juruoyun basic lib is licensed under the Mulan PSL v1.
#   You can use this software according to the terms and conditions of the Mulan PSL v1.
#   You may obtain a copy of Mulan PSL v1 at:
#      http://license.coscl.org.cn$(H)MulanPSL
#   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER BITSPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
#   PURPOSE.
#   See the Mulan PSL v1 for more details.
#jbl
ifeq ($(system),linux)
JBL_EXLIB = -lpthread
endif
ifeq ($(system),windows)
JBL_EXLIB = 
endif
jbl                       :jbl/jbl_aes jbl/jbl_array jbl/jbl_base64 jbl/jbl_bitset jbl/jbl_cmd jbl/jbl_exception jbl/jbl_endian jbl/jbl_file jbl/jbl_gc jbl/jbl_ht jbl/jbl_json jbl/jbl_ll jbl/jbl_log jbl/jbl_malloc jbl/jbl_md5 jbl/jbl_pthread jbl/jbl_rand jbl/jbl_scanner jbl/jbl_sha1 jbl/jbl_stream jbl/jbl_string jbl/jbl_time jbl/jbl_var jbl/jbl_ying 
	ar  rc tmp$(H)$(pre)jbl.a tmp$(H)$(pre)jbl_*.o
jbl/jbl_aes            :
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_aes.o         jbl$(H)jbl_aes.c         $(JBL_EXLIB)
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_aes_soft.o    jbl$(H)jbl_aes_soft.c    $(JBL_EXLIB)
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_aes_hard.o    jbl$(H)jbl_aes_hard.c    $(JBL_EXLIB) -maes
jbl/jbl_array          :
	$(CC) $(BITS) -c       -o tmp$(H)$(pre)jbl_array.o       jbl$(H)jbl_array.c       $(JBL_EXLIB)
jbl/jbl_base64         :
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_base64.o      jbl$(H)jbl_base64.c      $(JBL_EXLIB)
jbl/jbl_bitset         :
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)jbl_bitset.o      jbl$(H)jbl_bitset.c      $(JBL_EXLIB)
jbl/jbl_cmd            :
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_cmd.o         jbl$(H)jbl_cmd.c         $(JBL_EXLIB)
jbl/jbl_endian         :
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)jbl_endian.o      jbl$(H)jbl_endian.c      $(JBL_EXLIB)
jbl/jbl_exception      :
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)jbl_exception.o   jbl$(H)jbl_exception.c   $(JBL_EXLIB)
jbl/jbl_file           :
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_file.o        jbl$(H)jbl_file.c        $(JBL_EXLIB)
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_file_ct.o     jbl$(H)jbl_file_ct.c     $(JBL_EXLIB)
jbl/jbl_gc             :
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)jbl_gc.o          jbl$(H)jbl_gc.c          $(JBL_EXLIB)
jbl/jbl_ht             :
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_ht.o          jbl$(H)jbl_ht.c          $(JBL_EXLIB)
jbl/jbl_json           :
ifeq ($(system),linux)
ifeq ($(findstring jbl,$(complain_re2c)),jbl)
	re2c -f -c jbl$(H)jbl_json.l -o jbl$(H)jbl_json.c
endif
endif
ifeq ($(system),macos)
ifeq ($(findstring jbl,$(complain_re2c)),jbl)
	re2c -f -c jbl$(H)jbl_json.l -o jbl$(H)jbl_json.c
endif
endif
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_json.o        jbl$(H)jbl_json.c        $(JBL_EXLIB)
jbl/jbl_ll             :
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_ll.o          jbl$(H)jbl_ll.c          $(JBL_EXLIB)
jbl/jbl_log             :
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_log.o         jbl$(H)jbl_log.c         $(JBL_EXLIB)
jbl/jbl_malloc         :
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)jbl_malloc.o      jbl$(H)jbl_malloc.c      $(JBL_EXLIB)
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)jbl_malloc_fast.o jbl$(H)jbl_malloc_fast.c $(JBL_EXLIB)
jbl/jbl_md5            :
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_md5.o         jbl$(H)jbl_md5.c         $(JBL_EXLIB)
jbl/jbl_pthread        :
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)jbl_pthread.o     jbl$(H)jbl_pthread.c     $(JBL_EXLIB)
jbl/jbl_rand           :
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)jbl_rand.o        jbl$(H)jbl_rand.c        $(JBL_EXLIB)
jbl/jbl_scanner           :
ifeq ($(system),linux)
ifeq ($(findstring jbl,$(complain_re2c)),jbl)
	re2c -o jbl$(H)jbl_scanner.c jbl$(H)jbl_scanner.l
endif
endif
ifeq ($(system),macos)
ifeq ($(findstring jbl,$(complain_re2c)),jbl)
	re2c -o jbl$(H)jbl_scanner.c jbl$(H)jbl_scanner.l
endif
endif
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_scanner.o     jbl$(H)jbl_scanner.c     $(JBL_EXLIB)  
jbl/jbl_sha1           :
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_sha1.o        jbl$(H)jbl_sha1.c        $(JBL_EXLIB)    
jbl/jbl_stream         :
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_stream.o      jbl$(H)jbl_stream.c      $(JBL_EXLIB)
jbl/jbl_string         :
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)jbl_string.o      jbl$(H)jbl_string.c      $(JBL_EXLIB)
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)jbl_string_cc.o   jbl$(H)jbl_string_cc.c   $(JBL_EXLIB)
jbl/jbl_time           :
ifeq ($(system),linux)
ifeq ($(findstring jbl,$(complain_re2c)),jbl)
	re2c -o jbl$(H)jbl_time.c jbl$(H)jbl_time.l
endif
endif
ifeq ($(system),macos)
ifeq ($(findstring jbl,$(complain_re2c)),jbl)
	re2c -o jbl$(H)jbl_time.c jbl$(H)jbl_time.l
endif
endif
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_time.o       jbl$(H)jbl_time.c        $(JBL_EXLIB)
jbl/jbl_var            :
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_var.o        jbl$(H)jbl_var.c         $(JBL_EXLIB)
	$(CC) $(BITS) -c -Wall -o tmp$(H)$(pre)jbl_var_data.o   jbl$(H)jbl_var_data.c    $(JBL_EXLIB)
jbl/jbl_ying           :
	$(CC) $(BITS) -c -Wall -Wextra -Wconversion -o tmp$(H)$(pre)jbl_ying.o       jbl$(H)jbl_ying.c        $(JBL_EXLIB)
