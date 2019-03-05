.PHONY: clean

#Name of output binary file;
PROGRAM_NAME=parse

#List of sources files
SOURCE_FILES:=$(wildcard ./src/*.cpp)
OBJECT_FILES:=$(foreach tmp, $(SOURCE_FILES), $(tmp:.cpp=.o))

#Compiler
CC=g++
C_FLAGS= -g -std=C++11 -Wall -I./
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


