.PHONY: clean

#Name of output binary file;
PROGRAM_NAME=parse

#List of sources files
SOURCE_FILES:=$(wildcard ./*.c)
OBJECT_FILES:=$(foreach tmp, $(SOURCE_FILES), $(tmp:.c=.o))

#Compiler
CC=gcc
C_FLAGS=-Wall -I./
CLEAN=rm -rf

QUIET ?= @

#build exacutable file
$(PROGRAM_NAME): $(OBJECT_FILES)
	$(QUIET)$(CC) $(C_FLAGS) -o $@ $^

#build all object file
%.o: %.c
ifeq ($(QUIET),@)
	@echo Compile $<
endif
	$(QUIET)$(CC) $(C_FLAGS) -c $<

.PHONY: clean


clean:
	$(QUIET)$(CLEAN) $(OBJECT_FILES) $(PROGRAM_NAME)

check:
	@echo $(SOURCE_FILES)
	@echo $(OBJECT_FILES)


