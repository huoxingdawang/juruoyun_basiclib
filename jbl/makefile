#   Copyright (c) [2020] juruoyun developer team
#   Juruoyun basic lib is licensed under the Mulan PSL v1.
#   You can use this software according to the terms and conditions of the Mulan PSL v1.
#   You may obtain a copy of Mulan PSL v1 at:
#	  http://license.coscl.org.cn$(H)MulanPSL
#   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER BITSPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
#   PURPOSE.
#   See the Mulan PSL v1 for more details.
ifeq ($(SYSTEM),linux)
	JBL_SRC:=$(shell find jbl/ -name "*.[cl]")
	JBL_EXLIB = -lpthread -maes
else ifeq ($(SYSTEM),macos)
	JBL_SRC:=$(shell find jbl -name "*.[cl]")
	JBL_EXLIB = -maes
else ifeq ($(SYSTEM),windows)
	JBL_SRC:=$(shell dir /b jbl\*.c jbl\*.l)
	JBL_SRC:=$(JBL_SRC:%.c=jbl/%.c)
	JBL_SRC:=$(JBL_SRC:%.l=jbl/%.l)
	JBL_EXLIB =  -maes
endif
JBL_DEP:=$(JBL_SRC:jbl/%.c=$(TMPDIR)$(PRE)%.d)
JBL_DEP:=$(JBL_DEP:jbl/%.l=$(TMPDIR)$(PRE)%.d)
-include $(JBL_DEP)

$(TMPDIR)jbl_json.c:jbl/jbl_json.l jbl/jbl_json.h
ifeq ($(SYSTEM),$(filter $(SYSTEM),linux macos))
	@echo "Re2c       $@"
	@re2c -f -c $< -o $@
endif
$(TMPDIR)jbl_scanner.c:jbl/jbl_scanner.l jbl/jbl_scanner.h
ifeq ($(SYSTEM),$(filter $(SYSTEM),linux macos))
	@echo "Re2c       $@"
	@re2c -o $@ $<
endif
$(TMPDIR)jbl_time.c:jbl/jbl_time.l jbl/jbl_scanner.h
ifeq ($(SYSTEM),$(filter $(SYSTEM),linux macos))
	@echo "Re2c       $@"
	@re2c -o $@ $<
endif


$(TMPDIR)$(PRE)%.d:jbl/%.c
	@echo Generating $@
ifeq ($(SYSTEM),$(filter $(SYSTEM),linux macos))
	@echo $(TMPDIR)$(PRE)$(shell $(CC) -MM $< $(EXDIR) $(EXLIB))>$@
	@echo "\t@$(CC) $(BITS) -Wall -Wextra -Wconversion -c $< -o $(@:%.d=%.o) $(EXDIR) $(EXLIB)">>$@
	@echo "\t@echo 'Compling   $@'">>$@
else ifeq ($(SYSTEM),windows)
	@echo $(TMPDIR)$(PRE)$(subst \,,$(shell $(CC) -MM $< $(EXDIR) $(EXLIB))>$@)
	@echo 	@$(CC) $(BITS) -Wall -Wextra -Wconversion -c $< -o $(@:%.d=%.o) $(EXDIR) $(EXLIB)>>$@
	@echo 	@echo Compling   $@>>$@
endif
$(TMPDIR)$(PRE)%.d:$(TMPDIR)%.c
	@echo Generating $@
ifeq ($(SYSTEM),$(filter $(SYSTEM),linux macos))
	@echo $(TMPDIR)$(PRE)$(shell $(CC) -MM $< $(EXDIR) $(EXLIB))>$@
	@echo "\t@$(CC) $(BITS) -Wall -Wextra -Wconversion -c $< -o $(@:%.d=%.o) $(EXDIR) $(EXLIB)">>$@
	@echo "\t@echo 'Compling   $@'">>$@
else ifeq ($(SYSTEM),windows)
	@echo $(TMPDIR)$(PRE)$(subst \,,$(shell $(CC) -MM $< $(EXDIR) $(EXLIB))>$@)
	@echo 	@$(CC) $(BITS) -Wall -Wextra -Wconversion -c $< -o $(@:%.d=%.o) $(EXDIR) $(EXLIB)>>$@
	@echo 	@echo Compling   $@>>$@
endif

$(TMPDIR)$(PRE)jbl.a:$(JBL_SRC:jbl/%.c=$(TMPDIR)$(PRE)%.o) $(JBL_SRC:jbl/%.l=$(TMPDIR)$(PRE)%.o)
	@echo "packaging  $@"
	@ar  rc $(TMPDIR)$(PRE)jbl.a $(TMPDIR)$(PRE)jbl*.o


