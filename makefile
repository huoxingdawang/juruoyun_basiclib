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
BITS =
EXLIB = $(JBL_EXLIB)
ifeq ($(shell uname),Linux)
	H = /
	rm = rm -f
	pre = linux_
else
	H = \\
	rm = del
	pre = win_
endif
# all:jbl aes array base64 bitset cmd file json ht ll malloc md5 rand stream string time sha1 test2 var
all:jbl aes base64 bitset cmd ht json ll malloc md5 rand sha1 stream string time test2 var
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
ifeq ($(shell uname),Linux)
	sudo gcc tools/pause.c -o /bin/pause
endif
run:
	exes$(H)aes         && pause
#	exes$(H)array       && pause
	exes$(H)base64      && pause
	exes$(H)bitset      && pause
	exes$(H)cmd         && pause
#	exes$(H)file        && pause
	exes$(H)ht          && pause
	exes$(H)json        && pause
	exes$(H)ll          && pause
	exes$(H)malloc      && pause
	exes$(H)md5         && pause
	exes$(H)rand        && pause
	exes$(H)sha1        && pause
	exes$(H)stream      && pause
	exes$(H)string      && pause
	exes$(H)string_var  && pause
	exes$(H)time        && pause
	exes$(H)time2       && pause
	exes$(H)time_var    && pause
	exes$(H)var         && pause
	exes$(H)var_refer
#examples
aes:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)aes.o       examples$(H)aes.c      $(EXLIB)
	$(CC) $(BITS) -o exes$(H)aes         tmp$(H)$(pre)aes.o       tmp$(H)$(pre)jbl.a
#array:
#	$(CC) $(BITS) -c -std=gnu99 -o tmp$(H)$(pre)array.o examples$(H)array.c $(EXLIB)
#	$(CC) -o exes$(H)array tmp$(H)$(pre)array.o tmp$(H)$(pre)jbl.a
base64:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)base64.o     examples$(H)base64.c $(EXLIB)
	$(CC) $(BITS) -o exes$(H)base64      tmp$(H)$(pre)base64.o     tmp$(H)$(pre)jbl.a
bitset:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)bitset.o     examples$(H)bitset.c $(EXLIB)
	$(CC) $(BITS) -o exes$(H)bitset      tmp$(H)$(pre)bitset.o     tmp$(H)$(pre)jbl.a
cmd:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)cmd.o        examples$(H)cmd.c    $(EXLIB)
	$(CC) $(BITS) -o exes$(H)cmd         tmp$(H)$(pre)cmd.o        tmp$(H)$(pre)jbl.a	
file:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)file.o       examples$(H)file.c   $(EXLIB)
	$(CC) $(BITS) -o exes$(H)file        tmp$(H)$(pre)file.o       tmp$(H)$(pre)jbl.a
json:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)json.o       examples$(H)json.c	$(EXLIB)
	$(CC) $(BITS) -o exes$(H)json        tmp$(H)$(pre)json.o       tmp$(H)$(pre)jbl.a
ht:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)ht.o         examples$(H)ht.c     $(EXLIB)
	$(CC) $(BITS) -o exes$(H)ht          tmp$(H)$(pre)ht.o         tmp$(H)$(pre)jbl.a	
ll:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)ll.o         examples$(H)ll.c     $(EXLIB)
	$(CC) $(BITS) -o exes$(H)ll          tmp$(H)$(pre)ll.o         tmp$(H)$(pre)jbl.a
malloc:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)malloc.o     examples$(H)malloc.c $(EXLIB)
	$(CC) $(BITS) -o exes$(H)malloc      tmp$(H)$(pre)malloc.o     tmp$(H)$(pre)jbl.a
md5:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)md5.o        examples$(H)md5.c    $(EXLIB)
	$(CC) $(BITS) -o exes$(H)md5         tmp$(H)$(pre)md5.o        tmp$(H)$(pre)jbl.a
rand:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)rand.o       examples$(H)rand.c   $(EXLIB)
	$(CC) $(BITS) -o exes$(H)rand        tmp$(H)$(pre)rand.o       tmp$(H)$(pre)jbl.a	
stream:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)stream.o     examples$(H)stream.c $(EXLIB)
	$(CC) $(BITS) -o exes$(H)stream      tmp$(H)$(pre)stream.o     tmp$(H)$(pre)jbl.a
string:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)string.o     examples$(H)string.c     $(EXLIB)
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)string_var.o examples$(H)string_var.c $(EXLIB)
	$(CC) $(BITS) -o exes$(H)string      tmp$(H)$(pre)string.o     tmp$(H)$(pre)jbl.a
	$(CC) $(BITS) -o exes$(H)string_var  tmp$(H)$(pre)string_var.o tmp$(H)$(pre)jbl.a
sha1:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)sha1.o       examples$(H)sha1.c   $(EXLIB)
	$(CC) $(BITS) -o exes$(H)sha1        tmp$(H)$(pre)sha1.o       tmp$(H)$(pre)jbl.a
time:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)time.o       examples$(H)time.c   $(EXLIB)
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)time2.o      examples$(H)time2.c  $(EXLIB)
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)time_var.o   examples$(H)time_var.c   $(EXLIB)
	$(CC) $(BITS) -o exes$(H)time        tmp$(H)$(pre)time.o       tmp$(H)$(pre)jbl.a
	$(CC) $(BITS) -o exes$(H)time2       tmp$(H)$(pre)time2.o      tmp$(H)$(pre)jbl.a
	$(CC) $(BITS) -o exes$(H)time_var    tmp$(H)$(pre)time_var.o   tmp$(H)$(pre)jbl.a
test2:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)test2.o       examples$(H)test2.c   $(EXLIB)
	$(CC) $(BITS) -o exes$(H)test2        tmp$(H)$(pre)test2.o       tmp$(H)$(pre)jbl.a
var:
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)var.o        examples$(H)var.c    $(EXLIB)
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)var_refer.o  examples$(H)var_refer.c    $(EXLIB)
	$(CC) $(BITS) -o exes$(H)var         tmp$(H)$(pre)var.o        tmp$(H)$(pre)jbl.a
	$(CC) $(BITS) -o exes$(H)var_refer   tmp$(H)$(pre)var_refer.o  tmp$(H)$(pre)jbl.a
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
ifeq ($(shell uname),Linux)
JBL_EXLIB = 
else
JBL_EXLIB = 
endif
jbl                       :jbl/jbl_aes jbl/jbl_array jbl/jbl_base64 jbl/jbl_bitset jbl/jbl_cmd jbl/jbl_exception jbl/jbl_file jbl/jbl_gc jbl/jbl_ht jbl/jbl_ll jbl/jbl_log jbl/jbl_malloc jbl/jbl_md5 jbl/jbl_rand jbl/jbl_sha1 jbl/jbl_stream jbl/jbl_string jbl/jbl_time jbl/jbl_var jbl/jbl_ying 
	ar  rc tmp$(H)$(pre)jbl.a tmp$(H)$(pre)jbl_*.o
jbl/jbl_aes            :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_aes.o        jbl$(H)jbl_aes.c        $(JBL_EXLIB)
jbl/jbl_array          :
	$(CC) $(BITS) -c       -std=gnu99 -o tmp$(H)$(pre)jbl_array.o      jbl$(H)jbl_array.c      $(JBL_EXLIB)
jbl/jbl_base64         :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_base64.o     jbl$(H)jbl_base64.c     $(JBL_EXLIB)
jbl/jbl_bitset         :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_bitset.o     jbl$(H)jbl_bitset.c     $(JBL_EXLIB)
jbl/jbl_cmd            :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_cmd.o        jbl$(H)jbl_cmd.c        $(JBL_EXLIB)
jbl/jbl_exception      :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_exception.o  jbl$(H)jbl_exception.c  $(JBL_EXLIB)
jbl/jbl_file           :
	$(CC) $(BITS) -c       -std=gnu99 -o tmp$(H)$(pre)jbl_file.o       jbl$(H)jbl_file.c       $(JBL_EXLIB)
jbl/jbl_gc             :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_gc.o         jbl$(H)jbl_gc.c         $(JBL_EXLIB)
jbl/jbl_ht             :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_ht.o         jbl$(H)jbl_ht.c         $(JBL_EXLIB)
jbl/jbl_ll             :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_ll.o         jbl$(H)jbl_ll.c         $(JBL_EXLIB)
jbl/jbl_log             :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_log.o        jbl$(H)jbl_log.c         $(JBL_EXLIB)
jbl/jbl_malloc         :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_malloc.o     jbl$(H)jbl_malloc.c     $(JBL_EXLIB)
jbl/jbl_md5            :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_md5.o        jbl$(H)jbl_md5.c        $(JBL_EXLIB)
jbl/jbl_rand           :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_rand.o       jbl$(H)jbl_rand.c       $(JBL_EXLIB)
jbl/jbl_sha1           :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_sha1.o       jbl$(H)jbl_sha1.c       $(JBL_EXLIB)    
jbl/jbl_stream         :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_stream.o     jbl$(H)jbl_stream.c     $(JBL_EXLIB)
jbl/jbl_string         :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_string.o     jbl$(H)jbl_string.c     $(JBL_EXLIB)
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_string_cc.o  jbl$(H)jbl_string_cc.c  $(JBL_EXLIB)
jbl/jbl_time           :
	$(CC) $(BITS) -c       -std=gnu99 -o tmp$(H)$(pre)jbl_time.o       jbl$(H)jbl_time.c       $(JBL_EXLIB)
jbl/jbl_var            :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_var.o        jbl$(H)jbl_var.c        $(JBL_EXLIB)
jbl/jbl_ying           :
	$(CC) $(BITS) -c -Wall -std=gnu99 -o tmp$(H)$(pre)jbl_ying.o       jbl$(H)jbl_ying.c       $(JBL_EXLIB)
