#   Copyright (c) [2019] juruoyun developer team
#   Juruoyun basic lib is licensed under the Mulan PSL v1.
#   You can use this software according to the terms and conditions of the Mulan PSL v1.
#   You may obtain a copy of Mulan PSL v1 at:
#      http://license.coscl.org.cn$(H)MulanPSL
#   THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER BITSPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
#   PURPOSE.
#   See the Mulan PSL v1 for more details.
ifeq ($(SYSTEM),linux)
	EXAMPLES_SRC:=$(shell find examples/ -name "*.c")
else ifeq ($(SYSTEM),macos)
	EXAMPLES_SRC:=$(shell find examples -name "*.c")
else ifeq ($(SYSTEM),windows)
	EXAMPLES_SRC:=$(shell dir /b examples\*.c)
	EXAMPLES_SRC:=$(EXAMPLES_SRC:%.c=examples/%.c)
endif
EXAMPLES_DEP:=$(EXAMPLES_SRC:examples/%.c=$(TMPDIR)$(PRE)%.d)
-include $(EXAMPLES_DEP)
run:
	$(OUTDIR)aes              && pause
	$(OUTDIR)aes_big          && pause
	$(OUTDIR)aes_stream       && pause
	$(OUTDIR)array            && pause
	$(OUTDIR)base64           && pause
	$(OUTDIR)base64_threads   && pause
	$(OUTDIR)bitset           && pause
	$(OUTDIR)cmd              && pause
	$(OUTDIR)file             && pause
	$(OUTDIR)ht               && pause
	$(OUTDIR)json             && pause
	$(OUTDIR)ll               && pause
	$(OUTDIR)log              && pause
	$(OUTDIR)malloc           && pause
	$(OUTDIR)md5              && pause
	$(OUTDIR)pthread          && pause
	$(OUTDIR)rand             && pause
	$(OUTDIR)sha1             && pause
	$(OUTDIR)stream           && pause
	$(OUTDIR)string           && pause
	$(OUTDIR)string_threads   && pause
	$(OUTDIR)test2            && pause
	$(OUTDIR)time             && pause
	$(OUTDIR)time2            && pause
	$(OUTDIR)var         
$(TMPDIR)$(PRE)%.d:examples/%.c
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

%:$(TMPDIR)$(PRE)%.o $(TMPDIR)$(PRE)jbl.a
	@echo Linking    $@
	@$(CC) $(BITS) -o $(OUTDIR)$@ $(TMPDIR)$(PRE)$@.o $(TMPDIR)$(PRE)jbl.a $(EXDIR) $(EXLIB)
