#   Copyright (c) [2019] juruoyun developer team
#   Juruoyun basic lib is licensed under the Mulan PSL v1.
#   You can use this software according to the terms and conditions of the Mulan PSL v1.
#   You may obtain a copy of Mulan PSL v1 at:
#      http://license.coscl.org.cn$(H)MulanPSL
#   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER BITSPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
#   PURPOSE.
#   See the Mulan PSL v1 for more details.
.PHONY:all clean
CC = gcc
BITS = -O2 -m64
EXDIR = -I jbl/
EXLIB = $(JBL_EXLIB)
TMPDIR = tmp/
OUTDIR = exes/
ifeq ($(shell uname),Linux)
	SYSTEM = linux
	PRE = linux_
else ifeq ($(shell uname),Darwin)
	SYSTEM = macos
	PRE = macos_
else	
	SYSTEM = windows
	PRE = win_
endif
all:tmp/win_jbl.a
.SECONDARY:
include jbl/makefile

clean:
ifeq ($(SYSTEM),$(filter $(SYSTEM),linux macos))
	find $(TMPDIR) -name "*.*"  | xargs rm -f
	find $(OUTDIR) -name "*.*"  | xargs rm -f
else ifeq ($(SYSTEM),windows)
	del $(TMPDIR:%/=%\\) /s /Q
	del $(OUTDIR:%/=%\\) /s /Q
endif